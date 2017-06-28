#include <cstdio>
#include <cstring>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
 
const int N = 105;
const double INF = 1e20;
const double EPS = 1e-9;
bool cmin(double &x, double y) { return x > y ? x = y, 1 : 0; }
bool cmax(double &x, double y) { return x < y ? x = y, 1 : 0; }
 
 
int n;
namespace KM {
    double w[N][N], wx[N], wy[N], slack[N];
    int q[N], mx[N], my[N], pre[N];
    bool vx[N], vy[N];
     
    void match(int y) {
        for(int x, z; ~y; y = z) {
            x = pre[y], z = mx[x];
            mx[x] = y, my[y] = x;
        }
    }
     
    void find(int o) {
        for(int i = 1; i <= n; ++i) vx[i] = vy[i] = 0;
        for(int i = 1; i <= n; ++i) slack[i] = INF;
         
        int h = 1, t = 0;
        q[++t] = o, vx[o] = 1;
        for(;;) {
            while(h <= t) {
                int x = q[h++];
                for(int y = 1; y <= n; ++y) if(!vy[y]) {
                    double d = wx[x] + wy[y] - w[x][y];
                    if(!d) {
                        pre[y] = x;
                        if(my[y] < 0) return match(y);
                        q[++t] = my[y], vx[my[y]] = vy[y] = 1;
                    } else if(cmin(slack[y], d)) pre[y] = x;
                }
            }
     
            double d = INF;
            for(int i = 1; i <= n; ++i)
                if(!vy[i]) cmin(d, slack[i]);
            for(int i = 1; i <= n; ++i) {
                if(vx[i]) wx[i] -= d;
                if(vy[i]) wy[i] += d;
                else slack[i] -= d;
            }
             
            for(int i = 1; i <= n; ++i)
                if(!vy[i] && !slack[i]) {
                    if(my[i] < 0) return match(i);
                    q[++t] = my[i], vx[my[i]] = vy[i] = 1;
                }
        }
         
    }
     
    double calc(double v[][N]) {
        for(int i = 1; i <= n; ++i) mx[i] = my[i] = -1;
        for(int i = 1; i <= n; ++i) wx[i] = -INF;
        for(int i = 1; i <= n; ++i) wy[i] = 0;
         
        for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            cmax(wx[i], w[i][j] = v[i][j]);
        for(int i = 1; i <= n; ++i) find(i);
         
        double ret = 0;
        for(int i = 1; i <= n; ++i)
            ret += wx[i] + wy[i];
        return ret;
    }
}
 
 
double v[N][N];
int a[N][N], b[N][N];
bool judge(double x) {
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        v[i][j] = -x*b[i][j] + a[i][j];
    return KM::calc(v) > EPS;
}
 
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        scanf("%d", &a[i][j]);
     
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        scanf("%d", &b[i][j]);
     
     
    double l = 0, r = 1e4;
    while(r-l > 1e-7) {
        double mid = (l+r)/2;
        if(judge(mid)) l = mid;
        else r = mid;
    }
    printf("%.6lf\n", l);
    return 0;
}
﻿
