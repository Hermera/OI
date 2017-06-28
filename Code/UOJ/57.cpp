#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define double long double
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 4e5+5;
const int L = 20;
const int INF = 1e9;
const double EPS = 1e-8;
const double OFF = 1e-2;

void cmax(int &x, int y) {
	x = x < y ? y : x;
}


int q, who[N];
namespace Ograph {
	int n, m, cnt, root, h[N], vis[N];
	struct Data { 
		int next, to, w; 
	} g[N];
	void add(int x, int y, int w) {
		g[++cnt] = (Data) { h[x], y, w }; h[x] = cnt;
		g[++cnt] = (Data) { h[y], x, w }; h[y] = cnt;
	}
	
	struct Link { 
		int x, y, w; 
		bool operator <(const Link &b) const {
			return w < b.w;
		}
	} e[N];
	void insert(int x, int y, int w) {
		e[++m] = (Link) { x, y, w };
		vis[x] = vis[y] = 1;
	}
	
	
	int dep[N], fa[N][L], mx[N][L];
	void dfs(int x) {
		for(int v, i = h[x]; i; i = g[i].next)
			if((v = g[i].to) != fa[x][0]) {
				fa[v][0] = x;
				mx[v][0] = g[i].w;
				dep[v] = dep[x] + 1;
				dfs(v);
			}
	}
	
	int query(int x, int y) {
		if(x == 1 || y == 1) return -1;
		if(x == y) return 0;
		if(!vis[x] || !vis[y]) return -1;
		
		if(dep[x] < dep[y]) swap(x, y);
		
		int dis = dep[x] - dep[y];
		int ret = 0;
		for(int i = L-1; ~i; --i)
			if(dis & (1<<i)) cmax(ret, mx[x][i]), x = fa[x][i];
		if(x == y) return ret;
		for(int i = L-1; ~i; --i)
			if(fa[x][i] != fa[y][i]) {
				cmax(ret, mx[x][i]);
				cmax(ret, mx[y][i]);
				x = fa[x][i], y = fa[y][i];
			}
		return max(ret, max(mx[x][0], mx[y][0]));
	}
	
	
	int pa[N];
	int getpa(int x) {
		return x == pa[x] ? x : pa[x] = getpa(pa[x]);
	}
	
	bool merge(int x, int y) {
		x = getpa(x), y = getpa(y);
		if(x == y) return 0;
		return pa[y] = x, 1;
	}
	
	
	void main() {
		sort(e+1, e+1+m);
		for(int i = 1; i <= n; ++i) pa[i] = i;
		for(int i = 1; i <= m; ++i)
			if(merge(e[i].x, e[i].y)) 
				add(e[i].x, e[i].y, e[i].w);

		dfs(root = e[1].x);
		for(int i = 1; i < L; ++i)
		for(int j = 1; j <= n; ++j) {
			fa[j][i] = fa[fa[j][i-1]][i-1];
			mx[j][i] = max(mx[j][i-1], mx[fa[j][i-1]][i-1]);
		}
		
		for(int i = 1; i <= q; ++i) 
			printf("%d\n", query(who[i], who[i+q]));
	}
}



struct vec {
	double x, y;
	vec() {}
	vec(double a, double b) : x(a), y(b) {}
	bool operator <(const vec &b) const {
		return x != b.x ? x < b.x : y < b.y;
	}
	
	void input() {
		double a, b;
		scanf("%Lf%Lf", &a, &b);
		x = 2 * a;
		y = 2 * b;
	}
} p[N];

double nx;
struct Edge {
	int u, v, w, id;
	double d, sp;
	Edge() {}
	Edge(int a, int b, int c): u(a), v(b), w(c) {
		d = atan2(p[v].y-p[u].y, p[v].x-p[u].x);
		if(p[u].x == p[v].x) sp = INF;
		else sp = (p[v].y-p[u].y) / (p[v].x-p[u].x);
	}
	
	friend bool operator <(Edge a, Edge b) {
		double y1 = p[a.u].y + a.sp * (nx - p[a.u].x);
		double y2 = p[b.u].y + b.sp * (nx - p[b.u].x);
		if(fabs(y1-y2) < EPS) return a.d < b.d;
		return y1 < y2;
	}
} E[N];


namespace Scanline {
	int n, t;
	struct ele {
		int o, id, type;
		ele() {}
		ele(int x, int y, int z) :
			o(x), id(y), type(z) {}
			
		bool operator <(const ele &b) const {
			if(p[o].x != p[b.o].x) return p[o].x < p[b.o].x;
			return type < b.type;
		}
	} op[N];
	
	multiset <Edge> S;
	multiset <Edge>:: iterator it;
	
	
	void insert(int u, int v, int o) {
		if(p[v] < p[u]) swap(u, v), o ^= 1;
		op[++t] = ele(u, o, 2);
		op[++t] = ele(v, o, 1);
	}
	
	void main() {
		q = read();
		for(int i = 1; i <= q; ++i) {
			p[++n].input();
			p[++n].input();
			op[++t] = ele(n-1, i, 3);
			op[++t] = ele(n, i+q, 3);
		}
		
		sort(op+1, op+1+t);
		for(int i = 1; i <= t; ++i) {
			ele &e = op[i];
			nx = p[e.o].x;
			if(e.type == 1) {
				nx -= OFF; 
				it = S.find(E[e.id]);
				if(it != S.end()) S.erase(it);
			}
			
			if(e.type == 2) nx += OFF, S.insert(E[e.id]);
			if(e.type == 3) {
				it = S.lower_bound(Edge(e.o, e.o, 0));
				if(it == S.end()) who[e.id] = 1;
				else who[e.id] = it->id;
			}
		}
	}
}


namespace Pgraph {
	int n, m, t, cnt, bound, nxt[N];
	vector <int> G[N];
	
	bool cmp(int x, int y) {
		return E[x].d < E[y].d;
	}
	
	void getsort(vector <int> &g) {
		sort(g.begin(), g.end(), cmp);
		for(int i = 0; i < g.size(); ++i)
			nxt[g[i]] = g[(i+1) % g.size()];
	}
	
	void getid(int o, int x) {
		for(; !E[x].id; x = nxt[x^1])
			E[x].id = o;
	}

	void main() {
		n = read(), m = read(), cnt = 1;
		for(int i = 1; i <= n; ++i) {
			p[i].input();
			if(p[i] < p[bound] || !bound) bound = i;
		}
			
		for(int i = 1; i <= m; ++i) {
			int u = read(), v = read(), w = read();
			E[++cnt] = Edge(u, v, w);
			E[++cnt] = Edge(v, u, w);
			G[u].push_back(cnt-1);
			G[v].push_back(cnt);
		}
		
		for(int i = 1; i <= n; ++i) getsort(G[i]);
		getid(++t, G[bound][0]);
		for(int i = 2; i <= cnt; ++i)
			if(!E[i].id) getid(++t, i);
		
		Scanline::n = n;
		Ograph::n = t;
		for(int i = 2; i <= cnt; i += 2) {
			if(p[E[i].u].x != p[E[i].v].x)
				Scanline::insert(E[i].u, E[i].v, i);
			if(E[i].id != 1 && E[i^1].id != 1)
				Ograph::insert(E[i].id, E[i^1].id, E[i].w);
		}
		Scanline::main();
	}
}


int main() {
	Pgraph::main();
	Ograph::main();
	return 0;
}
