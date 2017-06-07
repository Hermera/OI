#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6+5;
const double pi = acos(-1);
struct Complex {
	double r, i;
	Complex(double r = 0.0, double i = 0.0): r(r), i(i) {};
	Complex operator +(const Complex &b) const { return Complex(r+b.r, i+b.i); }
	Complex operator -(const Complex &b) const { return Complex(r-b.r, i-b.i); }
	Complex operator *(const Complex &b) const { return Complex(r*b.r-i*b.i, r*b.i+i*b.r); }
} a[maxn], b[maxn], c[maxn], d[maxn], r[maxn<<1], *e = r+maxn;
int N, L, Log, rev[maxn];
double x[maxn];

void FFT(Complex *x, int dir) {
	Complex u, v;
	for(int i = 0; i < L; ++i)
		if(rev[i] > i) swap(x[i], x[rev[i]]);
		
	for(int h = 2; h <= L; h <<= 1, dir >>= 1)
		for(int i = 0; i < L; i += h)
			for(int k = i, d = 0; k < i+(h>>1); ++k, d += dir) 
				u = x[k], v = e[d]*x[k+(h>>1)], x[k] = u+v, x[k+(h>>1)] = u-v;			
}

void Multiply(Complex *ans, Complex *x, Complex *y, int L) {
	FFT(x, L>>1), FFT(y, L>>1);
	for(int i = 0; i < L; ++i) ans[i] = x[i]*y[i];
	FFT(ans, -(L>>1));
	for(int i = 0; i < L; ++i) (ans[i].r += 0.5) /= L;
}

void init(int &n) {
	while(n != (n&-n)) n += n&-n; n <<= 1;
	for(int i = n; i > 1; i >>= 1) ++Log;
	
	Complex R = Complex(cos(2*pi/n), sin(2*pi/n));
	e[0] = Complex(1, 0);
	for(int i = 1; i < n; ++i) e[i] = e[i-1]*R;
	for(int i = 1; i < n; ++i) e[-i] = e[n-i];
	for(int i = 0; i < n; ++i)
		for(int k = 0; k < Log; ++k)
			if(i&(1<<k)) rev[i] += 1<<(Log-k-1);
}
	
int main() {
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) 
		scanf("%lf", &x[i]);
	
	init(L = N);
	for(int i = 0; i < N; ++i) a[i] = Complex(x[i]);
	for(int i = 1; i < N; ++i) b[i] = Complex(1.0/i/i);
	Multiply(c, a, b, L);
	
	for(int i = 0; i < L; ++i) a[i] = b[i] = Complex();
	for(int i = 0; i < N; ++i) a[i] = Complex(x[N-i-1]);
	for(int i = 1; i < N; ++i) b[i] = Complex(1.0/i/i);
	Multiply(d, a, b, L);
	
	for(int i = 0; i < N; ++i) printf("%.3lf\n", c[i].r - d[N-i-1].r);
	return 0;
}
