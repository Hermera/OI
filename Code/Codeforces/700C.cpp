#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 1005, maxm = 3e4+5, inf = 2147483647;
struct Edge { int to, id; };
int N, M, S, T, tim, ban, ans;
int c[maxm], dfn[maxn], low[maxn];
bool vis[maxn];
vector <Edge> G[maxn];
vector <int> P, br, put;

bool dfs(int x) {
	vis[x] = true;
	if(x == T) return true;
	for(int i = 0; i < G[x].size(); ++i) {
		Edge &e = G[x][i];
		if(!vis[e.to] && dfs(e.to)) {
			P.push_back(e.id);
			return true;
		}
	}
	return false;
}

bool Tarjan(int x, int fa) {
	vis[x] = true;
	dfn[x] = low[x] = ++tim;
	bool ret = (x == T);
	for(int i = 0; i < G[x].size(); ++i) {
		Edge &e = G[x][i];
		if(e.id == ban || e.id == fa) continue;
		if(!vis[e.to]) ret |= Tarjan(e.to, e.id);
		low[x] = min(low[x], low[e.to]);
	}
	if(ret && dfn[x] == low[x] && fa) br.push_back(fa);
	return ret;
}

bool update(int &x, int y) {
	x = min(x, y);
	return x == y;
}

int main() {
	freopen("700C.in", "r", stdin);

	scanf("%d%d%d%d", &N, &M, &S, &T);
	for(int i = 1, u, v, w; i <= M; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back((Edge){ v, i });
		G[v].push_back((Edge){ u, i });
		c[i] = w;
	}
	
	ans = inf;
	if(!dfs(S)) return printf("0\n0\n"), 0;
	for(int i = 0; i < P.size(); ++i) {
		ban = P[i], tim = 0, br.clear();
		for(int j = 1; j <= N; ++j) vis[j] = 0;
		
		if(!Tarjan(S, 0) && update(ans, c[P[i]])) 
			put.clear(), put.push_back(P[i]);
		for(int j = 0; j < br.size(); ++j)
			if(update(ans, c[P[i]]+c[br[j]])) 
				put.clear(), put.push_back(P[i]), put.push_back(br[j]);
	}
	
	if(ans >= inf) return printf("-1\n"), 0;
	printf("%d\n%d\n", ans, (int)put.size());
	for(int i = 0; i < put.size(); ++i) printf("%d ", put[i]);
	printf("\n");
	return 0;
}
