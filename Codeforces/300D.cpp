#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int root = 3;
const int maxl = 35;
const int maxn = 1e4+5;
const int mod = 7340033;


ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k&1) (ret *= x) %= mod;
    return ret;
}

void rev(ll *s, int len) {
    for(int i = 0, t = 0; i < len; ++i) {
        if(i > t) swap(s[i], s[t]);
        for(int j = len>>1; (t ^= j) < j; j >>= 1);
    }
}

void NTT(ll *s, int len, int on) {
    rev(s, len);
    for(int h = 2; h <= len; h <<= 1) {
        ll wn = quickpow(root, on ? (mod-1)/h : mod-1 - (mod-1)/h);
        for(int j = 0; j < len; j += h) {
            ll w = 1, x, y;
            for(int k = j; k < j+h/2; ++k, (w *= wn) %= mod)
                x = s[k], y = (w*s[k+h/2]) % mod,
                s[k] = (x+y) % mod, s[k+h/2] = (x-y+mod) % mod;
        }
    }
    if(!on) {
        ll inv = quickpow(len, mod-2);
        for(int i = 0; i < len; ++i) (s[i] *= inv) %= mod;
    }
}


int q, n = 1024;
ll dp[maxl][maxn], a[maxn];

void square(ll *a, int len) {
    NTT(a, len, 1);
    for(int i = 0; i < len; ++i) a[i] = a[i]*a[i] % mod;
    NTT(a, len, 0);
}

int div(int n) {
    int ret = 0;
    while((n&1) && n > 1) ret++, n >>= 1;
    return ret;
}

int main() {
    dp[0][0] = 1;
    for(int i = 1; i < maxl; ++i) {
        for(int j = n<<2; j; --j) a[j] = 0;
        for(int j = 0; j < n; ++j) a[j] = dp[i-1][j];
        square(a, n<<1);
        square(a, n<<2);

        dp[i][0] = 1;
        for(int j = 1; j < n; ++j) dp[i][j] = a[j-1];
    }

    scanf("%d", &q);
    for(int x, k; q--; ) {
        scanf("%d%d", &x, &k);
        if(!k) printf("1\n");
        else if(~x & 1) printf("0\n");
        else printf("%lld\n", dp[div(x)][k]);
    }
    return 0;
}
