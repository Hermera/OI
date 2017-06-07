#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 2005;
const int INF = 1e9;
const double eps = 1e-6;
struct Edge { int to, rev; double cap; };
vector <Edge> G[maxn];
int n, m, s, t, p, ans, level[maxn], iter[maxn];

void add(int x, int y, double cap) {
	G[x].push_back((Edge){ y, G[y].size(), cap });
	G[y].push_back((Edge){ x, G[x].size()-1, 0 });
}

queue <int> q;
bool bfs() {
	for(int i = s; i <= t; ++i) level[i] = -1, iter[i] = 0;
	q.push(s), level[s] = 0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i) {
			Edge &e = G[v][i];
			if(level[e.to] < 0 && e.cap) 
				level[e.to] = level[v]+1, q.push(e.to);
		}
	}
	return ~level[t];
}

double dfs(int v, double f) {
	if(v == t || !f) return f;
	for(int &i = iter[v]; i < G[v].size(); ++i) {
		Edge &e = G[v][i];
		if(e.cap && level[e.to] > level[v]) {
			double d = dfs(e.to, min(f, e.cap));
			if(d) {
				e.cap -= d, G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

struct Link { int x, y; double w; } e[maxn];
double maxflow(double x) {
	double flow = 0;
	for(int i = s; i <= t; ++i) G[i].clear();
	for(int i = 1; i <= m; ++i) add(e[i].x, e[i].y, min(x, e[i].w));
	while(bfs())
		for(double f; (f = dfs(s, INF)) > 0; flow += f);
	return flow;
}

int main() {
	freopen("3130.in", "r", stdin);

	scanf("%d%d%d", &n, &m, &p), s = 1, t = n;
	for(int i = 1; i <= m; ++i) 
		scanf("%d%d%lf", &e[i].x, &e[i].y, &e[i].w);
	ans = maxflow(INF);
	printf("%d\n", ans);
	
	double l = 0, r = INF;
	while(r-l > eps) {
		double mid = (l+r)/2;
		if(maxflow(mid) == ans) r = mid;
		else l = mid;
	}
	printf("%lf\n", l*p);
	return 0;
}
