#include <cstdio>
using namespace std;
typedef long long ll;
 
const int N = 1e6+5;
 
int n, t, mod;
int vis[N], mob[N], p[N];
void prepare() {
    n = 1e6, mob[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) p[++t] = i, mob[i] = -1;
        for(int j = 1; j <= t && i*p[j] <= n; ++j) {
            vis[i*p[j]] = 1;
            if(!(i % p[j])) {
                mob[i*p[j]] = 0;
                break;
            } else mob[i*p[j]] = -mob[i];
        }
    }
}
 
int cas;
ll fuc[N], inv[N], g[N], h[N];
ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k & 1) (ret *= x) %= mod;
    return ret;
}
 
int main() {
    prepare();
 
    scanf("%d", &cas);
    while(cas--) {
        scanf("%d%d", &n, &mod);
     
        fuc[1] = 1, fuc[2] = 2;
        for(int i = 3; i <= n; ++i)
            fuc[i] = (fuc[i-1] * 2 + fuc[i-2]) % mod;
        for(int i = 1; i <= n; ++i) 
            inv[i] = quickpow(fuc[i], mod - 2);
             
        for(int i = 1; i <= n; ++i) h[i] = 1;
        for(int i = 1; i <= n; ++i)
            for(int j = i; j <= n; j += i) {
                if(mob[j/i] > 0) (h[j] *= fuc[i]) %= mod;
                if(mob[j/i] < 0) (h[j] *= inv[i]) %= mod;
            }
         
        g[0] = 1;
        for(int i = 1; i <= n; ++i)
            g[i] = g[i-1] * h[i] % mod;
             
        ll ans = 0;
        for(int i = 1; i <= n; ++i)
            (ans += i * g[i]) %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}