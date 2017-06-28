#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
const ll oo = 1e18;
int n, m, t, k, cnt;
int dep[maxn], h[maxn], fa[maxn], rt[maxn], p[maxn];
ll dis[maxn], up[maxn];
bool ok[maxn], vis[maxn];

struct Data { int next, to, w; } g[maxn<<1];
void add(int x, int y, int w) {
	g[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
}

void dfs(int x, int y) {
	rt[x] = y;
	for(int i = h[x]; i; i = g[i].next)
		if(g[i].to != fa[x]) {
			Data &e = g[i];
			dep[e.to] = dep[x]+1;
			dis[e.to] = dis[x]+e.w;
			fa[e.to] = x;
			if(x == 1) dfs(e.to, e.to);
			else dfs(e.to, y);
		}
}

struct ele {
	ll len; int to;
	ele(ll x = 0, int y = 0): len(x), to(y) {}
	bool operator <(const ele &b) const { 
		return len != b.len ? len < b.len : to < b.to; 
	}
} arm[maxn], foe[maxn];

void mark(int x) {
	bool leaf = 1;
	for(int i = h[x]; i; i = g[i].next) 
		if(g[i].to != fa[x]) {
			mark(g[i].to), leaf = 0,
			up[x] = max(up[x], up[g[i].to]-g[i].w);
			if(up[g[i].to] >= g[i].w) vis[x] = 1;
		}
	ok[x] = 1;
	if(!vis[x]) {
		if(leaf) ok[x] = 0;
		else for(int i = h[x]; i; i = g[i].next)
			if(g[i].to != fa[x]) ok[x] &= ok[g[i].to];
	}
}
	

bool judge(ll x) {
	t = k = 0;
	for(int i = 1; i <= n; ++i) ok[i] = up[i] = vis[i] = 0;
	for(int i = 1; i <= m; ++i) 
		if(dis[p[i]] > x) up[p[i]] = x;
		else arm[++t] = ele(x-dis[p[i]], rt[p[i]]);
		
	mark(1);
	for(int i = h[1]; i; i = g[i].next)
		if(!ok[g[i].to]) foe[++k] = ele(dis[g[i].to], g[i].to);
	sort(arm+1, arm+1+t);
	sort(foe+1, foe+1+k);
	for(int i = 1, j = 1; i <= t; ++i) {
		if(!ok[arm[i].to]) ok[arm[i].to] = 1;
		else if(foe[j].len <= arm[i].len) ok[foe[j].to] = 1;
		while(j <= k && ok[foe[j].to]) ++j;
		if(j > k) return 1;
	}
	return 0;
}

int main() {
	freopen("blockade.in", "r", stdin);
	freopen("blockade.out", "w", stdout);

	n = read();
	for(int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(),
		add(u, v, w), add(v, u, w);
	dfs(1, 1);
	m = read();
	for(int i = 1; i <= m; ++i) p[i] = read();

	ll l = 0, r = oo, ans = oo;
	while(l <= r) {
		ll mid = (l+r)>>1;
		if(judge(mid)) ans = mid, r = mid-1;
		else l = mid+1;
	}
	printf("%lld\n", ans);
	return 0;
}
	
	
