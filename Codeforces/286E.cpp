#include <cmath>
#include <cstdio>
#include <complex>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int maxn = 5e6+5;
const double pi = acos(-1);
typedef complex <double> cpx;

int n, m, l = 1<<21;
int ans[maxn], back;
cpx a[maxn], b[maxn], c[maxn];

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
    n = read(), m = read();
    for(int i = 0; i < n; ++i) a[read()] = 1;
    for(int i = 0; i < l; ++i) c[i] = a[i];

    FFT(a, l, 1);
    for(int i = 0; i < l; ++i) b[i] = a[i]*a[i];
    FFT(b, l, -1);

    bool cannot = 0;
    for(int x, y, i = 1; i <= m; ++i) {
        x = round(b[i].real());
        y = round(c[i].real());
        if(!x && y) ans[++back] = i;
        if(x && !y) cannot = 1;
    }

    if(cannot) printf("NO\n");
    else {
        printf("YES\n");
        printf("%d\n", back);
        for(int i = 1; i <= back; ++i) printf("%d ", ans[i]);
    }
    return 0;
}
