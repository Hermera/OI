#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

int gcd(int x, int y) {
	return !y ? x : gcd(y, x % y);
}

const int N = 1e5+5;
const int mod = 998244353;

typedef pair<int, int> pii;
#define fir first
#define sec second

pii p[N];
int n, t;
int a[N], f[N], g[N];



int main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i)	f[i] = gcd(a[i], f[i-1]);
	for(int i = n; i >= 1; --i) g[i] = gcd(a[i], g[i+1]);

	int l = n, r = n;
	for(l = n; l >= 1; --l) 
		if(g[r+1] != g[l+1]) {
			p[++t] = pii(l+1, r);
			r = l;
		}
	if(1 < r) p[++t] = pii(1, r);

	int ans = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= t; ++j) {
			int l = max(i, p[j].fir);
			int r = p[j].sec;
			int v = gcd(f[i-1], g[r+1]);
			if(l <= r) {
				(ans += 1LL * v * (r - l + 1) % mod) %= mod;
			}
		}
	
	(ans += mod - a[1]) %= mod;
	(ans += mod - a[n]) %= mod;

	printf("%d\n", ans);
}