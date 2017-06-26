#include <cstdio>
using namespace std;
typedef long long ll;
 
const int N = 1e6+5;
 
int n, t, mod, cas;
ll f[N], g[N], h[N];
ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k & 1) (ret *= x) %= mod;
    return ret;
}
 
int main() {
    scanf("%d", &cas);
    while(cas--) {
        scanf("%d%d", &n, &mod);
     
        f[1] = 1, f[2] = 2;
        for(int i = 3; i <= n; ++i)
            f[i] = (f[i-1] * 2 + f[i-2]) % mod;
         
        for(int i = 1; i <= n; ++i) {
            h[i] = quickpow(f[i], mod - 2);
            for(int j = i * 2; j <= n; j += i) 
                (f[j] *= h[i]) %= mod;
        }
         
        g[0] = 1;
        for(int i = 1; i <= n; ++i)
            g[i] = g[i-1] * f[i] % mod;
             
        ll ans = 0;
        for(int i = 1; i <= n; ++i)
            (ans += i * g[i]) %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}