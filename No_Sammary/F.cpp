#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 3e5+5;
const int L = 20;
const ll INF = 1e16;

typedef pair<int, int> pi;
#define fir first
#define sec second


int n, m, s;
bool inq[N];
ll dis[N];
vector <pi> G[N];

queue <int> q;
void SPFA(int s) {
	for(int i = 1; i <= n; ++i)
		dis[i] = INF;
	dis[s] = 0, q.push(s);
	while(!q.empty()) {
		int v = q.front(); q.pop(), inq[v] = 0;
		for(int i = 0; i < G[v].size(); ++i) {
			pi &e = G[v][i];
			if(dis[e.fir] > dis[v] + e.sec) {
				dis[e.fir] = dis[v] + e.sec;
				if(!inq[e.fir]) inq[e.fir] = 1, q.push(e.fir);
			}
		}
	}
}


vector <int> A[N], B[N];
int rk[N], dep[N], deg[N];
int fa[N][L];

int topsort(int s) {
	int h = 1, t = 0;
	rk[++t] = s;
	while(h <= t) {
		int v = rk[h++];
		for(int i = 0; i < A[v].size(); ++i)
			if(!(--deg[A[v][i]])) rk[++t] = A[v][i];
	}
	return t;
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	int d = dep[x] - dep[y];
	for(int i = L-1; ~i; --i)
		if(d & (1<<i)) x = fa[x][i];
	if(x == y) return x;
	for(int i = L-1; ~i; --i)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

int p[N], siz[N];
bool cmp(int x, int y) {
	return dep[x] > dep[y];
}


int main() {
	n = read(), m = read(), s = read();
	for(int u, v, w; m--; ) {
		u = read(), v = read(), w = read();
		G[u].push_back(pi(v, w));
		G[v].push_back(pi(u, w));
	}
	
	SPFA(s);
	for(int i = 1; i <= n; ++i)
	for(int j = 0; j < G[i].size(); ++j) {
		pi &e = G[i][j];
		if(dis[i] + e.sec == dis[e.fir])
			A[i].push_back(e.fir),
			B[e.fir].push_back(i),
			++deg[e.fir];
	}
	
	n = topsort(s);
	for(int i = 2; i <= n; ++i) {
		int x = rk[i];
		fa[x][0] = B[x][0];
		for(int i = 1; i < B[x].size(); ++i)
			fa[x][0] = LCA(fa[x][0], B[x][i]);
		dep[x] = dep[fa[x][0]]+1;
		for(int i = 1; i < L; ++i)
			fa[x][i] = fa[fa[x][i-1]][i-1];
	}
	
	for(int i = 1; i <= n; ++i) p[i] = rk[i];
	sort(p + 1, p + 1 + n, cmp);
	for(int i = 1; i <= n; ++i)
		++siz[p[i]], siz[fa[p[i]][0]] += siz[p[i]];
	
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		if(p[i] != s) ans = max(ans, siz[p[i]]);
	printf("%d\n", ans);
	return 0;
}
