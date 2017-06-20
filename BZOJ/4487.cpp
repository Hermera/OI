#include <cstdio>
using namespace std;
typedef long long ll;

const int N = 405;
const int mod = 1e9+7;

ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k & 1) (ret *= x) %= mod;
    return ret;
}

int rev(int x) {
    return x&1 ? -1 : 1;
}

int n, m, c;
ll co[N][N], ans;

int main() {
    n = 400;
    for(int i = 0; i <= n; ++i) co[i][0] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            co[i][j] = (co[i-1][j-1] + co[i-1][j]) % mod;
    scanf("%d%d%d", &n, &m, &c);
    for(int i = 0; i <= n; ++i)
        for(int k = 0; k <= c; ++k) {
            ll ret = co[n][i] * co[c][k] % mod;
            ll tmp = 1 - quickpow(k+1, i);
            (ret *= quickpow(tmp, m)) %= mod;
            (ret *= rev(n+m+c-i-k)) %= mod;
            (ans += ret) %= mod;
        }

    (ans += mod) %= mod;
    printf("%lld\n", ans);
    return 0;
}
