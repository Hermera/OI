#include <cstdio>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 2e6 + 5;
const int mod = 998244353;

int n, m = (1 << 20);
ll a[N], b[N], f1[N], f2[N];

ll quickpow(ll x, int k) {	
	ll ret = 1;
	for (; k; k >>= 1, (x *= x) %= mod)
		if (k & 1) (ret *= x) %= mod;
	return ret;
}

void fwt(ll *s, int on) {
	for (int h = 2; h <= m; h <<= 1) 
		for (int i = 0; i < m; i += h)
			for (int j = i; j < i + h / 2; ++j) {
				int u = s[j], v = s[j + h / 2];
				s[j] = (u + v) % mod;
				s[j + h / 2] = (u - v) % mod;
			}
	if (!on) {
		ll inv = quickpow(m, mod - 2);
		for (int i = 0; i < m; ++i)
			s[i] = s[i] * inv % mod;
	}
}


int main() {
	n = read();
	for (int i = 1; i <= n; ++i) 
		a[read()] += 2;
	a[0] += n;	
	fwt(a, 1);
	
	f1[0] = f2[0] = 1;
	for (int i = 1; i <= n; ++i) {
		f1[i] = f1[i - 1] * 3 % mod;
		f2[i] = -f2[i - 1];
	}
	
	for (int i = 0; i < m; ++i) {
		int x = (a[i] + n) / 4, y = n - x;
		b[i] = f1[x] * f2[y] % mod;
	}
	fwt(b, 0);
	
	int ans = (b[0] + mod) % mod;
	ans = (ans + mod - 1) % mod;
	printf("%d\n", ans);
	return 0;
}
