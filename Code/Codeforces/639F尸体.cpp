#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 6e5+5, maxl = 20;

int N, M, Q, R, n, m, top, root = N+1;
int fa[maxn][maxl], deep[maxn], st[maxn], d[maxn];
struct Edge { int u, v; } e[maxn];
struct Data { int next, to; };
struct Graph {
	int tot, tim, cnt;
	int head[maxn], low[maxn], dfn[maxn], bcc[maxn], blg[maxn];
	bool vis[maxn];
	Data data[maxn];
	void add(int x, int y) {
		data[++cnt] = (Data){ head[x], y }; head[x] = cnt; 
		data[++cnt] = (Data){ head[y], x }; head[y] = cnt;
	}
	
	void dfs(int x, int pa) {
		low[x] = dfn[x] = ++tim;
		st[++top] = x;
		for(int i = head[x]; i; i = data[i].next) {
			Data &e = data[i];
			if(e.to == pa) {
				pa = -1;
				continue;
			}		
			if(!dfn[e.to]) dfs(e.to, x), low[x] = min(low[x], low[e.to]);
			else if(!blg[e.to]) low[x] = min(low[e.to], low[x]);
		}
		if(low[x] == dfn[x]) {
			++tot;
			while(top) {
				int v = st[top--];
				blg[v] = tot;
				if(v == x) break;
			}
		}
	}
	
	void Tarjan(int n) {
		tim = top = 0;
		for(int i = 1; i <= n; ++i) low[i] = dfn[i] = 0;
		for(int i = 1; i <= n; ++i) if(!dfn[i]) dfs(i, 0);
	}
	
	void dfs(int x) {
		dfn[x] = ++tim;
		for(int i = head[x]; i; i = data[i].next) 
		if(!dfn[data[i].to]) {
			Data &e = data[i];
			deep[e.to] = deep[x]+1;
			fa[e.to][0] = x;
			dfs(e.to);
		}
	}
	
	void init() {
		for(int i = 1; i <= N; ++i) if(!dfn[i]) dfs(i);
		for(int i = 1; i < maxl; ++i)
		for(int j = 1; j <= N; ++j)
			fa[j][i] = fa[ fa[j][i-1] ][i-1];
	}
	
	bool query(int n) {
		for(int i = 2; i <= n; ++i)
			if(bcc[i] != bcc[1]) return false;
		return true;
	}
} G, T, V;

int LCA(int x, int y) {
	if(deep[x] < deep[y]) swap(x, y);
	int dst = deep[x]-deep[y];
	for(int i = 0; i < maxl; ++i)
		if(dst&(1<<i)) x = fa[x][i];
	if(x == y) return x;
	for(int i = maxl-1; ~i; --i)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

bool cmp(int x, int y) { return T.dfn[x] < T.dfn[y]; }
void build() {
	sort(d+1, d+1+n, cmp);
	//n = unique(d+1, d+1+n, cmp) - d-1;
	V.head[root] = top = 0;
	st[++top] = root;
		
	for(int i = 1; i <= n; ++i) {
		if(d[i] == st[top]) continue;
		int u = d[i], lca = LCA(st[top], u);
		V.head[u] = 0;
		
		while(deep[st[top]] > deep[lca])
			if(deep[st[top-1]] > deep[lca])
				V.add(st[top-1], st[top]), --top;
			else {
				if(lca != st[top-1]) V.head[lca] = 0;
				V.add(lca, st[top--]);
				break;
			}
		if(lca != st[top]) st[++top] = lca;
		st[++top] = u;
	}
	while(top) V.add(st[top-1], st[top]), --top;
	for(int i = 1; i <= m; ++i) V.add(e[i].u, e[i].v);
}

int rotate(int x) {
	(x += R)%= N;
	if(!x) x += N;
	return x;
}

int main() {
	freopen("639F.in", "r", stdin);

	N = read(), M = read(), Q = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), G.add(u, v);
	G.Tarjan(N);
	
	for(int i = 1; i <= N; ++i)
	for(int j = G.head[i]; j; j = G.data[j].next) 
		if(G.bcc[i] != G.bcc[G.data[j].to])
			T.add(G.bcc[i], G.bcc[G.data[j].to]);
	T.init();
	
	for(int i = 1; i <= Q; ++i) {
		n = read(), m = read();
		for(int j = 1; j <= n; ++j) d[j] = rotate(read());
		for(int j = 1, u, v; j <= m; ++j) {
			u = rotate(read()), v = rotate(read());
			e[i] = (Edge){ u, v };
			d[++n] = u, d[++n] = v;
		}
		build();
		V.Tarjan(n+1);
		if(V.query(n+1)) printf("YES\n"), R += i;
		else printf("NO\n");
	}
	return 0;
}	
