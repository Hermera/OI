#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 705;
const int INF = 1e9;
struct Edge { int to, cap, rev; bool it; };
vector <Edge> G[maxn];
int n, m, o, s, t, sum;
int level[maxn], val[maxn], iter[maxn], deg[maxn];
bool ok[maxn];

void add(int x, int y, int cap) {
	++deg[x];
	G[x].push_back((Edge){ y, cap, G[y].size(), 1 });
	G[y].push_back((Edge){ x, 0, G[x].size()-1, 0 });
}

queue <int> q;
bool bfs() {
	for(int i = 1; i <= o; ++i) level[i] = -1, iter[i] = 0;
	q.push(s), level[s] = 0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i) {
			Edge &e = G[v][i];
			if(level[e.to] < 0 && e.cap && ok[e.to]) 
				level[e.to] = level[v]+1, q.push(e.to);
		}
	}
	return ~level[t];
}

int dfs(int v, int f) {
	if(v == t || !f) return f;
	for(int &i = iter[v]; i < G[v].size(); ++i) {
		Edge &e = G[v][i];
		if(e.cap && level[e.to] > level[v]) {
			int d = dfs(e.to, min(f, e.cap));
			if(d) {
				e.cap -= d, G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int maxflow() {
	int flow = 0;
	while(bfs())
		for(int f; (f = dfs(s, INF)) > 0; flow += f);
	return flow;
}

void topsort() {
	for(int i = 1; i <= o; ++i) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int v = q.front(); q.pop(), ok[v] = 1;
		if(val[v] > 0) sum += val[v];
		for(int i = 0; i < G[v].size(); ++i) if(!G[v][i].it)
			if(!(--deg[G[v][i].to])) q.push(G[v][i].to); 
	}
}

int id(int x, int y) { return (x-1)*m+y; }
int main() {
	freopen("pvz.in", "r", stdin);
	freopen("pvz.out", "w", stdout);

	n = read(), m = read();
	o = id(n, m), s = ++o, t = ++o;
	for(int i = 1; i <= n; ++i)
	for(int j = 1, v, w; j <= m; ++j) {
		v = read(), w = read(), val[id(i, j)] = v;		
		if(v > 0) add(s, id(i, j), v);
		else add(id(i, j), t, -v);
		if(j != m) add(id(i, j), id(i, j+1), INF);
		for(int r, c; w--;) 
			r = read()+1, c = read()+1,
			add(id(r, c), id(i, j), INF);

	}
	
	topsort();
	printf("%d\n", sum-maxflow());
	return 0;
}
