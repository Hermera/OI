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

const int maxn = 1e5+5;
int n, m, t, k, cnt, sum, root;
int h[maxn], f[maxn], q[maxn], dep[maxn], siz[maxn], fa[maxn];
bool vis[maxn];
ll ans;

struct Data { int next, to, w; } g[maxn<<1];
void add(int x, int y, int w) {
	g[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
}

void getroot(int x, int p) {
	siz[x] = 1, f[x] = 0;
	for(int i = h[x]; i; i = g[i].next) {
		Data &e = g[i];
		if(!vis[e.to] && e.to != p) {
			getroot(e.to, x);
			siz[x] += siz[e.to];
			f[x] = max(f[x], siz[e.to]);
		}
	}
	f[x] = max(f[x], sum-siz[x]);
	if(f[x] < f[root]) root = x;
}

void dfs(int x, int p) {
	q[++t] = dep[x];
	for(int i = h[x]; i; i = g[i].next) {
		Data &e = g[i];
		if(e.to != p && !vis[e.to]) 
			dep[e.to] = dep[x]+e.w, dfs(e.to, x);
	}
}

ll work(int x, int fir) {
	ll ret = 0;
	dep[x] = fir, t = 0, dfs(x, 0);
	sort(q+1, q+1+t);
	for(int l = 1, r = t; l < r;)
		if(q[l]+q[r] <= k) ret += r-l, ++l;
		else --r;
	return ret;
}

void solve(int x) {
	ans += work(x, 0), vis[x] = 1;
	for(int i = h[x]; i; i = g[i].next) if(!vis[g[i].to]){
		Data &e = g[i];
		ans -= work(e.to, e.w);
		sum = siz[e.to], getroot(e.to, root = 0);
		solve(root);
	}
}

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int u, v, w; m--; ) 
		u = read(), v = read(), w = read(),
		add(u, v, w), add(v, u, w), fa[Find(u)] = Find(v);
	k = read();
	
	for(int i = 1; i <= n; ++i) ++siz[Find(i)];
	for(int i = 1; i <= n; ++i) if(!vis[i]) {
		sum = f[0] = siz[Find(i)];
		getroot(i, root = 0);
		solve(root);
	}
	printf("%lld\n", ans);
	return 0;
}
