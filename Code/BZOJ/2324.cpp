#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 505;
const int INF = 1e9;

int n, m, v, s, t, flow, cost;
int dis[maxn], iter[maxn], w[maxn][maxn];
struct Edge { int to, rev, cap, cost; };
vector <Edge> G[maxn];
bool vis[maxn];

queue <int> q;
bool spfa() {
    for(int i = 0; i <= t; ++i) 
    	dis[i] = INF, vis[i] = iter[i] = 0;
    q.push(s), dis[s] = 0;
    while(!q.empty()) {
        int v = q.front(); q.pop();
        vis[v] = 0;
        for(int i = 0; i < G[v].size(); ++i) {
            Edge &e = G[v][i];
            if(e.cap && dis[v]+e.cost < dis[e.to]) {
                dis[e.to] = dis[v]+e.cost;
                if(!vis[e.to]) q.push(e.to), vis[e.to] = 1;
            }
        }
    }
    return dis[t] != INF;
}

int dfs(int v, int f) {
    if(v == t || !f) return f;
    vis[v] = true;
    for(int &i = iter[v]; i < G[v].size(); ++i) {
        Edge &e = G[v][i];
        if(e.cap && !vis[e.to] && dis[v]+e.cost == dis[e.to]) {
            int d = dfs(e.to, min(e.cap, f));
            if(d) {
                cost += d*e.cost;
                e.cap -= d, G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

void costflow() {
    while(spfa())
        for(int f; (f = dfs(s, INF)); flow += f);
}

void add(int x, int y, int cap, int cost) {
    G[x].push_back((Edge){ y, G[y].size(), cap, cost });
    G[y].push_back((Edge){ x, G[x].size()-1, 0, -cost});
}

int main() {
	scanf("%d%d%d", &n, &m, &v);
	memset(w, 63, sizeof(w));
	for(int i = 0; i <= n; ++i) w[i][i] = 0;
	for(int x, y, l; m--; ) {
		scanf("%d%d%d", &x, &y, &l);
		w[x][y] = min(w[x][y], l);
		w[y][x] = min(w[y][x], l);
	}
	
	for(int k = 0; k <= n; ++k)
	for(int i = 0; i <= n; ++i)
	for(int j = 0; j <= n; ++j)
		if(k <= i || k <= j)
			w[i][j] = min(w[i][j], w[i][k]+w[k][j]);
	
	
	s = 2*n+1, t = 2*n+2;
	add(s, 0, v, 0);
	for(int i = 0; i <= n; ++i)
	for(int j = i+1; j <= n; ++j)
		if(w[i][j] < INF) add(i, j+n, 1, w[i][j]);
	for(int i = 1; i <= n; ++i) add(s, i, 1, 0);
	for(int i = 1; i <= n; ++i) add(i+n, t, 1, 0);
	costflow();
	printf("%d\n", cost);
	return 0;
}
