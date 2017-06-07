#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxm = 5e5+5;
int N, M, tim, dfn[maxn], rev[maxn], size[maxn];
int fa[maxn], pa[maxn], sdom[maxn], idom[maxn], best[maxn]; 

struct Data { int next, to; };
struct Graph {
	int head[maxn], cnt;
	Data data[maxm];
	void add(int x, int y) {
		data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
	}
} G, F, S, T;
#define for_edge(i, a, x) for(int i = a.head[x]; i; i = a.data[i].next)
	
void Get(int x) {
	dfn[x] = ++tim, rev[tim] = x;
	for_edge(i, G, x) {
		Data &e = G.data[i];
		if(!dfn[e.to]) Get(e.to), pa[dfn[e.to]] = dfn[x];
	}
}
	
int Find(int x) {
	if(x == fa[x]) return x;
	int y = Find(fa[x]);
	if(sdom[best[x]] > sdom[best[fa[x]]])
		best[x] = best[fa[x]];
	return fa[x] = y;
}

void Lengauer_Tarjan() {
	for(int i = 1; i <= tim; ++i) fa[i] = sdom[i] = best[i] = i;
	for(int i = tim; i > 1; --i) {
		for_edge(j, F, rev[i]) {
			int v = dfn[F.data[j].to];
			if(v) Find(v), sdom[i] = min(sdom[i], sdom[best[v]]);
		}
		
		S.add(sdom[i], i);
		fa[i] = pa[i];
		for_edge(j, S, pa[i]) {
			int v = S.data[j].to;
			Find(v);
			if(sdom[v] == sdom[best[v]]) idom[v] = sdom[v];
			else idom[v] = best[v];
		}
		S.head[pa[i]] = 0;
	}
	
	for(int i = 2; i <= tim; ++i) {
		if(idom[i] != sdom[i]) idom[i] = idom[idom[i]];
		T.add(rev[idom[i]], rev[i]);
	}
}

void Dfs(int x) {
	size[x] = 1;
	for_edge(i, T, x) {
		Data &e = T.data[i];
		Dfs(e.to);
		size[x] += size[e.to];
	}
}		

int main() {
	N = read(), M = read();
	for(int i = 1, u, v; i <= M; ++i) 
		u = read(), v = read(), G.add(u, v), F.add(v, u);
		
	Get(1);
	Lengauer_Tarjan();
	Dfs(1);
	
	ll ans = 0;
	for_edge(i, T, 1) {
		Data &e = T.data[i];
		ans += 1LL*size[e.to]*(size[1]-1-size[e.to]);
	}
	ans = ans/2 + size[1]-1;
	printf("%lld\n", ans);
	return 0;
}
