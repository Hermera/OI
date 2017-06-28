#include <cmath>
#include <cstdio>
#include <complex>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int N = 2e5+5;
const int K = 18;
const double pi = acos(-1.0);
 
 
int n, m, t, b, a[N], L[N], R[N];
long long ans;
 
struct Atom {
    double r, i;
    Atom() {}
    Atom(double _r, double _i): r(_r), i(_i) {}
} A[N], B[N];
 
Atom operator +(Atom a, Atom b) { return Atom(a.r+b.r, a.i+b.i); }
Atom operator -(Atom a, Atom b) { return Atom(a.r-b.r, a.i-b.i); }
Atom operator *(Atom a, Atom b) { return Atom(a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r); }
 
 
int rev[N];
void FFT(Atom *s, int on) {
    for(int i = 0; i < m; ++i)
        if(rev[i]) swap(s[i], s[rev[i]]);
     
    for(int h = 2; h <= m; h <<= 1) {
        Atom wn(cos(-2*on*pi/h), sin(-2*on*pi/h));
        for(int i = 0; i < m; i += h) {
            Atom w(1, 0), x, y;
            for(int j = i; j < i+h/2; ++j) {
                x = s[j], y = s[j+h/2] * w;
                s[j] = x + y, s[j+h/2] = x - y;
                w = w * wn;
            }
        }
    }
 
    if(on < 0) {
        for(int i = 0; i < m; ++i)   
            s[i].r /= m;
    }
}
 
 
void FFT_prepare() {
    m = 1;
    while(m <= t) m <<= 1; m <<= 1;
    for(int i = 0; i < m; ++i) rev[i] = 0;
    for(int i = 0, k = 0; i < m; ++i) {
        if(i > k) rev[i] = k;
        for(int j = m>>1; (k ^= j) < j; j >>= 1);
    }
}
 
 
int main() {
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) t = max(t, a[i]);
 
    FFT_prepare();
     
    b = min(n, int(sqrt(n) * 6));
    for(int i = 1; i <= n; ++i) ++R[a[i]];
    for(int i = 1; i <= n; i += b) {
        int l = i, r = min(i+b-1, n);
         
        for(int j = l; j <= r; ++j) --R[a[j]];
        for(int j = l; j <= r; ++j) {
            for(int k = j+1, v; k <= r; ++k) {
                if((v = 2*a[j] - a[k]) >= 0) ans += L[v];
                if((v = 2*a[k] - a[j]) >= 0) ans += R[v];
            }
            ++L[a[j]]; // two numbers both in blocks
        }
    }
         
    for(int i = 1; i <= n; i += b) {
        int l = i, r = min(i+b-1, n);
        for(int j = 0; j < m; ++j) L[j] = R[j] = 0;
        for(int j = 1; j < l; ++j) ++L[a[j]];
        for(int j = n; j > r; --j) ++R[a[j]];
         
        for(int j = 0; j < m; ++j) A[j] = B[j] = Atom(0, 0);
        for(int j = 0; j < m; ++j) A[j] = Atom(L[j], 0);
        for(int j = 0; j < m; ++j) B[j] = Atom(R[j], 0);
         
        FFT(A, 1), FFT(B, 1);
        for(int j = 0; j < m; ++j) A[j] = A[j] * B[j];
        FFT(A, -1);
         
        for(int j = l; j <= r; ++j)
            ans += (long long)(A[a[j]<<1].r + 0.5);
    }
     
    printf("%lld\n", ans);
    return 0;
}