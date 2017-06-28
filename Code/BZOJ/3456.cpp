#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
const int root = 3;
const int mod = 1004535809;

ll pow(ll x, ll k) {
	ll ret = 1;
	for(; k; k >>= 1, (x *= x) %= mod)
		if(k & 1) (ret *= x) %= mod;
	return ret;
}

void rev(ll *s, int len) {
	for(int i = 0, t = 0; i < len; ++i) {
		if(i > t) swap(s[i], s[t]);
		for(int j = len>>1; (t ^= j) < j; j >>= 1);
	}
}

void FFT(ll *s, int len, int on) {
	rev(s, len);
	for(int h = 2; h <= len; h <<= 1) {
		ll wn = pow(root, on ? (mod-1)/h : mod-1 - (mod-1)/h);
		for(int i = 0; i < len; i += h) {
			ll w = 1, x, y;
			for(int j = i; j < i + h/2; ++j)
				x = s[j], y = w * s[j+h/2] % mod,
				s[j] = (x + y) % mod,
				s[j+h/2] = (x - y + mod) % mod,
				w = w * wn % mod;
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
	poly() { memset(s, 0, sizeof(s)); }
	poly inv();
	poly(ll *a, int l): len(l) {
		memset(s, 0, sizeof(s));
		for(int i = 0; i < len; ++i) s[i] = a[i];
	}
	
	ll &operator [](int x) { return s[x]; }
} F, G, H, K;

poly operator *(poly &a, poly &b) {
	int len = max(a.len, b.len)<<1;
	static ll A[maxn], B[maxn], C[maxn];
	for(int i = 0; i < a.len; ++i) A[i] = a[i];
	for(int i = 0; i < b.len; ++i) B[i] = b[i];
	
	FFT(A, len, 1), FFT(B, len, 1);
	for(int i = 0; i < len; ++i) C[i] = A[i] * B[i] % mod;
	FFT(C, len, 0);
	return poly(C, len>>1);
}


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

int n, m = 1;
ll fac[maxn], inv[maxn], sum[maxn];

int main() {
	scanf("%d", &n);
		
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
	for(int i = 0; i <= n; ++i) inv[i] = pow(fac[i], mod - 2);
	for(int i = 0; i <= n; ++i) sum[i] = pow(2, 1LL*i*(i-1)>>1);
	
	while(m <= n) m <<= 1;
	G.len = H.len = F.len = m;
	for(int i = 0; i <= n; ++i) G[i] = sum[i] * inv[i-1] % mod;
	for(int i = 0; i <= n; ++i) H[i] = sum[i] * inv[i] % mod;
	H = H.inv();
	F = G * H;
	
	printf("%lld\n", F[n] * fac[n-1] % mod);
	return 0;
}
