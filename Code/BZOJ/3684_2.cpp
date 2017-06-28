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

ll pwn[maxl][2], pw[maxl][maxn][2], ifac[maxn];
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
		ll in = ifac[len];
		for(int i = 0; i < len; ++i) (s[i] *= in) %= mod;
	}
}


ll G[maxn], I[maxn], L[maxn], E[maxn];
void GetInv(ll *A, ll *B, int len) {
	static ll C[maxn];
	B[0] = pow(A[0], mod - 2);
	for(int i = 2; i <= len; i <<= 1) {
		int k = i << 1;
		for(int j = i; j < k; ++j) B[j] = C[j] = 0;
		for(int j = 0; j < i; ++j) C[j] = A[j];
		FFT(B, k, 1), FFT(C, k, 1);
		for(int j = 0; j < k; ++j)
			B[j] = ((B[j]*2 - B[j]*B[j]%mod*C[j]%mod)%mod + mod) % mod;
		FFT(B, k, 0);
		for(int j = i; j < k; ++j) B[j] = C[j] = 0;
	}
}

void GetLnn(ll *A, ll *B, int len) {
	static ll C[maxn], D[maxn];
	GetInv(A, C, len);
	for(int i = 0; i < len - 1; ++i)
		D[i] = A[i+1] * (i+1) % mod;
	int k = len << 1;
	FFT(C, k, 1), FFT(D, k, 1);
	for(int i = 0; i < k; ++i) B[i] = C[i] * D[i] % mod;
	FFT(B, k, 0);
	for(int i = len-1; i; --i) B[i] = B[i-1] * ifac[i] % mod;
	for(int i = len; i < k; ++i) B[i] = 0; B[0] = 0;
	memset(C, 0, sizeof(C[0])*k);
	memset(D, 0, sizeof(D[0])*k);
}

void GetExp(ll *A, ll *B, int len) {
	static ll C[maxn];
	B[0] = 1;
	for(int i = 2; i <= len; i <<= 1) {
		int k = i<<1;
		memset(C, 0, sizeof(C[0])*k);
		GetLnn(B, C, i);
		
		for(int j = 0; j < i; ++j) 
			C[j] = (A[j] - C[j] + (j == 0) + mod) % mod;
		FFT(B, k, 1), FFT(C, k, 1);
		for(int j = 0; j < k; ++j) (B[j] *= C[j]) %= mod;
		FFT(B, k, 0);
		for(int j = i; j < k; ++j) B[j] = 0;
	}
}


int n, m, l;
int main() {
	n = read(), m = read(), G[0] = 1;
	for(int i = 1; i <= m; ++i) --G[read() - 1];
	for(int i = 1; i <= n; ++i) if(G[i] < 0) G[i] += mod;
	
	l = 1;
	while(l <= n) l <<= 1;
	ifac[1] = 1;
	for(int i = 2; i <= l<<1; ++i)
		ifac[i] = (mod - mod/i)*ifac[mod%i]%mod;
	
	precalc(l<<1);
	GetInv(G, I, l);
	GetLnn(I, L, l);
	for(int i = 0; i < l; ++i) (L[i] *= n) %= mod;
	GetExp(L, E, l);
	
	printf("%lld\n", E[n - 1] * pow(n, mod-2) % mod);
	return 0;
}
