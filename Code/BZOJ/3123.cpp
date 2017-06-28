#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 8e4+5;
const int maxl = 18;
int n, m, q, c, last, v[maxn], r[maxn];

#define mid (l+r>>1)
#define lc(x) t[(x)].ls
#define rc(x) t[(x)].rs
#define wi(x) t[(x)].tot
int idx, root[maxn];
struct node { int ls, rs, tot; } t[maxn*110];
struct PersistSegment {	
	void modify(int &o, int l, int r, int p) {
		t[++idx] = t[o], ++wi(o = idx);
		if(l == r) return;
		if(p <= mid) modify(lc(o), l, mid, p);
		else modify(rc(o), mid+1, r, p);
	}
	
	int query(int o1, int o2, int f1, int f2, int k) {
		int l = 1, r = c;
		while(l != r) {
			int ret = wi(lc(o1))+wi(lc(o2))-wi(lc(f1))-wi(lc(f2));
			if(ret >= k) o1 = lc(o1), o2 = lc(o2), f1 = lc(f1), f2 = lc(f2), r = mid;
			else o1 = rc(o1), o2 = rc(o2), f1 = rc(f1), f2 = rc(f2), k -= ret, l = mid+1;
		}
		return l;
	}
} T;


int h[maxn], dep[maxn], siz[maxn], top[maxn], fa[maxn][maxl], cnt;
struct Data { int next, to; } g[maxn<<1];
void add(int x, int y) {
	g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	int d = dep[x]-dep[y];
	for(int i = 0; i < maxl; ++i)
		if(d&(1<<i)) x = fa[x][i];
	if(x == y) return x;
	for(int i = maxl-1; ~i; --i) 
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void dfs(int x, int p, int tp) {
	fa[x][0] = p, dep[x] = dep[p]+1, top[x] = tp;
	T.modify(root[x] = root[p], 1, c, v[x]);
	for(int i = 1; i < maxl; ++i) fa[x][i] = fa[fa[x][i-1]][i-1];
	for(int i = h[x]; i; i = g[i].next)
		if(g[i].to != fa[x][0]) dfs(g[i].to, x, tp);
}

void merge(int x, int y) {
	if(siz[top[x]] > siz[top[y]]) swap(x, y);
	siz[top[y]] += siz[top[x]];
	add(y, x), add(x, y), dfs(x, y, top[y]);
}

int ask(int x, int y, int k) {
	int o = LCA(x, y);
	return r[T.query(root[x], root[y], root[o], root[fa[o][0]], k)];
}

char op[3];
int load() { return read()^last; }
int main() {
	freopen("3123.in", "r", stdin);

	read(), n = read(), m = read(), q = read();
	for(int i = 1; i <= n; ++i) r[i] = v[i] = read();
	sort(r+1, r+1+n);
	c = unique(r+1, r+1+n) - r - 1;
	for(int i = 1; i <= c; ++i) v[i] = lower_bound(r+1, r+1+n, v[i]) - r;
	
	for(int i = 1; i <= n; ++i) top[i] = i, siz[i] = 1;
	for(int i = 1; i <= n; ++i) T.modify(root[i], 1, c, v[i]);
	for(int i = 1; i <= m; ++i) merge(read(), read());
	for(int x, y; q--; ) {
		scanf("%s", op), x = load(), y = load();
		if(*op == 'Q') printf("%d\n", last = ask(x, y, load()));
		else merge(x, y);
	}
	return 0;
}
