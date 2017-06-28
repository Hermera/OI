#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxp = 65;
const int maxl = 18;
const int maxm = 60005;
const int mod = 998244353;
const int G = 3;

ll pow(ll x, int k, int mod) {
	ll ret = 1;
	if(k < 0) k += mod-1;
	for(; k; k >>= 1, (x *= x) %= mod) 
		if(k & 1) (ret *= x) %= mod;
	return ret;
}

int n, m, p, l, rev[maxm];
ll pw[maxl][maxm][2];
void forward(int m) {
	for(l = 1; l <= m; l <<= 1); l <<= 1;
	for(int i = 0; i < l; ++i) rev[i] = -1;
	for(int i = 0, t = 0; i < l; ++i) {
		if(i > t) rev[i] = t;
		for(int j = l>>1; (t ^= j) < j; j >>= 1);
	}
	for(int h = 2, t = 1; h <= l; h <<= 1, ++t) {
		ll wn0 = pow(G, -(mod - 1) / h, mod);
		ll wn1 = pow(G, (mod - 1) / h, mod);
		for(int j = 0; j < l; j += h) {
			ll w0 = 1, w1 = 1;
			for(int k = j; k < j + h / 2; ++k) {
				pw[t][k][0] = w0;
				pw[t][k][1] = w1;
				(w0 *= wn0) %= mod;
				(w1 *= wn1) %= mod;
			}
		}
	}
}

inline int inc(int x) {
	if(x >= mod) x -= mod;
	if(x < 0) x += mod;
	return x;
}

void NTT(ll *x, int len, int d) {
	for(int i = 0; i < len; ++i)
		if(~rev[i]) swap(x[i], x[rev[i]]);
	ll u = 0, v = 0;
	for(int h = 2, t = 1; h <= len; h <<= 1, ++t) 
		for(int j = 0; j < len; j += h) 
			for(int k = j; k < j + h / 2; ++k) 
				u = x[k], v = pw[t][k][d]*x[k+h/2]%mod,
				x[k] = inc(u+v), x[k+h/2] = inc(u-v);

	if(d > 0) return;
	ll inv = pow(len, -1, mod);
	for(int i = 0; i < len; ++i) (x[i] *= inv) %= mod;
}


ll f[maxp][maxm], g[maxp][maxm], h[maxp][maxm];
void clear(ll *x, int len) {
	for(int i = m+1; i < l; ++i) x[i] = 0;
}

int main() {
	scanf("%d%d%d", &n, &p, &m);
	forward(m);
	
	h[0][0] = 1;
	int x1 = 1, x2 = 1;
	int y1 = 0, y2 = 1;
	for(int i = 0; i < 10; ++i) 
		if(i <= m) f[i%p][i] = 1;
	for(; n; n >>= 1) {
		if(n & 1) {
			y2 = pow(10, y1, p), y1 += x1;
			memset(g, 0, sizeof(g));
			for(int i = 0; i < p; ++i) NTT(f[i], l, 1), NTT(h[i], l, 1);
			for(int i = 0; i < p; ++i)
			for(int j = 0; j < p; ++j)
			for(int k = 0; k < l; ++k)
				(g[(y2*i+j)%p][k] += f[i][k]*h[j][k]) %= mod;
			memcpy(h, g, sizeof(g));
			for(int i = 0; i < p; ++i) NTT(h[i], l, 0), NTT(f[i], l, 0);
			for(int i = 0; i < p; ++i) clear(h[i], m), clear(f[i], m);
		}
		
		x2 = pow(10, x1, p), x1 <<= 1;
		memset(g, 0, sizeof(g));
		for(int i = 0; i < p; ++i) NTT(f[i], l, 1);
		for(int i = 0; i < p; ++i)
		for(int j = 0; j < p; ++j)
		for(int k = 0; k < l; ++k)
			(g[(x2*i+j)%p][k] += f[i][k]*f[j][k]) %= mod;
		memcpy(f, g, sizeof(g));
		for(int i = 0; i < p; ++i) NTT(f[i], l, 0);
		for(int i = 0; i < p; ++i) clear(f[i], m);
	}
	
	ll ans = 0;
	for(int i = 0; i <= m; ++i) {
		(ans += h[0][i]) %= mod;
		printf("%lld ", ans);
	}
	return 0;
}
