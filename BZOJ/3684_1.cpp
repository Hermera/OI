#include <cstdio>
#include <cstring>
#include <assert.h>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e5+5;
const int maxl = 20;
const int root = 7;
const int mod = 950009857;

ll pow(ll x, int k) {
	ll ret = 1;
	for(; k; k >>= 1, (x *= x) %= mod)
		if(k & 1) (ret *= x) %= mod;
	return ret;
}

ll pwn[maxl][2], pw[maxl][maxn][2];
void precalc(int len) {
	for(int h = 2, k = 0; h <= len; ++k, h <<= 1) {
		pwn[k][1] = pow(root, (mod-1)/h);
		pwn[k][0] = pow(root, mod-1 - (mod-1)/h);
		for(int i = 0; i < len; i += h) {
			ll w0 = 1, w1 = 1;
			for(int j = i; j < i + h/2; ++j) 
				pw[k][j][0] = w0, w0 = w0*pwn[k][0]%mod,
				pw[k][j][1] = w1, w1 = w1*pwn[k][1]%mod;
		}
	}
}

void rev(ll *s, int len) {
	for(int i = 0, t = 0; i < len; ++i) {
		if(i > t) swap(s[i], s[t]);
		for(int j = len>>1; (t ^= j) < j; j >>= 1);
	}
}

void FFT(ll *s, int len, int on) {
	rev(s, len);
	for(int h = 2, k = 0; h <= len; ++k, h <<= 1) {
		ll wn = pwn[k][on];
		for(int i = 0; i < len; i += h) {
			ll x, y;
			for(int j = i; j < i + h/2; ++j) 
				x = s[j], y = pw[k][j][on] * s[j+h/2] % mod,
				s[j] = (x + y) % mod,
				s[j+h/2] = (x - y + mod) % mod;	
		}
	}
	if(!on) {
		ll in = pow(len, mod - 2);
		for(int i = 0; i < len; ++i) (s[i] *= in) %= mod;
	}
}

struct poly {
	int len;
	ll s[maxn];
	
	poly inv();
	poly(int x = 0): len(x) { memset(s, 0, sizeof(s)); }
	poly(ll *a, int x): len(x) {
		memset(s, 0, sizeof(s));
		for(int i = 0; i < len; ++i) s[i] = a[i];
	}
	ll &operator [](int x) { return s[x]; }
} G, H;


poly poly::inv() {
	static ll A[maxn], B[maxn];
	A[0] = pow(s[0], mod - 2);
	for(int i = 2; i <= len; i <<= 1) {
		int k = i << 1;
		for(int j = i>>1; j < k; ++j) A[j] = B[j] = 0;
		for(int j = 0; j < i; ++j) B[j] = s[j];
		FFT(A, k, 1), FFT(B, k, 1);
		for(int j = 0; j < k; ++j)
			A[j] = ((A[j]*2 - A[j]*A[j]%mod*B[j]%mod)%mod + mod) % mod;
		FFT(A, k, 0);
	}
	return poly(A, len);
}

int n, m, l;
poly operator ^(poly &a, int k) {
	static poly ret(a.len), x = a; ret[0] = 1;
	int len = x.len << 1;
	for(; k; k >>= 1) {
	 	FFT(x.s, len, 1);
		if(k & 1) {
			FFT(ret.s, len, 1);
			for(int i = 0; i < len; ++i) (ret[i] *= x[i]) %= mod;
			FFT(ret.s, len, 0);
			for(int i = x.len; i < len; ++i) ret[i] = 0;
		}
		for(int i = 0; i < len; ++i) (x[i] *= x[i]) %= mod;
		FFT(x.s, len, 0);
		for(int i = x.len; i < len; ++i) x[i] = 0;
	}
	return ret;
}


int main() {
	n = read(), m = read(), G[0] = 1;
	for(int i = 1; i <= m; ++i) --G[read() - 1];
	for(int i = 1; i <= n; ++i) if(G[i] < 0) G[i] += mod;
	
	l = 1;
	while(l <= n) l <<= 1;
	G.len = l;
	
	precalc(l<<1);
	H = G.inv();
	H = H ^ n;
	printf("%lld\n", H[n - 1] * pow(n, mod-2) % mod);
	return 0;
}
