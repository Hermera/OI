#include <cstdio>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5, inf = 1e9;
#define for_edge(a, x, y) for(int i = a.head[x]; i; i = a.data[i].next) if(a.data[i].to != y)
struct Data { int next, to, w; };
struct LinkTable {
	Data data[maxn];
	int head[maxn], cnt;
	void add(int x, int y, int w) {
		data[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
	}
} E, R;

struct DP { int sum, id, lca; } f[maxn], g[maxn];
int N, K, mx[5], mi[5], ret[maxn], fa[maxn], w[maxn];
bool mark[maxn];
 
int update(int &x, int y) {
	if(x < y) return x = y, 1;
	if(x == y) return 0;
	return -1;
}  
 
void F(int x) {
	int sum = mark[x] ? 0 : -inf, id = x;
	for_edge(E, x, fa[x]) {
		Data &e = E.data[i];
		fa[e.to] = x;
		w[e.to] = e.w;
		F(e.to);
		
		if(update(sum, f[e.to].sum+e.w) == 1) id = f[e.to].id;
		else if(!update(sum, f[e.to].sum+e.w)) id = x;
	}
	f[x].sum = sum;
	f[x].id = id;
	f[x].lca = x;

}

void G(int x) {
	g[x] = g[fa[x]];
	g[x].sum += w[x];
	if(mark[fa[x]] && w[x] > g[x].sum) 
		g[x].sum = w[x], g[x].id = g[x].lca = fa[x];
		
	for_edge(R, fa[x], x) {
		Data &e = R.data[i];
		if(update(g[x].sum, f[e.to].sum+e.w+w[x]) == 1) 
			g[x].id = f[e.to].id, g[x].lca = fa[x];
		else if(update(g[x].sum, f[e.to].sum+e.w+w[x]) == 0)
			g[x].id = g[x].lca = fa[x];
	}
	
	for(int i = 0; i < 3; ++i) mi[i] = 0, mx[i] = -inf;
	for_edge(E, x, fa[x]) {
		Data &e = E.data[i];
		if(update(mx[0], f[e.to].sum+e.w) == 1) {
			mx[2] = mx[1], mi[2] = mi[1];
			mx[1] = mx[0], mi[1] = mi[0];
			mi[0] = e.to;
		}
		else if(update(mx[1], f[e.to].sum+e.w) == 1)
			mx[2] = mx[1], mi[2] = mi[1], mi[1] = e.to;
		else if(update(mx[2], f[e.to].sum+e.w) == 1) 
			mi[2] = e.to;
	}
	
	for(int i = 0; i < 3; ++i)
		if(mi[i]) R.add(x, mi[i], w[mi[i]]);
		
	for_edge(E, x, fa[x]) G(E.data[i].to);
}

void init() {
	N = read(), K = read();
	for(int i = 1; i <= K; ++i) mark[read()] = true;
	for(int i = 1, u, v, w; i < N; ++i) 
		u = read(), v = read(), w = read(), E.add(u, v, w), E.add(v, u, w);
	g[0].sum = -inf;
}

void dfs(int x) {
	for_edge(E, x, fa[x]) {
		Data &e = E.data[i];
		dfs(e.to);
		ret[x] += ret[e.to];
	}
}

void solve() {
	for(int i = 1; i <= N; ++i) 
		if(mark[i] && f[i].sum != g[i].sum) 
			if(f[i].sum > g[i].sum) 
				++ret[f[i].id], --ret[f[i].lca];
			else ++ret[g[i].id], --ret[g[i].lca], ++ret[i], --ret[fa[g[i].lca]];
	dfs(1);
	int sum = -inf, once = 0;
	for(int i = 1; i <= N; ++i)
		if(!mark[i])
			if(ret[i] > sum) sum = ret[i], once = 1;
			else if(ret[i] == sum) ++once;
	printf("%d %d\n", sum, once);
}

int main() {
	init();
	F(1), G(1);
	solve();
	return 0;
}
