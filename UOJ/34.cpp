#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}


const int N = 5e5+5;
const double pi = acos(-1.0);

int n, m, l;
struct Atom {
    double r, i;
    Atom() {}
    Atom(double _r, double _i = 0): r(_r), i(_i) {}
} A[N], B[N];
Atom operator +(Atom a, Atom b) { return Atom(a.r+b.r, a.i+b.i); }
Atom operator -(Atom a, Atom b) { return Atom(a.r-b.r, a.i-b.i); }
Atom operator *(Atom a, Atom b) {
    return Atom(a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r);
}


void FFT(Atom *s, int on) {
    for(int i = 0, t = 0; i < l; ++i) {
        if(i > t) swap(s[i], s[t]);
        for(int j = l>>1; (t ^= j) < j; j >>= 1);
    }

    for(int h = 2; h <= l; h <<= 1) {
        Atom wn(cos(-2*on*pi/h), sin(-2*on*pi/h));
        for(int i = 0; i < l; i += h) {
            Atom w(1, 0), x, y;
            for(int j = i; j < i+h/2; ++j) {
                x = s[j], y = w * s[j+h/2];
                s[j] = x+y, s[j+h/2] = x-y;
                w = w * wn;
            }
        }
    }

    if(on < 0)
        for(int i = 0; i < l; ++i)
            s[i].r /= l;
}


int a[N], b[N], c[N];
int main() {
    freopen("34.in", "r", stdin);

    n = read(), m = read();
    for(int i = 0; i <= n; ++i) a[i] = read();
    for(int i = 0; i <= m; ++i) b[i] = read();

    l = 1;
    while(l <= max(n, m)) l <<= 1;
    l <<= 1;

    for(int i = 0; i < l; ++i) A[i] = Atom(a[i]);
    for(int i = 0; i < l; ++i) B[i] = Atom(b[i]);
    FFT(A, 1), FFT(B, 1);
    for(int i = 0; i < l; ++i) A[i] = A[i] * B[i];
    FFT(A, -1);

    for(int i = 0; i <= n+m; ++i) c[i] = round(A[i].r);
    for(int i = 0; i <= n+m; ++i) printf("%d ", c[i]);
    printf("\n");
    return 0;
}
