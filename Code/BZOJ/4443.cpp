#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 505, oo = 1e9;
int n, m, k, s, t, a[maxn][maxn], level[maxn], iter[maxn];
struct Edge { int to, cap, rev; };
vector <Edge> G[maxn];
void add(int x, int y, int cap) {
	G[x].push_back((Edge){ y, cap, G[y].size() });
	G[y].push_back((Edge){ x, 0, G[x].size()-1 });
}

queue <int> q;
bool bfs() {
	for(int i = s; i <= t; ++i) level[i] = -1, iter[i] = 0;
	level[s] = 0, q.push(s);
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i) {
			Edge &e = G[v][i];
			if(e.cap && level[e.to] < 0)
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
			int d = dfs(e.to, min(e.cap, f));
			if(d) { 
				e.cap -= d, G[e.to][e.rev].cap += d; 
				return d; 
			}
		}
	}
	return 0;
}

int maxflow() {
	int flow = 0, now;
	while(bfs())
		while((now = dfs(s, oo))) flow += now;
	return flow;
}

bool judge(int x) {
	s = 0, t = n+m+1;
	for(int i = s; i <= t; ++i) G[i].clear();
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		if(a[i][j] <= x) add(i, n+j, 1); 
	for(int i = 1; i <= n; ++i) add(s, i, 1);
	for(int i = 1; i <= m; ++i) add(i+n, t, 1);	
	return maxflow() >= k;
}

int main() {
	scanf("%d%d%d", &n, &m, &k), k = n-k+1;
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		scanf("%d", &a[i][j]);
	
	int l = 1, r = oo, ans;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(judge(mid)) ans = mid, r = mid-1;
		else l = mid+1;
	}
	printf("%d\n", ans);
	return 0;
}
