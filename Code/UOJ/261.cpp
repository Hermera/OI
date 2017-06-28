#include <cstdio>
#include <vector>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e5+5;
const int maxm = 7e5+5;
int n, m, tim, w[maxn], A[maxn];
int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], dfn[maxn];
vector <int> G[maxn], B[maxn];

void add(int x, int y) {
	G[x].push_back(y);
	G[y].push_back(x);
}

void dfs(int x) {
	siz[x] = 1;
	for(int i = 0, v; i < G[x].size(); ++i) 
		if((v = G[x][i]) != fa[x]){
			fa[v] = x, dep[v] = dep[x]+1;
			dfs(v), siz[x] += siz[v];
			if(siz[v] > siz[son[x]]) son[x] = v;
		}
}

void dfs(int x, int tp) {
	dfn[x] = ++tim, top[x] = tp;
	if(son[x]) dfs(son[x], tp);
	for(int i = 0; i < G[x].size(); ++i) 
		if(G[x][i] != son[x] && G[x][i] != fa[x]) 
			dfs(G[x][i], G[x][i]);
}

int lca(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y]) swap(x, y);
	return y;
}


struct ele { int u, v, len; };
vector <ele> P[maxn];
int aa[maxm], bb[maxm], ans[maxn];
int *st = aa, *ed = bb+maxn;

void solve(int x) {
	ans[x] -= st[w[x]+dep[x]];
	ans[x] -= ed[dep[x]-w[x]];
	for(int i = 0; i < G[x].size(); ++i)
		if(G[x][i] != fa[x]) solve(G[x][i]);
		
	st[dep[x]] += A[x];
	for(int i = 0; i < B[x].size(); ++i) 
		++ed[dep[x]-B[x][i]];
	ans[x] += st[w[x]+dep[x]];
	ans[x] += ed[dep[x]-w[x]];	
	for(int i = 0; i < P[x].size(); ++i)
		--st[dep[P[x][i].u]],
		--ed[dep[P[x][i].v]-P[x][i].len];
}

int main() {
	n = read(), m = read();
	for(int i = 2; i <= n; ++i) add(read(), read());
	for(int i = 1; i <= n; ++i) w[i] = read();
	
	dfs(1);
	dfs(1, 1);
	for(int i = 1, u, v, c, l; i <= m; ++i) {
		u = read(), v = read(), c = lca(u, v);
		l = dep[u]+dep[v]-2*dep[c];
		++A[u], B[v].push_back(l);
		P[c].push_back((ele){ u, v, l });
		if(w[c]+dep[c] == dep[u]) --ans[c];
	}
	
	solve(1);
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
