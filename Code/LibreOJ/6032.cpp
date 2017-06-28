#include <set>
#include <cstdio>
#include <assert.h>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 2e5+5;
const int K = 18;
const int INF = 2e9;


struct ele {
	int type, pos, hei, id;
	void init(int i) {
		id = i;
		pos = read();
		hei = read() << 1 | 1;
		type = read();
	}
	
	inline bool operator <(const ele &b) const {
		return hei != b.hei ? hei < b.hei : id < b.id;
	}
} opt[N], NONE;

bool cmp(ele a, ele b) {
	return a.hei != b.hei ? a.hei < b.hei : a.id > b.id;
}


#define ls o<<1
#define rs o<<1|1
#define mid (l+r>>1)
#define lc ls, l, mid
#define rc rs, mid+1, r
struct segment {
	set <ele> mus[N];
	ele t[N << 2];
	
	inline void pushup(int o) {
		t[o] = min(t[ls], t[rs]);
	}
	
	void build(int o, int l, int r) {
		if(l == r) {
			mus[l].clear();
			mus[l].insert(NONE);
			t[o] = NONE;
			return;
		}
		build(lc);
		build(rc);
		pushup(o);
	}

	inline void insert(int o, int l, int r, int p, ele v) {
		if(l == r) {
			mus[l].insert(v);
			t[o] = *mus[l].begin();
			return;
		}
		if(p <= mid) insert(lc, p, v);
		else insert(rc, p, v);
		pushup(o);
	}
	
	inline ele query(int o, int l, int r, int L, int R) {
		if(R < l || r < L) return NONE;
		if(L <= l && r <= R) return t[o];
		return min(query(lc, L, R), query(rc, L, R));
	}
	
	inline void remove(int o, int l, int r, int p) {
		if(l == r) {
			mus[l].erase(mus[l].begin());
			t[o] = *mus[l].begin();
			return;
		}
		if(p <= mid) remove(lc, p);
		else remove(rc, p);
		pushup(o);
	}
} t0, t1;


int n, m, ban[N];
struct STtable {
	int c, lg[N];
	int st[N][K];
	
	void build() {
		c = n + 1, lg[0] = -1;
		for(int i = 1; i <= c; ++i) lg[i] = lg[i>>1] + 1;
		for(int i = 1; i <= c; ++i) st[i][0] = i;
		for(int i = 1; i < K; ++i)
			for(int j = 1; j <= c; ++j) {
				int t1 = st[j][i-1];
				int t2 = (j+(1<<i-1) <= c) ? st[j+(1<<i-1)][i-1] : 0;
				st[j][i] = ban[t1] > ban[t2] ? t1 : t2;
			}
	}
	
	int query(int l, int r) {
		int t = lg[r-l+1];
		return max(ban[st[l][t]], ban[st[r-(1<<t)+1][t]]);
	}
	
	int askL(int p, int v) {
		int l = 1, r = p;
		while(l < r) 
			if(query(mid+1, r) > v) l = mid+1;
			else r = mid;
		return l;
	}
	
	int askR(int p, int v) {
		int l = p, r = c;
		while(l < r) 
			if(query(p, mid) > v) r = mid;
			else l = mid+1;
		return r;
	}
} height;



int root, ans, sum, cnt;
int del[N], siz[N], deg[N], h[N];
struct Data {
	int next, to;
} g[N];

void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt, ++deg[y];
}

int dfs(int x) {
	int ret = 0;
	for(int i = h[x], v; i; i = g[i].next) {
		ret += dfs(v = g[i].to);
		siz[x] += siz[v];
	}
	return max(ret, siz[x]);
}


int cas;
int main() {
	cas = read();
	while(cas--) {
		n = read(), m = read();
		ban[1] = ban[n+1] = INF;
		for(int i = 2; i <= n; ++i) ban[i] = read() << 1;
		for(int i = 1; i <= m; ++i) opt[i].init(i);
		height.build();
		
		NONE.hei = INF;
		t0.build(1, 1, n);
		t1.build(1, 1, n);
		
		cnt = sum = 0;
		for(int i = 1; i <= m+1; ++i) 
			h[i] = siz[i] = deg[i] = del[i] = 0;
			
		for(int i = 1; i <= m; ++i)
			if(opt[i].type) t1.insert(1, 1, n, opt[i].pos, opt[i]);
			else t0.insert(1, 1, n, opt[i].pos, opt[i]), ++sum;
		sort(opt+1, opt+1+m, cmp);
		
		for(int i = 1; i <= m; ++i) 
			if(opt[i].type) {
				ele &e = opt[i];
				if(del[e.id]) continue;
				int L = height.askL(e.pos, e.hei);
				int R = height.askR(e.pos+1, e.hei)-1;
				
				for(ele v; (v = t1.query(1, 1, n, L, R)).hei <= e.hei;) {
					if(v.hei == e.hei) {
						++siz[e.id];
						if(v.id != e.id) {
							del[v.id] = 1;
							t1.remove(1, 1, n, v.pos);
						} else break;
					} else {
						add(e.id, v.id);
						t1.remove(1, 1, n, v.pos);
					}
				}
				
				for(ele v; (v = t0.query(1, 1, n, L, R)).hei <= e.hei;) 
					t0.remove(1, 1, n, v.pos), --siz[e.id];
			}
		
		root = m + 1;
		for(int i = 1; i <= m; ++i) {
			ele &e = opt[i];
			if(!e.type) continue;
			if(deg[e.id]) continue;
			if(del[e.id]) continue;
			add(root, opt[i].id);
		}
		
		ans = dfs(root) + sum;
		printf("%d\n", ans);
	}
	return 0;
}