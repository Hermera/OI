#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
 
const int N = 1e6+5;
const int mod = 1e9+7;
 
int quickpow(int x, int k) {
    int ret = 1;
    for(; k; k >>= 1, x = 1LL * x * x % mod)
        if(k & 1) ret = 1LL * ret * x % mod;
    return ret;
}
 
 
int t, n, m, mob[N], vis[N], pri[N];
int fun[N], inv[N], val[N], sum[N], isu[N];
 
void prepare() {
    n = 1e6, mob[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) pri[++t] = i, mob[i] = -1;
        for(int j = 1; j <= t && i*pri[j] <= n; ++j) {
            vis[i*pri[j]] = 1;
            if(i % pri[j]) mob[i*pri[j]] = -mob[i];
            else break;
        }
    }
     
    fun[1] = 1;
    for(int i = 2; i <= n; ++i) fun[i] = (fun[i-1] + fun[i-2]) % mod;
    for(int i = 1; i <= n; ++i) inv[i] = quickpow(fun[i], mod - 2);
    for(int i = 1; i <= n; ++i) val[i] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; j += i) {
            if(mob[j/i] < 0) val[j] = 1LL * val[j] * inv[i] % mod;
            if(mob[j/i] > 0) val[j] = 1LL * val[j] * fun[i] % mod;
        }
     
    sum[0] = isu[0] = 1;
    for(int i = 1; i <= n; ++i) sum[i] = 1LL * sum[i-1] * val[i] % mod;
    for(int i = 1; i <= n; ++i) isu[i] = quickpow(sum[i], mod - 2);
}
 
int cas;
int main() {
    prepare();
     
    scanf("%d", &cas);
    while(cas--) {
        scanf("%d%d", &n, &m);
        if(n > m) swap(n, m);
         
        int ans = 1, ret;
        for(int l = 1, r; l <= n; l = r+1) {
            r = min(n/(n/l), m/(m/l));
             
            ret = 1LL * sum[r] * isu[l-1] % mod;
            ret = quickpow(ret, 1LL * (n/l) * (m/l) % (mod-1));
            ans = 1LL * ans * ret % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}
﻿
