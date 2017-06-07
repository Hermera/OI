#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e5+5;
struct Heap {
	struct Data {
		int l, r, d, top;
		ll w, tag;
	} t[maxn];
	int tot;
	
	int node(int top, ll w) {
		t[++tot] = (Data){ 0, 0, 0, top, w, 0 };
		return tot;
	}
	
	void pushdown(int o) {
		if(!t[o].tag) return;
		t[o].w += t[o].tag;
		if(t[o].l) t[t[o].l].tag += t[o].tag;
		if(t[o].r) t[t[o].r].tag += t[o].tag;
		t[o].tag = 0;
	}
	
	int merge(int x, int y) {
		if(!x || !y) return x|y;
		pushdown(x);
		pushdown(y);
		
		if(t[x].w > t[y].w) swap(x, y);
		t[x].r = merge(t[x].r, y);
		
		if(t[t[x].l].d < t[t[x].r].d) swap(t[x].l, t[x].r);
		t[x].d = t[t[x].r].d+1;
		return x;
	}
	
	void pop(int &o) {
		pushdown(o);
		o = merge(t[o].l, t[o].r);
	}
} T;

struct Line { int top; ll w; };
vector <Line> g[maxn];

int N, M, cnt, fail, head[maxn], root[maxn], deep[maxn];
struct Edge { int next, to; } data[maxn<<1];
ll dp[maxn];

void add(int x, int y) {
	data[++cnt] = (Edge){ head[x], y }; head[x] = cnt;
}

#define for_edge(x) for(int i = head[x]; i; i = data[i].next) if(data[i].to != fa)
void dfs(int x, int fa) {
	ll sum = 0;
	for_edge(x) {
		Edge &e = data[i];
		deep[e.to] = deep[x]+1;
		dfs(e.to, x);
		
		if(fail && x != 1) return;
		sum += dp[e.to];
	}
	
	for(int i = 0; i < g[x].size(); ++i) 
		root[x] = T.merge(root[x], T.node(g[x][i].top, g[x][i].w+sum));
	
	for_edge(x) {
		Edge &e = data[i];
		T.t[root[e.to]].tag += sum-dp[e.to];
		root[x] = T.merge(root[x], root[e.to]);
	}
	
	while(root[x] && deep[T.t[root[x]].top] >= deep[x]) T.pop(root[x]);
	if(!root[x] && x != 1) {
		fail = true;
		return;
	}
	
	T.pushdown(root[x]);
	dp[x] = T.t[root[x]].w;
}

int main() {
	freopen("671D.in", "r", stdin);

	N = read(), M = read();
	if(N == 1) return printf("0\n"), 0;
	
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
	for(int i = 1, u, v, c; i <= M; ++i) {
		u = read(), v = read(), c = read();
		g[u].push_back((Line){ v, c });
	}
	
	memset(dp, 63, sizeof(dp));
	dfs(1, 0);
	
	if(fail) printf("-1\n");
	else {
		ll ans = 0;
		for(int i = head[1]; i; i = data[i].next) 
			ans += dp[data[i].to];
		printf("%lld\n", ans);
	}
	return 0;
}
