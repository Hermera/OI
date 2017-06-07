#include <cstdio>
#include <cmath>
#include <complex>
using namespace std;
typedef complex <double> cpx;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5;
const double pi = acos(-1.0);

cpx a[maxn], b[maxn], c[maxn];
int n, l;

void rev(cpx *s, int len) {
    for(int i = 0, t = 0; i < len; ++i) {
    	if(i > t) swap(s[i], s[t]);
    	for(int j = len>>1; (t ^= j) < j; j >>= 1);
    }
}

void FFT(cpx *s, int len, int on) {
	rev(s, len);
	for(int h = 2; h <= len; h <<= 1) {
		cpx wn(cos(-on*2*pi/h), sin(-on*2*pi/h));
		for(int j = 0; j < len; j += h) {
			cpx w(1, 0), x, y;
			for(int k = j; k < j+h/2; ++k)
				x = s[k], y = w*s[k+h/2],
				s[k] = x+y, s[k+h/2] = x-y, w = w*wn;
		}
	}
	if(on < 0) for(int i = 0; i < len; ++i) s[i].real() /= len;			
}

int main() {
	n = read(), l = 1;
	while(l <= n) l <<= 1; l <<= 1;
	for(int i = 0; i < n; ++i) a[n-i-1] = read(), b[i] = read();
	
	FFT(a, l, 1), FFT(b, l, 1);
	for(int i = 0; i < l; ++i) c[i] = a[i]*b[i];
	FFT(c, l, -1);
	
	for(int i = n-1; ~i; --i) printf("%d\n", (int)(c[i].real()+0.5));
	return 0;
}
