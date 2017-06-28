#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
 
const int N = 505;
const int M = 2e7+5;
const double pi = acos(-1.0);
 
 
int pri[M/10], t, m;
bool vis[M];
void getprime() {
    vis[1] = 1;
    for(int i = 2; i <= m; ++i) {
        if(!vis[i]) pri[++t] = i;
        for(int j = 1; j <= t && i*pri[j] <= m; ++j) {
            vis[i*pri[j]] = 1;
            if(i % pri[j] == 0) break;
        }
    }
}
 
 
struct Atom {
    double r, i;
    Atom() {}
    Atom(double _r, double _i): r(_r), i(_i) {}
};
 
Atom operator +(Atom a, Atom b) { return Atom(a.r+b.r, a.i+b.i); }
Atom operator -(Atom a, Atom b) { return Atom(a.r-b.r, a.i-b.i); }
Atom operator *(Atom a, Atom b) {
    return Atom(a.r*b.r - a.i*b.i, a.r*b.i + a.i*b.r);
}
 
 
int n, p, l, mod, rev[N];
void FFT(Atom *s, int on) {
    for(int i = 0; i < l; ++i)
        if(rev[i]) swap(s[i], s[rev[i]]);
    for(int h = 2; h <= l; h <<= 1) {
        Atom wn(cos(-on*2*pi/h), sin(-on*2*pi/h));
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
 
 
Atom A[N], B[N];
void mul(ll *c, ll *a, ll *b) {
    for(int i = 0; i < l; ++i) A[i] = Atom(a[i], 0);
    for(int i = 0; i < l; ++i) B[i] = Atom(b[i], 0);
    FFT(A, 1), FFT(B, 1);
    for(int i = 0; i < l; ++i) A[i] = A[i] * B[i];
    FFT(A, -1);
     
    for(int i = 0; i < l; ++i) c[i] = 0;
    for(int i = 0; i < l; ++i)
        (c[i%p] += round(A[i].r)) %= mod;
}
 
ll a[N], b[N], R[N];
ll quickpow(ll *A, int k) {
    memset(R, 0, sizeof(R)), R[0] = 1;
    for(; k; k >>= 1, mul(A, A, A)) 
        if(k & 1) mul(R, R, A);
    return R[0];
}
 
 
ll solve(int x) {
    mod = x;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for(int i = 1; i <= m; ++i) ++a[i%p];
    for(int i = 1; i <= m; ++i) if(vis[i]) ++b[i%p];
     
    ll ret1 = quickpow(a, n);
    ll ret2 = quickpow(b, n);
    return (ret1 - ret2 + mod) % mod;
}
 
 
 
ll exgcd(ll x, ll y, ll &a, ll &b) {
    if(!y) return a = 1, b = 0, x;
    int ret = exgcd(y, x%y, b, a);
    return b -= x/y*a, ret;
}
 
ll inv(ll x, ll y) {
    ll a, b, g = exgcd(x, y, a, b);
    if(g != 1) return -1;
    return a;
}
 
 
ll P[5], Q[5];
ll CRT(int k) {
    ll ret = 0, MOD = 1;
    for(int i = 1; i <= k; ++i) MOD *= Q[i];
    for(int i = 1; i <= k; ++i) {
        ll MI = MOD / Q[i];
        (ret += P[i] * MI % MOD * inv(MI, Q[i])) %= MOD;
    }
    return ret;
}
 
 
int main() {
    scanf("%d%d%d", &n, &m, &p);
     
    l = 1;
    while(l <= p) l <<= 1; l <<= 1;
    for(int i = 0, t = 0; i < l; ++i) {
        if(i > t) rev[i] = t;
        for(int j = l>>1; (t ^= j) < j; j >>= 1);
    }
     
    getprime();
    P[1] = solve(Q[1] = 8);
    P[2] = solve(Q[2] = 1091);
    P[3] = solve(Q[3] = 2311);
    printf("%lld\n", CRT(3));
    return 0;
}

