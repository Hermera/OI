#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int N = 2e5+5, M = 2e6+5;
int n, m, dfn, all, now, cnt, ed = 1;
int g[N], nxt[N], v[N], w[N], ok[N], f[N], val[N];
int siz[N], top[N], son[N], fa[N], loc[N], seq[N];
int G[N], NXT[M], V[2][M], W[M], ED;
ll sw[N], sdw[N], sew[N], sedw[N];

void add(int x, int y, int z) {
	v[++ed] = y, w[ed] = z, nxt[ed] = g[x], ok[ed] = 1, g[x] = ed;
}

void ADD(int x, int y, int z, int w) {
	V[0][++ED] = y; V[1][ED] = z; W[ED] = w; NXT[ED] = G[x]; G[x] = ED;
}

/**********The Tree Divide**********/
void findroot(int x, int p) {
	siz[x] = 1, f[x] = 0;
	for(int i = g[x]; i; i = nxt[i]) if(ok[i] && v[i] != p) {
		findroot(v[i], x);
		siz[x] += siz[v[i]];
		f[x] = max(f[x], siz[v[i]]);
	}
	f[x] = max(f[x], all-siz[x]);
	if(f[x] < f[now]) now = x;
}

void dfs(int x, int p, int dis) {
	ADD(x, now, cnt, dis);
	for(int i = g[x]; i; i = nxt[i])
		if(ok[i] && v[i] != p) dfs(v[i], x, dis+w[i]);
}

void solve(int x) {
	for(int i = g[x]; i; i = nxt[i]) 
		if(ok[i]) ++cnt, dfs(v[i], x, w[i]);
	for(int i = g[x]; i; i = nxt[i]) 
		if(ok[i]) {
			ok[i^1] = 0;
			f[0] = all = siz[v[i]];
			findroot(v[i], now = 0);
			solve(now);
		}
}
/***********************************/


/*******The HeavyLight Tree*********/
void dfs(int x) {
	siz[x] = 1;
	for(int i = g[x]; i; i = nxt[i]) 
		if(v[i] != fa[x]) {
			fa[v[i]] = x, dfs(v[i]), siz[x] += siz[v[i]];
			if(siz[v[i]] > siz[son[x]]) son[x] = v[i];
		}
}

void dfs(int x, int tp) {
	top[x] = tp; seq[loc[x] = ++dfn] = x;
	if(son[x]) dfs(son[x], tp);
	for(int i = g[x]; i; i = nxt[i])
		if(v[i] != son[x] && v[i] != fa[x]) dfs(v[i], v[i]);
}

#define mid (l+r>>1)
struct Segment {
	ll t[N<<2], p[N<<2];
	void upd(int o, int c) { t[o] += c, p[o] += c; }
	void pushdown(int o) {
		if(p[o]) upd(o<<1, p[o]), upd(o<<1|1, p[o]);
		p[o] = 0;
	}

	void add(int o, int l, int r, int L, int R, int c) {
		if(L <= l && r <= R) return upd(o, c);
		if(R < l || r < L) return;
		pushdown(o);
		add(o<<1, l, mid, L, R, c);
		add(o<<1|1, mid+1, r, L, R, c);
		t[o] = max(t[o<<1], t[o<<1|1]);
	}
	
	int getroot() {
		int o = 1, l = 1, r = n;
		while(l < r) {
			pushdown(o);
			if(t[o<<1|1]*2 >= t[1]) l = mid+1, o = o<<1|1;
			else r = mid, o = o<<1;
		}
		return seq[l];
	}
} T;
/***********************************/

void modify(int x, int y){
	val[x] += y;
	for(int i = G[x]; i; i = NXT[i]) {
		sw[V[0][i]] += y, sdw[V[0][i]] += (ll)W[i]*y;
		sew[V[1][i]] += y, sedw[V[1][i]] += (ll)W[i]*y;
	} 
	for(int i = x; i; i = fa[top[i]])
		T.add(1, 1, n, loc[top[i]], loc[i], y);
}

ll query(int x) {
	ll ans = sdw[x];
	for(int i = G[x]; i; i = NXT[i]) {
		ans += (sw[V[0][i]]-sew[V[1][i]]+val[V[0][i]])*W[i];
		ans += sdw[V[0][i]]-sedw[V[1][i]];
	}
	return ans;
}

int main() {
	n = read(), m = read();
	for(int i = 1, x, y, w; i < n; ++i) {
		x = read(), y = read(), w = read();
		add(x, y, w);
		add(y, x, w);
	}
	
	f[0] = all = n;
	findroot(1, now = 0);
	solve(now);
	
	dfs(1);
	dfs(1, 1);
	while(m--) {
		int x = read(), y = read();
		modify(x, y);
		printf("%lld\n", query(T.getroot()));
	}
	return 0;
}
