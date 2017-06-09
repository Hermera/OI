#include <cstdio>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 1e6 + 2000 + 5;
const int K = 2005;
const int mod = 1e9+7;


void update(int &x, int y) {
	x += y;
	if(x < 0) x += mod;
	if(x >= mod) x -= mod;
}

ll quickpow(ll x, int k) {
	ll ret = 1;
	for(; k; k >>= 1, (x *= x) %= mod)
		if(k & 1) (ret *= x) %= mod;
	return ret;
}

ll fac[N], inv[N];
ll combine(int n, int m) {
	ll ret = fac[n];
	(ret *= inv[m]) %= mod;
	(ret *= inv[n-m]) %= mod;
	return ret;
}

int f[K], g[K], s[K], v[K];
int ans[K], n, q, m = 2000;


int main() {
	n = 1e6 + 2000, fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
	inv[n] = quickpow(fac[n], mod - 2);
	for(int i = n; i >= 1; --i) inv[i-1] = inv[i] * i % mod;

	n = read(), f[0] = 1;
	for(int i = 1; i <= n; ++i) ++s[read()];
	for(int i = 1; i <= m; ++i) if(s[i]) {
		for(int j = 0; j <= m; ++j) g[j] = f[j], f[j] = 0;
		for(int j = 0; j <= s[i]; ++j) {
			int d = j & 1 ? -1 : 1;
			for(int p = 0; p <= m; ++p)
				if(p + (i+1)*j > m) continue;
				else update(f[p + (i+1)*j], 1LL * g[p] * combine(s[i], j) * d % mod);
		}
	}
	
	for(int i = 0; i <= m; ++i) v[i] = combine(n+i-1, i);
	for(int i = 0; i <= m; ++i)
		for(int j = 0; j <= i; ++j)
			update(ans[i], 1LL * f[j] * v[i-j] % mod);
			
	q = read();
	while(q--) printf("%d\n", ans[read()]);
	return 0;	
}
