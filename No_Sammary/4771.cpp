#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 1e5+5;

struct node {
	int ls, rs, tot;
} t[150 * N];
int n, m, q, idx;

#define mid (l+r>>1)
#define lc t[o].ls, l, mid
#define rc t[o].rs, mid+1, r
struct Segment {
	int root;
	void modify(int &o, int l, int r, int p, int v) {
		t[++idx] = t[o], o = idx;
		if(l == r) {
			t[o].tot += v;
			return;
		}
		if(p <= mid) modify(lc, p, v);
		else modify(rc, p, v);
		t[o].tot = t[t[o].ls].tot + t[t[o].rs].tot;
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[o].tot;
		if(R < l || r < L) return 0;
		return query(lc, L, R) + query(rc, L, R);
	}
	
	void modify(int x, int v) {
		modify(root, 1, m, x, v);
	}
	
	int query(int L, int R) {
		return query(root, 1, m, L, R);
	}
} T[N];

int h[N], w[N], cnt;
struct Data { int next, to; } g[N];
void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}

int fa[N], dep[N], siz[N], son[N], top[N];
void dfs(int x) {
	siz[x] = 1;
	for(int i = h[x]; i; i = g[i].next)	{
		int v = g[i].to;
		dep[v] = dep[x]+1, fa[v] = x;
		dfs(v), siz[x] += siz[v];
		if(siz[son[x]] < siz[v]) son[x] = v;
	}
}

map <int, int> c[N];
map <int, int>:: iterator it;
#define fir first
#define sec second

void insert(int x, int v, int d) {
	int o = top[x];
	if(!c[o].count(v)) {
		c[o][v] = d;
		T[x].modify(d, 1);
	} else {
		int t = c[o][v];
		if(t > d) {
			c[o][v] = d;
			T[x].modify(t, -1);
			T[x].modify(d, 1);
		}
	}
}

void build(int x) {	
	if(son[x]) {
		build(son[x]);
		T[x].root = T[son[x]].root;
	}
	
	insert(x, w[x], dep[x]);
	for(int v, i = h[x]; i; i = g[i].next)
		if((v = g[i].to) != son[x]) {
			build(v);
			for(it = c[v].begin(); it != c[v].end(); ++it)
				insert(x, it->fir, it->sec);
			c[v].clear();
		}
}

int last, cas;
void clean() {
	idx = cnt = m = last = 0;
	for(int i = 1; i <= n; ++i)
		T[i].root = h[i] = son[i] = 0;
	for(int i = 1; i <= n; ++i) c[i].clear();
}

int main() {
	freopen("4771.in", "r", stdin);
	freopen("4771.out", "w", stdout);

	cas = read();
	while(cas--) {
		clean();
	
		n = read(), q = read();
		for(int i = 1; i <= n; ++i) w[i] = read();
		for(int i = 2; i <= n; ++i) add(read(), i);
		
		dep[1] = 1, dfs(1);
		for(int i = 1; i <= n; ++i) m = max(m, dep[i]);
		for(int i = 1; i <= n; ++i)
			if(son[fa[i]] != i)
				for(int j = i; j; j = son[j])
					top[j] = i;
		build(1);
		for(int x, d; q--; ) {
			x = read() ^ last;
			d = read() ^ last;
			printf("%d\n", last = T[x].query(dep[x], dep[x] + d));
		}
	}
	return 0;
}
