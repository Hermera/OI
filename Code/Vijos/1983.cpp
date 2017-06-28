#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e5+5;
const int oo = 2e9;
int n, m, cnt, tim;
int h[maxn], siz[maxn], fa[maxn], son[maxn], dep[maxn], dis[maxn];
int id[maxn], top[maxn], w[maxn], add[maxn];
struct Data { int next, to, w; } G[maxn<<1];
void lik(int x, int y, int w) {
	G[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
}

void dfs(int x) {
	siz[x] = 1;
	for(int i = h[x], v; i; i = G[i].next) 
		if((v = G[i].to) != fa[x]) {
			fa[v] = x, dep[v] = dep[x]+1, dis[v] = dis[x]+G[i].w;
			dfs(v), siz[x] += siz[v], w[v] = G[i].w;
			if(siz[v] > siz[son[x]]) son[x] = v;
		}
}

void dfs(int x, int tp) {
	id[x] = ++tim, top[x] = tp;
	if(son[x]) dfs(son[x], tp);
	for(int i = h[x]; i; i = G[i].next)
		if(G[i].to != fa[x] && G[i].to != son[x])
			dfs(G[i].to, G[i].to);
}

int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y]) swap(x, y);
	return y;
}

struct plan {
	int x, y, lca, val;
	void init() {
		x = read(), y = read();
		lca = LCA(x, y);
		val = dis[x]+dis[y]-2*dis[lca];
	}
	bool operator <(const plan &b) const {
		return val > b.val;
	}
} p[maxn];

bool judge(int x) {
	int tot = 0;
	for(int i = 1; i <= n; ++i) add[i] = 0;
	for(int i = 1; i <= m; ++i) 
		if(p[i].val > x)
			++tot, add[p[i].lca] -= 2, 
			++add[p[i].x], ++add[p[i].y];
		else break;
	for(int i = 1; i <= n; ++i) add[fa[id[i]]] += add[id[i]];

	int mx = 0;
	for(int i = 1; i <= n; ++i)
		if(add[i] == tot) mx = max(mx, w[i]);
	for(int i = 1; i <= tot; ++i)
		if(p[i].val-mx > x) return 0;
	return 1;
}

bool cmp(int x, int y) { return dep[x] > dep[y]; }
int main() {
	n = read(), m = read();
	for(int i = 1, x, y, w; i < n; ++i)
		x = read(), y = read(), w = read(),
		lik(x, y, w), lik(y, x, w);
	
	dfs(1);
	dfs(1, 1);
	for(int i = 1; i <= n; ++i) id[i] = i;
	for(int i = 1; i <= m; ++i) p[i].init();
	sort(p+1, p+1+m);
	sort(id+1, id+1+n, cmp);
	
	int l = 0, r = oo, ans = oo;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(judge(mid)) ans = mid, r = mid-1;
		else l = mid+1;
	}
	printf("%d\n", ans);
	return 0;
}
