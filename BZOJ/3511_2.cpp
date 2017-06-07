#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int maxn = 1e5+5;
const int INF = 1e9;
struct Edge { int to, cap, rev; };
vector <Edge> G[maxn];
int n, m, o, s, t, sum, level[maxn], iter[maxn];
 
void add(int x, int y, int cap) {
    G[x].push_back((Edge){ y, cap, G[y].size() });
    G[y].push_back((Edge){ x, 0, G[x].size()-1 });
}
 
queue <int> q;
bool bfs() {
    for(int i = 1; i <= o; ++i) level[i] = -1, iter[i] = 0;
    q.push(s), level[s] = 0;
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int i = 0; i < G[v].size(); ++i) {
            Edge &e = G[v][i];
            if(level[e.to] < 0 && e.cap) 
                level[e.to] = level[v]+1, q.push(e.to);
        }
    }
    return ~level[t];
}
 
int dfs(int v, int f) {
    if(v == t || !f) return f;
    for(int &i = iter[v]; i < G[v].size(); ++i) {
        Edge &e = G[v][i];
        if(e.cap && level[e.to] > level[v]) {
            int d = dfs(e.to, min(f, e.cap));
            if(d) {
                e.cap -= d, G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
 
int maxflow() {
    int flow = 0;
    while(bfs())
        for(int f; (f = dfs(s, INF)) > 0; flow += f);
    return flow;
}
 
int main() {
    n = read(), m = read(), s = 1, t = o = n;
    for(int i = 2, x; i <= n-1; ++i) x = read(), sum += x, add(s, i, x);
    for(int i = 2, x; i <= n-1; ++i) x = read(), sum += x, add(i, t, x);
    for(int x, y, a, b, c; m--; ) {
        x = read(), y = read();
        a = read(), b = read(), c = read(), sum += a+b;
        add(s, ++o, a), add(o, x, INF), add(o, y, INF);
        add(++o, t, b), add(x, o, INF), add(y, o, INF);
        add(x, y, c), add(y, x, c);
    }
    printf("%d\n", sum-maxflow());
    return 0;
}
