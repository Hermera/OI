#include <queue>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 4e4 + 5;

struct Data {
	int next, to;
} g[N << 1];
int fa[N], h[N], cnt;
int n, o;

void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
	g[++cnt] = (Data) { h[y], x }; h[y] = cnt;
}

void dfs(int x) {
	for (int i = h[x]; i; i = g[i].next)
		if (g[i].to != fa[x]) 
			fa[g[i].to] = x, dfs(g[i].to);
}


int pa[N];
int getpa(int x) {
	return pa[x] == x ? x : pa[x] = getpa(pa[x]);
}


struct node {
	int id, siz;
	ll sum;
	
	node() {}
	node(int _i, int _z, ll _s): id(_i), siz(_z), sum(_s) {}
	bool operator <(const node &b) const {
		return sum * b.siz < b.sum * siz;
	}
};
priority_queue <node> q;

ll sum[N], ans;
int siz[N], pre[N], suf[N], nxt[N];
int idx, tim;


int main() {
	n = read(), o = read();
	for (int i = 1; i <= n; ++i) sum[i] = read();
	for (int i = 2; i <= n; ++i)
		add(read(), read());
	
	dfs(o);
	for (int i = 1; i <= n; ++i) {
		q.push(node(i, 1, sum[i]));
		pre[i] = suf[i] = pa[i] = i, siz[i] = 1;
	}
	
	idx = n;
	while (!q.empty()) {
		node now = q.top(); q.pop();
		if (getpa(now.id) != now.id) 
			continue;
		
		int u = now.id;
		int v = getpa(fa[u]);
		if (v) {
			++idx;
			pa[idx] = idx;
			fa[idx] = fa[v];
			pa[u] = pa[v] = idx;
			nxt[suf[v]] = pre[u];
			pre[idx] = pre[v], suf[idx] = suf[u];
			siz[idx] = siz[u] + siz[v];
			sum[idx] = sum[u] + sum[v];
			q.push(node(idx, siz[idx], sum[idx]));
		}
	}
	
	for (int i = 1; i <= n; ++i)
		ans += 1LL * i * sum[o], o = nxt[o];
	printf("%lld\n", ans);
	return 0;
}
