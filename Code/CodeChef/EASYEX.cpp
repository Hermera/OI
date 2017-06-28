#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 2e5+5;
const int maxf = 1005;
const int maxl = 18;
const int mod = 2003;
const double pi = acos(-1);

int N, K, L, F, M, P, cas, fac[maxn], inv[maxn];
struct cpx {
	double x, y;
	cpx(double a = 0, double b = 0): x(a), y(b) {}
} A[maxn], B[maxn];
cpx operator +(cpx a, cpx b) { return cpx(a.x+b.x, a.y+b.y); }
cpx operator -(cpx a, cpx b) { return cpx(a.x-b.x, a.y-b.y); }
cpx operator *(cpx a, cpx b) { return cpx(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x); }

int quickpow(int x, int k) {
	int ret = 1;
	for(; k; k >>= 1) {
		if(k & 1) (ret *= x) %= mod;
		(x *= x) %= mod;
	}
	return ret;
}

int C(int n, int m) { return fac[n] * inv[m] % mod * inv[n-m] % mod; }
int Lucas(int n, int m) {
	if(n == m || !m) return 1;
	if(n < m) return 0;
	return Lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}

int rev[maxn];
cpx pw[maxl][maxn][2];
void FFT(cpx *s, int len, int on) {
    for(int i = 0; i < len; ++i) if(rev[i]) swap(s[i], s[rev[i]]);
    
    cpx x, y;
    for(int h = 2, l = 0; h <= len; h <<= 1, ++l) 
        for(int j = 0; j < len; j += h) 
            for(int k = j; k < j+h/2; ++k)
                x = s[k], y = pw[l][k][on]*s[k+h/2],
                s[k] = x+y, s[k+h/2] = x-y;
    if(!on) for(int i = 0; i < len; ++i) s[i].x /= len;           
}

void mul(int *x, int *y) {
	for(int i = 0; i < M; ++i) A[i] = B[i] = cpx(0, 0);
	for(int i = 0; i <= N; ++i) A[i] = cpx(x[i], 0);
	for(int i = 0; i <= N; ++i) B[i] = cpx(y[i], 0);
	FFT(A, M, 1), FFT(B, M, 1);
	for(int i = 0; i < M; ++i) A[i] = A[i] * B[i];
	FFT(A, M, 0);
	for(int i = 0; i <= N; ++i) x[i] = round(A[i].x);
	for(int i = 0; i <= N; ++i) x[i] %= mod;
}

int f[maxf][maxf], x[maxn], y[maxn];
int solve() {
	scanf("%d%d%d%d", &P, &K, &L, &F);
	if(!(K % mod)) return 0;
	
	N = L*F, M = 1;
	while(M <= N) M <<= 1; M <<= 1;
	for(int i = 0; i < M; ++i) rev[i] = 0;
    for(int i = 0, t = 0; i < M; ++i) {
        if(i > t) rev[i] = t;
        for(int j = M>>1; (t ^= j) < j; j >>= 1);
    }
    for(int h = 2, l = 0; h <= M; h <<= 1, ++l) {
        cpx wn1(cos(-2*pi/h), sin(-2*pi/h));
        cpx wn0(cos(2*pi/h),  sin(2*pi/h));
        for(int j = 0; j < M; j += h) {
            cpx w1(1, 0), w0(1, 0);
            for(int k = j; k < j+h/2; ++k)
            	pw[l][k][1] = w1,
            	pw[l][k][0] = w0,
            	w1 = w1*wn1,
            	w0 = w0*wn0;
        }
    }
	
	for(int i = 0; i < M; ++i) x[i] = y[i] = 0;
	if(F == 1) x[L] = 1;
	else {
		x[0] = 1;
		for(int i = 1; i <= F; ++i) y[i] = f[F][i];
		for(; L; L >>= 1) {
			if(L & 1) mul(x, y);
			mul(y, y);
		}
	}

	int ans = 0, now = 1;
	int moc = quickpow(K % mod, mod - 2);
	for(int i = 1; i <= N; ++i) {
		(now *= moc) %= mod;
		(ans += x[i] * Lucas(P, i) % mod * fac[i] % mod * now) %= mod;
	}
	return (ans + mod) % mod;
}


int main() {
	N = 50000, F = 1000;
	
	fac[0] = 1;
	for(int i = 1; i <= N; ++i) fac[i] = fac[i-1] * i % mod;
	for(int i = 0; i <= N; ++i) inv[i] = quickpow(fac[i], mod - 2);
	
	f[0][0] = 1;
	for(int i = 1; i <= F; ++i)
	for(int j = 1; j <= i; ++j)
		f[i][j] = (f[i-1][j]*j + f[i-1][j-1]) % mod;
	
	scanf("%d", &cas);
	while(cas--) printf("%d\n", solve());
	return 0;
}
