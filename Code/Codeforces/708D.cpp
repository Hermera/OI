#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 505, inf = 1e9;
int N, M, S, T, flow, cost, dis[maxn], iter[maxn], d[maxn];
struct Edge { int to, rev, cap, cost; };
vector <Edge> G[maxn];
bool vis[maxn];

void AddEdge(int x, int y, int cap, int cost) {
    G[x].push_back((Edge){ y, G[y].size(), cap, cost });
    G[y].push_back((Edge){ x, G[x].size()-1, 0, -cost });
}
 
bool SPFA() {
    queue <int> q;
    for(int i = S; i <= T; ++i) iter[i] = vis[i] = 0, dis[i] = inf;
    q.push(T); dis[T] = 0; vis[T] = true;
    while(!q.empty()) {
        int v = q.front(); q.pop(); vis[v] = false;
        for(int i = 0; i < G[v].size(); ++i) {
            Edge &e = G[v][i];
            if(G[e.to][e.rev].cap && dis[e.to] > dis[v]-e.cost) {
                dis[e.to] = dis[v]-e.cost;
                if(!vis[e.to]) vis[e.to] = true, q.push(e.to);
            }
        }
    }
    mset(vis, 0);
    return dis[S] < inf;
}
 
int dfs(int v, int f) {
    vis[v] = true;
    if(v == T || !f) return f;
    for(int &i = iter[v]; i < G[v].size(); ++i) {
        Edge &e = G[v][i];
        if(e.cap && !vis[e.to] && dis[v]-e.cost == dis[e.to]) {
            int d = dfs(e.to, min(e.cap, f));
            if(d > 0)
            { cost += d*e.cost, e.cap -= d, G[e.to][e.rev].cap += d; return d; }
        }
    }
    return 0;
}
 
void ZKW() {
    while(SPFA())
        for(int f; (f = dfs(S, inf)) > 0; ) flow += f;
}

int main() {
	scanf("%d%d", &N, &M);
	S = 0, T = N+1;
	for(int i = 1, u, v, c, f; i <= M; ++i) {
		u = read(), v = read(), c = read(), f = read();
		d[u] -= f;
		d[v] += f;
		if(f > c) {
			cost += f-c;
			AddEdge(v, u, f-c, 0);
			AddEdge(v, u, c, 1);
			AddEdge(u, v, inf, 2);
		}
		else {
			AddEdge(v, u, f, 1);
			AddEdge(u, v, c-f, 1);
			AddEdge(u, v, inf, 2);
		}
	}
	AddEdge(N, 1, inf, 0);
	for(int i = 1; i <= N; ++i) 
		if(d[i] < 0) AddEdge(i, T, -d[i], 0);
		else AddEdge(S, i, d[i], 0);
	
	ZKW();
	printf("%d\n", cost);
	return 0;
}
