#include <cmath>
#include <cstdio>
#include <algorithm>
#define double long double
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int N = 3e5+5;
const double pi = acosl(-1.0);

struct Atom {
    double r, i;
    Atom() {}
    Atom(double x, double y): r(x), i(y) {}
} A[N], B[N];

Atom operator +(Atom a, Atom b) { return Atom(a.r+b.r, a.i+b.i); }
Atom operator -(Atom a, Atom b) { return Atom(a.r-b.r, a.i-b.i); }
Atom operator *(Atom a, Atom b) { return Atom(a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r); }


void rev(Atom *a, int l) {
    for(int i = 0, t = 0; i < l; ++i) {
        if(i > t) swap(a[i], a[t]);
        for(int j = l>>1; (t ^= j) < j; j >>= 1);
    }
}

void FFT(Atom *a, int l, int on) {
    rev(a, l);
    for(int h = 2; h <= l; h <<= 1) {
        Atom wn(cos(-2*on*pi/h), sin(-2*on*pi/h));
        for(int i = 0; i < l; i += h) {
            Atom w(1, 0), x, y;
            for(int j = i; j < i+h/2; ++j) {
                x = a[j], y = a[j+h/2] * w;
                a[j] = x + y, a[j+h/2] = x - y;
                w = w * wn;
            }
        }
    }
    if(on < 0)
        for(int i = 0; i < l; ++i)
            a[i].r /= l;
}

int n, m, l, cas, a[N];
ll ans[N], fac[N];

void multify(Atom *a, Atom *b) {
    FFT(a, l, 1), FFT(b, l, 1);
    for(int i = 0; i < l; ++i) a[i] = a[i] * b[i];
    FFT(a, l, -1);
}

int main() {
    cas = read();
    while(cas--) {
        n = read();
        for(int i = 1; i <= n; ++i) a[i] = read();
        for(int i = 1; i <= n; ++i) a[i] += a[i-1];

        m = a[n], l = 1;
        while(l <= m) l <<= 1; l <<= 1;
        for(int i = 0; i <= m; ++i) ans[i] = 0;

        for(int i = 0; i < l; ++i) A[i] = B[i] = Atom(0, 0);
        for(int i = 1; i <= n; ++i) A[ a[i] ].r += i;
        for(int i = 0; i <  n; ++i) B[m-a[i]].r += 1;
        multify(A, B);
        for(int i = 0; i <= m; ++i) ans[i] += round(A[m+i].r);

        for(int i = 0; i < l; ++i) A[i] = B[i] = Atom(0, 0);
        for(int i = 1; i <= n; ++i) A[ a[i] ].r += 1;
        for(int i = 0; i <  n; ++i) B[m-a[i]].r += i;
        multify(A, B);
        for(int i = 0; i <= m; ++i) ans[i] -= round(A[m+i].r);

        ll ans0 = 0;
        for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] + 1LL * i * (i+1) / 2;
        for(int l = 1, r = 0; l <= n; l = r+1)
            if(a[l] == a[l-1]){
                for(r = l; r < n && a[r+1] == a[l]; ++r);
                ans0 += fac[r-l+1];
            } else r = l;
        printf("%lld\n", ans0);

        for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    }
    return 0;
}
