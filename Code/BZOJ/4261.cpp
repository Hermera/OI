#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 155;
const int M = N * N;
const int inf = 1e9;

struct Edge {
	int to, rev, cap, cost;
};
vector <Edge> g[M];

int s, t, idx, sum, flow, cost;
int dis[M], vis[M], it[M];
void add(int x, int y, int c, int w) {
	g[x].push_back((Edge) { y, g[y].size(), c, w });
	g[y].push_back((Edge) { x, g[x].size() - 1, 0, -w });
}

queue <int> q;
bool spfa() {
	for (int i = 1; i <= idx; ++i)
		dis[i] = inf, vis[i] = it[i] = 0;
	q.push(s), dis[s] = 0;
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int i = 0; i < g[v].size(); ++i) {
			Edge &e = g[v][i];
			if (e.cap && dis[e.to] > dis[v] + e.cost) {
				dis[e.to] = dis[v] + e.cost;
				if (!vis[e.to]) q.push(e.to);
			}
		}
	}
	return dis[t] < inf;
}

int dfs(int v, int f) {
	if (v == t) return f;
	vis[v] = 1;
	for (int &i = it[v]; i < g[v].size(); ++i) {
		Edge &e = g[v][i];
		if (e.cap && !vis[e.to] && dis[e.to] == dis[v] + e.cost) {
			int d = dfs(e.to, min(e.cap, f));
			if (d) {
				e.cap -= d, g[e.to][e.rev].cap += d;
				cost += e.cost * d;
				return d;
			}
		}
	}
	return 0;
}

void costflow() {
	while (spfa()) {
		for (int f; f = dfs(s, inf);) flow += f;
	}
}



int n, m, tot;
int a[N][N], v[N][N], h[N][N], z[N][N];
const int fx[] = { 0, 1, 0, -1 };
const int fy[] = { 1, 0, -1, 0 };

int main() {
	freopen("4261.in", "r", stdin);

	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
			a[i][j] = !read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			v[i][j] = read();
			h[i][j] = ++idx;
			z[i][j] = ++idx;
		}

	s = ++idx, t = ++idx;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) if (a[i][j]) {
			add(h[i][j], z[i][j], 1, v[i][j]);
			add(z[i][j], h[i][j], 1, v[i][j]);
			++tot, sum += v[i][j];

			if (~ (i + j) & 1) {
				add(s, h[i][j], 1, 0);
				add(s, z[i][j], 1, 0);
				for(int d = 0; d < 4; ++d) {
					int nx = i + fx[d], ny = j + fy[d];
					if (!nx || !ny || nx > n || ny > m) continue;
					if (d & 1) add(z[i][j], z[nx][ny], 1, 0);
					else add(h[i][j], h[nx][ny], 1, 0);
				}
			} else {
				add(h[i][j], t, 1, 0);
				add(z[i][j], t, 1, 0);
			}
		}


	costflow();

	int ans = flow == tot ? sum - cost : -1;
	printf("%d\n", ans);
	return 0;
}