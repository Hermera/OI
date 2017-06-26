#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int maxn = 2005;
const double oo = 1e20;
int n, m, v, e, c[maxn], d[maxn], dis[maxn][maxn];
double t1, t2, t3, t4, p[maxn], dp[maxn][maxn][2];
 
int main() {
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for(int i = 1; i <= n; ++i) scanf("%d", c+i);
    for(int i = 1; i <= n; ++i) scanf("%d", d+i);
    for(int i = 1; i <= n; ++i) scanf("%lf", p+i);
     
    memset(dis, 63, sizeof(dis));
    for(int i = 1; i <= v; ++i) dis[i][i] = dis[0][i] = 0;
    for(int i = 1, x, y, w; i <= e; ++i)
        scanf("%d%d%d", &x, &y, &w), 
        dis[x][y] = dis[y][x] = min(dis[x][y], w);
    for(int k = 1; k <= v; ++k)
    for(int i = 1; i <= v; ++i)
    for(int j = 1; j <= v; ++j)
        dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
         
    for(int i = 0; i <= n; ++i)
    for(int j = 0; j <= m; ++j)
        dp[i][j][0] = dp[i][j][1] = oo;
    dp[0][0][0] = 0;
    for(int i = 1; i <= n; ++i)
    for(int j = 0; j <= m; ++j) {
        t1 = dp[i-1][j][0] + dis[c[i-1]][c[i]];
        t2 = dp[i-1][j][1] + p[i-1]*dis[d[i-1]][c[i]] + (1-p[i-1])*dis[c[i-1]][c[i]];
        dp[i][j][0] = min(t1, t2);
        if(j) {
            t1 = dp[i-1][j-1][0] + dis[c[i-1]][c[i]];
            t3 = dp[i-1][j-1][0] + dis[c[i-1]][d[i]];
            t2 = dp[i-1][j-1][1] + p[i-1]*dis[d[i-1]][c[i]] + (1-p[i-1])*dis[c[i-1]][c[i]];     
            t4 = dp[i-1][j-1][1] + p[i-1]*dis[d[i-1]][d[i]] + (1-p[i-1])*dis[c[i-1]][d[i]];
            dp[i][j][1] = min(p[i]*t3+(1-p[i])*t1, p[i]*t4+(1-p[i])*t2);
        }
    }
     
    double ans = oo;
    for(int i = 0; i <= m; ++i)
        ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
    printf("%.2lf\n", ans);
    return 0;
}