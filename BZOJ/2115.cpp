#include <cstdio>
#include <algorithm>
#define bin(x) (1LL<<(x))
using namespace std;
typedef long long ll;
ll read() {
	char ch = getchar(); ll x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int n, m, t, cnt, h[maxn];
ll a[maxn], bas[maxn], val[maxn], ans;
bool vis[maxn];

struct Data { int next, to; ll w; } g[maxn<<1];
void add(int x, int y, ll w) {
	g[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
}

void dfs(int x, int fa) {
	vis[x] = 1;
	for(int i = h[x], f = 1; i; i = g[i].next) {
		Data &e = g[i];
		if(!vis[e.to]) val[e.to] = val[x]^e.w, dfs(e.to, x);
		else a[++m] = val[x]^val[e.to]^e.w;
	}
}

void gauss() {
	for(int i = 60; ~i; --i) {
		int j = t+1;
		while(!(bin(i) & a[j]) && j <= m) ++j;
		if(j > m) continue;
		swap(a[++t], a[j]);
		for(int k = 1; k <= m; ++k)
			if(k != t && (a[k] & bin(i))) a[k] ^= a[t]; 
	}
}

int main() {
	n = read(), m = read();
	for(ll u, v, w; m--;) 
		u = read(), v = read(), w = read(),
		add(u, v, w), add(v, u, w);

	dfs(1, 0);
	gauss(), ans = val[n];
	for(int i = 1; i <= t; ++i)
		ans = max(ans, ans ^ a[i]);
	printf("%lld\n", ans);
	return 0;
}
	
