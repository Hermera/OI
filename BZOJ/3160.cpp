#include <cstdio>
#include <complex>
#include <cstring>
using namespace std;
typedef long long ll;
typedef complex<double> CPN;
 
const int maxn = 4e5+5;
const int mod = 1e9+7;
const double pi = acos(-1);
 
 
void rev(CPN *a, int len) {
    for(int i = 0, t = 0; i < len; ++i) {
        if(i > t) swap(a[i], a[t]);
        for(int j = len>>1; (t ^= j) < j; j >>= 1);
    }
}
 
void FFT(CPN *a, int len, int on) {
    rev(a, len);
    for(int h = 2; h <= len; h <<= 1) {
        CPN wn = CPN(cos(-on*2*pi/h), sin(-on*2*pi/h));
        for(int i = 0; i < len; i += h) {
            CPN w = CPN(1, 0), x, y;
            for(int j = i; j < i+h/2; ++j) {
                x = a[j], y = a[j+h/2] * w;
                a[j] = x + y, a[j+h/2] = x - y;
                w = wn * w;
            }
        }
    }
    if(on < 0) {
        for(int i = 0; i < len; ++i)
            a[i].real() /= len;
    }
}
 
ll quickpow(ll x, ll k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod) 
        if(k & 1) (ret *= x) %= mod;
    return ret;
}
 
 
char str[maxn];
CPN a[maxn];
int n, m, f[maxn];
 
ll getseq(char ch) {
    for(int i = 0; i < m; ++i) a[i] = CPN(0, 0);
    for(int i = 0; i < n; ++i) a[i] = str[i] == ch;
     
    FFT(a, m, 1);
    for(int i = 0; i < m; ++i) a[i] *= a[i];
    FFT(a, m, -1);
     
    for(int i = 0; i < m; ++i) 
        f[i] += (round(a[i].real())+1) / 2;
}
 
 
int p[maxn];
ll manacher(char *str) {
    for(int i = n; ~i; --i) 
        str[i+i+2] = str[i], str[i+i+1] = '#';
    str[0] = '*';
     
    int j = 0, mx = 0;
    for(int i = 2; i <= (n<<1); ++i) {
        if(mx <= i) p[i] = 1;
        else p[i] = min(p[2*j-i], mx-i);
        while(str[i+p[i]] == str[i-p[i]]) ++p[i];
        if(mx < p[i]+i) j = i, mx = p[i]+i;
    }
     
    ll ret = 0;
    for(int i = 2; i <= (n<<1); ++i)
        (ret += (p[i] >> 1)) %= mod;
    return ret;
}
 
int main() {
    scanf("%s", str);
    n = strlen(str), m = 1;
    while(m <= n) m <<= 1; m <<= 1;
     
    getseq('a');
    getseq('b');
     
    ll ans = 0;
    for(int i = 0; i < m; ++i)
        (ans += quickpow(2, f[i]) - 1) %= mod;
    (ans -= manacher(str)) %= mod;
    (ans += mod) %= mod;
    printf("%lld\n", ans);
    return 0;
}