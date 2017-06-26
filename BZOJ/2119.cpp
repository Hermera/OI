#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
inline int read() {
    char ch = getchar(); int x = 0, t = 1;
    while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int maxn = 5e4+5;
const int bin = 1e6+3;
 
int n, m, a[maxn], b[maxn];
ll pow[maxn], val[maxn];
 
ll getVal(int l, int r) { return val[r] - val[l-1] * pow[r-l+1]; }
 
int getLCP(int x, int y) {
    int l = 0, r = min(n-x+1, n-y+1), ans = 0;
    while(l <= r) {
        int mid = (l+r)>>1;
        if(getVal(x, x+mid-1) == getVal(y, y+mid-1))
            ans = mid, l = mid+1;
        else r = mid-1;
    }
    return ans;
}
 
int getLCS(int x, int y) {
    int l = 0, r = min(x, y), ans = 0;
    while(l <= r) {
        int mid = (l+r)>>1;
        if(getVal(x-mid+1, x) == getVal(y-mid+1, y))
            ans = mid, l = mid+1;
        else r = mid-1;
    }
    return ans;
}
 
 
int solve(int len) {
    int ret = 0;
    for(int l = 1; l <= n; l += len) {
        int r = l + len + m;
        if(r > n) break;
         
        int pre = min(getLCS(l, r), len);
        int suf = min(getLCP(l, r), len);
        int siz = pre + suf - 1;
        if(siz >= len) ret += siz - len + 1;
    }
    return ret;
}
 
 
int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) b[i] = read();
    for(int i = 1; i <= n; ++i) a[i] = b[i+1] - b[i];
     
    pow[0] = 1;
    for(int i = 1; i <= n; ++i) pow[i] = pow[i-1] * bin;
    for(int i = 1; i <= n; ++i) val[i] = val[i-1] * bin + a[i];
     
    ll ans = 0;
    for(int i = 1; i <= n; ++i) ans += solve(i);
    printf("%lld\n", ans);
    return 0;
}