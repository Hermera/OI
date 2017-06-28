#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int N = 3e5+5;
const int LIM = 100;
const double pi = acos(-1.0);
 
 
struct Atom {
    double r, i;
    Atom() {}
    Atom(double x, double y = 0): r(x), i(y) {}
} A[N], B[N];
 
Atom operator +(Atom a, Atom b) { return Atom(a.r+b.r, a.i+b.i); }
Atom operator -(Atom a, Atom b) { return Atom(a.r-b.r, a.i-b.i); }
Atom operator *(Atom a, Atom b) {
    return Atom(a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r);
}
 
 
void FFT(Atom *s, int l, int on) {
    for(int i = 0, t = 0; i < l; ++i) {
        if(i > t) swap(s[i], s[t]);
        for(int j = l>>1; (t ^= j) < j; j >>= 1);
    }
     
    for(int h = 2; h <= l; h <<= 1) {
        Atom wn = Atom(cos(-2*on*pi/h), sin(-2*on*pi/h));
        for(int i = 0; i < l; i += h) {
            Atom w(1, 0), x, y;
            for(int j = i; j < i+h/2; ++j) {
                x = s[j], y = w * s[j+h/2];
                s[j] = x + y, s[j+h/2] = x - y;
                w = w * wn;
            }
        }
    }
     
    if(on < 0) 
        for(int i = 0; i < l; ++i)
            s[i].r /= l;
}
 
 
 
int n, m, c;
ll a[N], b[N], ans[N];
 
void solve(int l, int r) {
    if(r-l <= LIM) {
        for(int i = l; i < r; ++i)
            for(int j = i+1; j < r; ++j)
                ans[i+j] += a[i] * b[j];
        return;
    }
     
    int k = r - l;
    int d = (l + r) >> 1;
    for(int i = 0; i < k; ++i) A[i] = B[i] = Atom(0);
    for(int i = l; i < d; ++i) A[i-l] = Atom(a[i]);
    for(int i = d; i < r; ++i) B[i-d] = Atom(b[i]);
     
    FFT(A, k, 1), FFT(B, k, 1);
    for(int i = 0; i < k; ++i) A[i] = A[i] * B[i];
    FFT(A, k, -1);
     
    for(int i = 0; i < k; ++i)
        ans[i + l + d] += round(A[i].r);
     
    solve(l, d);
    solve(d, r);
}
 
void solve() {
    c = 50000;
    m = 1 << 16;
    n = 1 << 17;
     
    for(int i = 0; i < n; ++i) A[i] = B[i] = Atom(0);
    for(int i = 0; i <= c; ++i) A[i] = Atom(a[i]);
    for(int i = 0; i <= c; ++i) B[i] = Atom(b[c-i]);
     
    FFT(A, n, 1), FFT(B, n, 1);
    for(int i = 0; i < n; ++i) A[i] = A[i] * B[i];
    FFT(A, n, -1);
     
    for(int i = c; i < n; ++i) 
        ans[i-c] += round(A[i].r);
    solve(0, m);
}
 
int cas, q;
int main() {
    cas = read();
    while(cas--) {
        n = read(), m = read(), q = read();
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(ans, 0, sizeof(ans));
         
        for(int i = 1; i <= n; ++i) ++a[read()];
        for(int i = 1; i <= m; ++i) ++b[read()];
         
        solve();
        while(q--) printf("%lld\n", ans[read()]);
    }
    return 0;
}

