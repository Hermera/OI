#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
 
const int maxn = 505;
const int mod = 1e9+7;
const int maxk = 2e6+5;
 
int A, B, C, D, E, F, n, m, k;
struct Atom {
    int x, y;
    bool operator <(const Atom &b) const {
        return x != b.x ? x < b.x : y < b.y;
    }
     
    bool change() {
        int x1 = (x*D - C*y), x2 = (A*D - B*C);
        int y1 = (x*B - y*A), y2 = (B*C - A*D);
        if(x1 % x2 || y1 % y2) return 0;
        if(x1*x2 < 0 || y1*y2 < 0) return 0;
        return x = x1/x2, y = y1/y2, 1;
    }
} p[maxn], a[maxn], tar;
 
 
ll fac[maxk], inv[maxk];
ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod) 
        if(k & 1) (ret *= x) %= mod;
    return ret;
}
 
 
ll Comb(int n, int m) {
    if(n < 0 || m < 0 || n < m) return 0;
    return fac[n] * inv[n-m] % mod * inv[m] % mod;
}
 
ll sum(Atom a, Atom b) {
    return Comb(b.x-a.x + b.y-a.y, b.x-a.x);
}
 
ll dp[maxn][2];
ll solve() {
    if(!tar.change()) return 0; 
    sort(a+1, a+1+m);
     
    dp[0][0] = 1;
    for(int i = 1; i <= m; ++i)
    for(int j = 0; j < i; ++j)   
        if(a[j].x <= a[i].x && a[j].y <= a[i].y)
            (dp[i][0] += dp[j][1] * sum(a[j], a[i])) %= mod,
            (dp[i][1] += dp[j][0] * sum(a[j], a[i])) %= mod;
     
    ll ans0 = 0, ans1 = 0;
    for(int i = 0; i <= m; ++i)
        (ans0 += dp[i][0] * sum(a[i], tar)) %= mod,
        (ans1 += dp[i][1] * sum(a[i], tar)) %= mod;
    return ((ans0 - ans1)%mod + mod) % mod;
}
 
void input() {
    scanf("%d%d%d", &tar.x, &tar.y, &n);
    scanf("%d%d%d%d", &A, &B, &C, &D);
     
    for(int i = 1; i <= n; ++i)
        scanf("%d%d", &p[i].x, &p[i].y);
    for(int i = 1; i <= n; ++i)
        if(p[i].change()) a[++m] = p[i];
         
    k = 2e6;
    fac[0] = 1;
    for(int i = 1; i <= k; ++i) fac[i] = fac[i-1] * i % mod;
    inv[k] = quickpow(fac[k], mod-2);
    for(int i = k-1; ~i; --i) inv[i] = inv[i+1] * (i+1) % mod;
}
 
int main() {
    input();
    printf("%lld\n", solve());
    return 0;
}