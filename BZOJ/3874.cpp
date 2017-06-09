#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 3e5+5;
const int mod = 786433;
const int G = 10;

int quickpow(int x, int k) {
	int ret = 1;
	for(; k; k >>= 1, x = (ll)x * x % mod)
		if(k & 1) ret = (ll)ret * x % mod;
	return ret;
}

int n, m, len;
int fac[N], val[N], X[N], Y[N];
void NTT(int *s, int on) {
	for(int i = 0, t = 0; i < len; ++i) {
		if(i > t) swap(s[i], s[t]);
		for(int j = len >> 1; (t ^= j) < j; j >>= 1);
	}
	
	for(int h = 2; h <= len; h <<= 1) {
		int wn = quickpow(G, on ? (mod-1)/h : mod-1 - (mod-1)/h);
		for(int i = 0; i < len; i += h) {
			int w = 1, x, y;
			for(int j = i; j < i+h/2; ++j) {
				x = s[j], y = (ll)s[j+h/2] * w % mod;
				s[j] = (x + y) % mod;
				s[j+h/2] = (x - y + mod) % mod;
				w = (ll)w * wn % mod;
			}
		}
	}
	
	if(!on) {
		int inv = quickpow(len, mod - 2);
		for(int i = 0; i < len; ++i)
			s[i] = (ll)s[i] * inv % mod;
	}
}


void getlen(int x) {
	len = 1;
	while(len <= x) len <<= 1;
	len <<= 1;
}

void calc(int l, int r) {
	if(l == r) return;
	int d = (l + r) >> 1;
	
	calc(l, d);
	getlen(r - l + 1);
	for(int i = 0; i < len; ++i) X[i] = Y[i] = 0;
	for(int i = 0; i < len; ++i) Y[i] = fac[i];
	for(int i = l; i <= d; ++i) X[i-l] = val[i];
	
	NTT(X, 1), NTT(Y, 1);
	for(int i = 0; i < len; ++i) X[i] = (ll)X[i] * Y[i] % mod;
	NTT(X, 0);
	
	for(int i = d+1; i <= r; ++i)
		val[i] = (val[i] - X[i-l] + mod) % mod;
	calc(d+1, r);
}

void prepare() {
	n = 1e5, fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = (ll)fac[i-1] * i % mod;
	for(int i = 1; i <= n; ++i) val[i] = fac[i];
	calc(1, n);
}


int cas;
void solve() {
	n = read(), m = read();
	
	int ans = 1;
	for(int i = 1; i <= m; ++i) {
		int x = read();
		int mn = n + 1, mx = 0;
		for(int j = 1; j <= x; ++j) {
			int y = read();
			mn = min(mn, y);
			mx = max(mx, y);
		}
		
		if(mx - mn + 1 != x) ans = 0;
		else ans = (ll)ans * val[x] % mod;
	}
	printf("%d\n", ans);
}

int main() {
	prepare();
	
	cas = read();
	while(cas--) solve();
	return 0;
}
