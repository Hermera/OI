#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 505, inf = 1e9;
int N, M, X, S, T, flow, cost, dis[maxn], iter[maxn];
struct Edge { int to, rev, cap, cost; };
vector <Edge> G[maxn];
bool vis[maxn];

void AddEdge(int x, int y, int cap, int cost) {
    G[x].push_back((Edge){ y, G[y].size(), cap, cost });
    G[y].push_back((Edge){ x, G[x].size()-1, 0, -cost });
}
 
bool SPFA() {
    queue <int> q;
    for(int i = S; i <= T; ++i) iter[i] = vis[i] = false, dis[i] = inf;
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
    for(int i = S; i <= T; ++i) vis[i] = false;
    return dis[S] < inf;
}
 
int dfs(int v, int f) {
    vis[v] = true;
    if(v == T || !f) return f;
    for(int &i = iter[v]; i < G[v].size(); ++i) {
        Edge &e = G[v][i];
        if(e.cap && !vis[e.to] && dis[v]-e.cost == dis[e.to]) {
            int d = dfs(e.to, min(e.cap, f));
            if(d > 0) { 
            	cost += d*e.cost, e.cap -= d, G[e.to][e.rev].cap += d;
            	return d; 
            }
        }
    }
    return 0;
}
 
void CostFlow() {
    while(SPFA())
        for(int f; (f = dfs(S, inf)) > 0; ) flow += f;
}

char s[maxn], t[maxn];
bool Judge(int u, int len) {
	for(int i = 1; i <= len; ++i) 
		if(s[u+i-1] != t[i]) return false;
	return true;
}		

void init() {
	scanf("%d%s%d", &N, s+1, &M);
	for(int i = 1, len, w; i <= M; ++i) {
		scanf("%s%d", t+1, &w);
		len = strlen(t+1);
		for(int j = 1; s[j]; ++j)
			if(Judge(j, len)) 
				AddEdge(j, j+len, 1, -w);
	}
	S = 0, T = N+2;
	scanf("%d", &X);
	for(int i = 1; i <= N; ++i) AddEdge(i, i+1, X, 0);
	AddEdge(S, 1, X, 0), AddEdge(N+1, T, X, 0);
}

int main() {
	init();
	CostFlow();
	printf("%d\n", -cost);
	return 0;
}
