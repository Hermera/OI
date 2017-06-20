#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int N = 2e5+5;
const int M = 4005;
const int mod = 1e9+7;

int n, m, a[N], b[N];
ll fac[N], inv[N];
struct Map {
    int val[M][M];
    int &operator ()(int x, int y) {
        return val[x+m][y+m];
    }
} dp;

ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k & 1) (ret *= x) %= mod;
    return ret;
}

void update(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    if(x < 0) x += mod;
}

int combine(int n, int m) {
    ll ret = fac[n];
    (ret *= inv[m]) %= mod;
    (ret *= inv[n-m]) %= mod;
    return ret;
}


int main() {
    n = 1e4;
    fac[0] = 1;
    for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
    inv[n] = quickpow(fac[n], mod-2);
    for(int i = n-1; ~i; --i) inv[i] = inv[i+1] * (i+1) % mod;

    n = read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read(), b[i] = read();
        m = max(m, a[i]);
        m = max(m, b[i]);
    }

    for(int i = 1; i <= n; ++i) ++dp(-a[i], -b[i]);
    for(int i = -m; i <= m; ++i)
    for(int j = -m; j <= m; ++j)
        update(dp(i+1, j), dp(i, j)),
        update(dp(i, j+1), dp(i, j));

    int ans = 0;
    for(int i = 1; i <= n; ++i)
        update(ans, dp(a[i], b[i]));
    for(int i = 1; i <= n; ++i)
        update(ans, -combine(2*(a[i]+b[i]), a[i]+a[i]));
    ans = 1LL * ans * quickpow(2, mod-2) % mod;
    update(ans, mod);
    printf("%d\n", ans);
    return 0;
}
