#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int maxn = 1005;
const int INF = 1e9;
 
int n, m, level[maxn], iter[maxn];
struct Edge { int to, rev, cap; };
struct Data { int x, y, w; } e[maxn * 10];
vector <Edge> g[maxn];
 
void add(int x, int y, int w) {
    g[x].push_back((Edge){ y, g[y].size(), w });
    g[y].push_back((Edge){ x, g[x].size()-1, w });
}
 
queue <int> q;
bool bfs(int s, int t) {
    for(int i = 1; i <= n; ++i) level[i] = -1;
    for(int i = 1; i <= n; ++i) iter[i] = 0;
    q.push(s), level[s] = 0;
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int i = 0; i < g[v].size(); ++i) {
            Edge &e = g[v][i];
            if(e.cap && level[e.to] < 0)
                level[e.to] = level[v]+1, q.push(e.to);
        }
    }
    return ~level[t];
}
 
int dfs(int v, int t, int f) {
    if(v == t) return f;
    for(int &i = iter[v]; i < g[v].size(); ++i) {
        Edge &e = g[v][i];
        if(e.cap && level[e.to] > level[v]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if(d) {
                e.cap -= d, g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
 
int maxflow(int s, int t) {
    int flow = 0;
    while(bfs(s, t)) 
        for(int f; f = dfs(s, t, INF); flow += f);
    return flow;
}
 
 
bool vis[maxn];
void dfs(int x) {
    if(vis[x]) return;
    vis[x] = 1;
    for(int i = 0; i < g[x].size(); ++i)
        if(g[x][i].cap) dfs(g[x][i].to);
}
 
int id[maxn], tmp[maxn], ans[maxn], tot;
void solve(int l, int r) {
    if(l == r) return;
     
    int s = id[l], t = id[r];
    for(int i = 1; i <= n; ++i) g[i].clear(), vis[i] = 0;
    for(int i = 1; i <= m; ++i) add(e[i].x, e[i].y, e[i].w);
    ans[++tot] = maxflow(s, t);
     
    dfs(s);
    int p1 = l, p2 = r;
    for(int i = l; i <= r; ++i)
        if(vis[id[i]]) tmp[p1++] = id[i];
        else tmp[p2--] = id[i];
    for(int i = l; i <= r; ++i) id[i] = tmp[i];
     
    solve(l, p1-1);
    solve(p2+1, r);
}
 
 
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i)
        e[i].x = read(), e[i].y = read(), e[i].w = read();
    for(int i = 1; i <= n; ++i) id[i] = i;
     
    solve(1, n);
     
    sort(ans + 1, ans + 1 + tot);
    tot = unique(ans + 1, ans + 1 + tot) - ans - 1;
    printf("%d\n", tot);
    return 0;
}