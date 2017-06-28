#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4005;
const int maxm = 600005;

int n, m, s, t, cnt, tot, top, tim;
int h[maxn], iter[maxn], level[maxn], dfn[maxn], low[maxn], scc[maxn], stack[maxn];
struct Data { int next, to, from, rev, cap; } g[maxm];

void add(int x, int y, int c) {
	++cnt, g[cnt] = (Data){ h[x], y, x, cnt+1, c }; h[x] = cnt;
	++cnt, g[cnt] = (Data){ h[y], x, y, cnt-1, 0 }; h[y] = cnt;
}

queue <int> q;
bool bfs() {
	for(int i = 1; i <= n; ++i) iter[i] = h[i], level[i] = -1;
	q.push(s), level[s] = 0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = h[v]; i; i = g[i].next) {
			Data &e = g[i];
			if(e.cap && level[e.to] < 0)
				level[e.to] = level[v]+1, q.push(e.to);
		}
	}
	return ~level[t];
}

int dfs(int v, int f) {
	if(v == t || !f) return f;
	for(int &i = iter[v]; i; i = g[i].next) {
		Data &e = g[i];
		if(e.cap && level[v] < level[e.to]) {
			int d = dfs(e.to, min(f, e.cap));
			if(d) {
				e.cap -= d, g[e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++tim;
	stack[++top] = x;
	for(int i = h[x]; i; i = g[i].next) if(g[i].cap) {
		Data &e = g[i];
		if(!dfn[e.to]) tarjan(e.to), low[x] = min(low[x], low[e.to]);
		else if(!scc[e.to]) low[x] = min(low[x], low[e.to]);
	}
	if(low[x] == dfn[x]) {
		++tot;
		while(top) {
			int v = stack[top--];
			scc[v] = tot;
			if(v == x) break;
		}
	}
}

int main() {
	n = read(), m = read();
	s = read(), t = read();
	for(int x, y, i = 1; i <= m; ++i) 
		x = read(), y = read(), add(x, y, read());
		
	while(bfs()) while(dfs(s, t));
	for(int i = 1; i <= n; ++i) 
		if(!dfn[i]) tarjan(i);

	for(int i = 1; i <= cnt; i += 2) {
		int x = g[i].from, y = g[i].to, z = !g[i].cap;
		printf("%d ",  scc[x] != scc[y] && z);
		printf("%d\n", scc[x] == scc[s] && scc[y] == scc[t] && z);
	}
	return 0;
}
