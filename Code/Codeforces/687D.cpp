#include <cstdio>
#include <vector>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e6+5;
int N, M, Q, tim;
struct Edge {
	int u, v, w;
	void init() { u = read(), v = read(), w = read(); }
} e[maxn];

struct DSU {
	int fa[maxn], v[maxn];
	void init() {
		for(int i = 1; i <= (N<<1); ++i) fa[i] = i;
	}
	
	int Find(int x) {
		if(v[x] != tim) fa[x] = x, v[x] = tim;
		return fa[x] == x ? x : fa[x] = Find(fa[x]);
	}
	
	int Union(int x, int y)	{
		if(Find(x) == Find(y)) return 1;
		if(Find(x) == Find(y+N)) return 0;
		fa[Find(x)] = Find(y+N);
		fa[Find(y)] = Find(x+N);
		return -1;
	}
} G;

struct Segment {
	#define mid (l+r>>1)
	#define lc o<<1, l, mid
	#define rc o<<1|1, mid+1, r

	struct Leaf {
		int w;
		vector <Edge> g;
		Leaf() { w = -1, g.clear(); }
		bool add(Edge x) {
			int acc = G.Union(x.u, x.v);
			if(acc) g.push_back(x);
			if(acc == 1) w = x.w;
			return acc == 1;
		}	
	} t[maxn<<2], O;
	
	Leaf merge(Leaf ls, Leaf rs) {
		Leaf ret;
		int p1 = 0, p2 = 0, flag = false;
		++tim;
			
		while(!flag && p1 < ls.g.size() && p2 < rs.g.size()) {
			if(ls.g[p1].w > rs.g[p2].w) flag = ret.add(ls.g[p1++]);
			else flag = ret.add(rs.g[p2++]);
		}
		while(!flag && p1 < ls.g.size()) flag = ret.add(ls.g[p1++]);
		while(!flag && p2 < rs.g.size()) flag = ret.add(rs.g[p2++]);
		return ret;
	}
	
	void build(int o, int l, int r) {
		if(l == r) {
			t[o].g.push_back(e[l]);
			t[o].w = -1;
			return;
		}
		else {
			build(lc), build(rc);
			t[o] = merge(t[o<<1], t[o<<1|1]);
		}
	}
	
	Leaf query(int o, int l, int r, int L, int R) {
		if(r < L || R < l) return O;
		if(L <= l && r <= R) return t[o];
		Leaf c1 = query(lc, L, R), c2 = query(rc, L, R);
		return merge(c1, c2);
	}
} T;

int main() {
	freopen("687D.in", "r", stdin);

	N = read(), M = read(), Q = read();
	G.init();
	for(int i = 1; i <= M; ++i) e[i].init();	
	T.build(1, 1, M);
	for(int i = 1, l, r; i <= Q; ++i) {
		l = read(), r = read();
		printf("%d\n", T.query(1, 1, M, l, r).w);
	}
	return 0;
}
