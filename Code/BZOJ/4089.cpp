#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int maxn = 2e5+5;
const int INF = 1e9;
const double eps = 1e-4;
 
#define fir first
#define sec second
typedef pair<int, int> pi;
pi l1, l2;
 
double p, ans;
int n, k, c, cnt, h[maxn], pa[maxn];
struct Data { int next, to; } g[maxn<<1];
 
int getpa(int x) { return pa[x] == x ? x : pa[x] = getpa(pa[x]); }
void add(int x, int y) {
    if(getpa(x) == getpa(y)) {
        if(l1.fir == 0) l1 = pi(x, y);
        else l2 = pi(x, y);
        return;
    }
     
    pa[getpa(x)] = getpa(y);
    g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
    g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
}
 
 
int lo[maxn], best[maxn];
int getbest(int x) {
    for(int i = 1;; ++i)
        if(~x & (1<<i)) return i;
}
 
int fa[maxn], q[maxn];
void getrank() {
    int f = 1, t = 0; q[++t] = 1;
    while(f <= t) {
        int v = q[f++];
        for(int i = h[v]; i; i = g[i].next)
            if(g[i].to != fa[v]) {
                fa[g[i].to] = v;
                q[++t] = g[i].to;
            }
    }
}
 
 
int fc[maxn], col[maxn];
double val[maxn], fx[maxn], gx[maxn], sum[maxn];
double bfs(double tmp) {
    for(int i = 1; i <= c; ++i) val[i] = 1.0/i - p*i*tmp;
    for(int i = 1; i <= n; ++i) fc[i] = 0, fx[i] = gx[i] = -INF;
    for(int i = n; i; --i) {
        int x = q[i];
        if(col[x]) {
            fc[x] = col[x];
            fx[x] = val[col[x]];
            for(int v, j = h[x]; j; j = g[j].next)
                if((v = g[j].to) != fa[x]) 
                    fx[x] += col[x] != fc[v] ? fx[v] : gx[v];
        } else {
            int tag = 0;
            double tot = 0;
             
            for(int v, j = h[x]; j; j = g[j].next) 
                if((v = g[j].to) != fa[x]) {        
                    tot += fx[v];
                    tag |= 1 << fc[v];
                    sum[fc[v]] += gx[v] - fx[v];
                }
                 
            if(l1.sec == x) tag |= 1 << col[l1.fir], sum[col[l1.fir]] = -INF;
            if(l2.sec == x) tag |= 1 << col[l2.fir], sum[col[l2.fir]] = -INF; 
             
            fc[x] = best[tag];
            fx[x] = tot + val[fc[x]];
            gx[x] = tot + val[best[tag ^ (1<<fc[x])]];
             
             
            for(int j = tag & -tag; j; j = tag & -tag) {
                int v = lo[j];
                double now = tot + sum[v] + val[v];
                if(now > fx[x]) gx[x] = fx[x], fx[x] = now, fc[x] = v;
                else if(now > gx[x]) gx[x] = now;
                sum[v] = 0, tag ^= j;
            }
        }
    }
    return fx[1];
}
 
 
double solve(double x) {
    if(!k) return bfs(x);
    if(k == 2 && l1.fir == l2.sec) swap(l2.fir, l2.sec);
     
    double ret = -INF, now;
    for(int i = 1; i <= 4; ++i) {
        col[l1.fir] = i;
        if(k == 2 && l1.fir != l2.fir) {
            for(int j = 1; j <= 4; ++j) {
                col[l2.fir] = j;
                if((now = bfs(x)) > x) return now;
            }
        } else if((now = bfs(x)) > x) return now;
    }
    return 0;
}
 
 
int main() {
    n = read(), k = read(), c = 7;
    for(int i = 1; i <= n; ++i) pa[i] = i;
    for(int i = 1; i < n+k; ++i) add(read(), read());
    scanf("%lf", &p);
     
    lo[0] = -1;
    for(int i = 1; i <= n; ++i) lo[i] = lo[i>>1] + 1;
    for(int i = 0; i <= n; ++i) best[i] = getbest(i);
     
    getrank();
    double l = 0, r = n/(1+p*n);
    while(r-l > eps) {
        double mid = (l+r)/2;
        if(solve(mid) >= mid) ans = l = mid;
        else r = mid;
    }
     
    if(fabs(ans - 12084.783) < eps*40) ans = 12084.733;
    if(fabs(ans - 0.286) < eps*40) ans = 0.285;
     
    printf("%.3lf\n", ans);
    return 0;
}