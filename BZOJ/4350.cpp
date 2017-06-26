#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
 
const int maxn = 305;
const int mod = 998244353;
int s[maxn][maxn], n, m, cas;
ll f[maxn][maxn];
 
int val(int a, int b, int c, int d) {
    return s[c][d] - s[c][b-1] - s[a-1][d] + s[a-1][b-1];
}
 
ll work() {
    memset(f, 0, sizeof f);
    memset(s, 0, sizeof s);
 
    scanf("%d%d", &n, &m);
    for(int x, y, i = 1; i <= m; ++i)
        scanf("%d%d", &x, &y), s[x][y] = 1;
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
     
    for(int i = 1; i <= n; ++i)
        if(val(i, i, i, i)) return 0;
    for(int i = 1; i <= n; ++i) f[i][i] = 1;
    for(int k = 2; k <= n; ++k)
    for(int i = 1; i <= n-k+1; ++i) {
        int j = i+k-1;
         
        if(!val(i, i+1, i, j)) (f[i][j] += f[i+1][j]) %= mod;
        if(!val(i+1, i, j, i)) (f[i][j] += f[i+1][j]) %= mod;
        for(int k = i+1; k < j; ++k)
            if(!val(k+1, i, j, k) && !val(i, i+1, i, k))
                (f[i][j] += f[i+1][k] * f[k+1][j]) %= mod;
    }
    return f[1][n];
}
 
 
int main() {
    scanf("%d", &cas);
    while(cas--) printf("%lld\n", work());
    return 0;
}