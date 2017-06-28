#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 60005;
int n, m, k;
namespace Tree {
	int root, all, cnt, tot, st, ed, anslen, anssum;
	int head[maxn], siz[maxn], mx[maxn], dep[maxn], dis[maxn], son[maxn];
	int len[maxn], sum[maxn], nowlen[maxn], nowsum[maxn];
	struct Data { int next, to, w; } G[maxn];
	bool vis[maxn];
	void add(int x, int y, int w) {
		G[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
	}

	void getroot(int x, int fa) {
		siz[x] = 1, mx[x] = 0;
		for(int i = head[x]; i; i = G[i].next) {
			Data &e = G[i];
			if(e.to != fa && !vis[e.to]) 
				getroot(e.to, x), 
				siz[x] += siz[e.to],
				mx[x] = max(mx[x], siz[e.to]);
		}
		mx[x] = max(mx[x], all-siz[x]);
		if(mx[x] < mx[root]) root = x;
	}
	
	void upd(int &a, int b, int &c, int d) {
		if(b > a) a = b, c = d;
		else if(a == b) c += d;
	}
	
	void dfs(int x, int fa) {
		if(dep[x] > k) return;
		son[++tot] = x;
		upd(nowlen[dep[x]], dis[x], nowsum[dep[x]], 1);
		upd(anslen, len[k-dep[x]]+dis[x], anssum, sum[k-dep[x]]);
		for(int i = head[x], y; i; i = G[i].next) 
			if((y = G[i].to) != fa && !vis[G[i].to]) 
				dis[y] = dis[x]+G[i].w,
				dep[y] = dep[x]+1,
				dfs(y, x);
	}		
	
	void work(int x) {
		vis[x] = 1;
		dis[x] = dep[x] = tot = 0;
		for(int i = head[x], y; i; i = G[i].next) 
			if(!vis[y = G[i].to]) {
				st = tot+1, dep[y] = 1, dis[y] = G[i].w;
				dfs(y, 0), ed = tot;
				for(int j = st, v; j <= ed; ++j) 
					v = dep[son[j]],
					upd(len[v], nowlen[v], sum[v], nowsum[v]),
					nowlen[v] = nowsum[v] = 0;
			}
		
		for(int i = 1, v; i <= tot; ++i) {
			if((v = dep[son[i]]) == k) upd(anslen, dis[son[i]], anssum, 1);
			nowlen[v] = len[v] = 0;
			nowsum[v] = sum[v] = 0;
		}
	}
	
	void solve(int x) {
		work(x);
		for(int i = head[x]; i; i = G[i].next) 
			if(!vis[G[i].to]) 
				all = mx[0] = siz[x],
				getroot(G[i].to, root = 0),
				solve(root); 
	}
	
	void done() {
		siz[0] = mx[0] = all = n;
		getroot(1, root = 0);
		solve(root);
		printf("%d %d\n", anslen, anssum);
	}	
};

struct Edge {
	int to, w;
	bool operator <(const Edge &b) const {
		return to < b.to;
	}
};

namespace Graph {
	int dis[maxn], inq[maxn], vis[maxn];
	vector <Edge> G[maxn];
	
	queue <int> q;
	void spfa(int s) {
		memset(dis, 63, sizeof(dis));
		q.push(s), dis[s] = 0;
		while(!q.empty()) {
			int v = q.front(); q.pop(), inq[v] = 0;
			for(int i = 0; i < G[v].size(); ++i) {
				Edge &e = G[v][i];
				if(dis[v]+e.w < dis[e.to]) {
					dis[e.to] = dis[v]+e.w;
					if(!inq[e.to]) q.push(e.to), inq[e.to] = 1;
				}
			}
		}
	}
	
	void build(int x) {
		vis[x] = 1;
		for(int i = 0; i < G[x].size(); ++i) {
			Edge &e = G[x][i];
			if(!vis[e.to] && dis[x]+e.w == dis[e.to]) 
				Tree::add(x, e.to, e.w),
				Tree::add(e.to, x, e.w),
				build(e.to);
		}
	}
	
	void init() {
		for(int i = 1, x, y, w; i <= m; ++i) 
			x = read(), y = read(), w = read(),
			G[x].push_back((Edge){ y, w }),
			G[y].push_back((Edge){ x, w });
		for(int i = 1; i <= n; ++i) 
			sort(G[i].begin(), G[i].end());
		spfa(1);
		build(1);
	}
};


int main() {
	n = read(), m = read(), k = read()-1;
	Graph::init();
	Tree ::done();
	return 0;
}
