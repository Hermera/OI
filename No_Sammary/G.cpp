#include <bits/stdc++.h>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 4e5+5;
const int M = N * 25;
const int L = 19;

typedef long long ll;
typedef pair<ll, int> pi;
#define fir first
#define sec second

void cmax(int &x, int y) {
	x = x < y ? y : x;
}


int cnt, h[N];
struct Data { 
	int next, to, w; 
} g[N << 1];
void add(int x, int y, int w) {
	g[++cnt] = (Data) { h[x], y, w }; h[x] = cnt;
	g[++cnt] = (Data) { h[y], x, w }; h[y] = cnt;
}


ll dis[N][L];
int all, cen, low[N], siz[N], vis[N];
int getroot(int x, int p) {
	low[x] = 0, siz[x] = 1;
	for(int v, i = h[x]; i; i = g[i].next)
		if(!vis[g[i].to] && g[i].to != p) {
			getroot(v = g[i].to, x);
			siz[x] += siz[v];
			cmax(low[x], siz[v]);
		}
	cmax(low[x], all - siz[x]);
	if(low[x] < low[cen]) cen = x;
}

int getsize(int x, int p) {
	int ret = 1;
	for(int i = h[x]; i; i = g[i].next)
		if(!vis[g[i].to] && g[i].to != p)
			ret += getsize(g[i].to, x);
	return ret;
}

void getroot(int &x) {
	all = getsize(x, 0);
	getroot(x, cen = 0);
	x = cen;
}

void getship(int x, int p, int d) {
	for(int i = h[x]; i; i = g[i].next)
		if(!vis[g[i].to] && g[i].to != p) {
			Data &e = g[i];
			dis[e.to][d] = dis[x][d] + e.w;
			getship(e.to, x, d);
		}
}


pi val[M], sum[M];
int son[M][3], tot[M];
int ori[M], fin[M], tim, idx;
int build(int x, int d) {
	getroot(x);
	vis[x] = 1;
	getship(x, 0, d);
	ori[x] = ++tim;
	for(int i = h[x]; i; i = g[i].next) 
		if(!vis[g[i].to]) {
			int v = g[i].to;
			son[x][tot[x]++] = (build(v, d+1));
		}
	fin[x] = ++tim;
	return x;
}


int newnode(int x) {
	int p = ++idx;
	ori[p] = ori[x], fin[p] = fin[x];
	val[p] = val[x], sum[p] = sum[x];
	for(int i = 0; i < tot[x]; ++i)
		son[p][i] = son[x][i];
	tot[p] = tot[x];
	return p;
}

void update(int &o, int x, int d) {
	o = newnode(o);
	val[o].fir += dis[x][d];
	val[o].sec += 1;
	for(int i = 0; i < tot[o]; ++i) {
		int &v = son[o][i];
		if(ori[v] <= ori[x] && ori[x] <= fin[v]) {
			update(v, x, d+1);
			sum[v].fir += dis[x][d];
			sum[v].sec += 1;
		}
	}
}

ll query(int o, int x, int d) {
	ll ans = val[o].fir;
	for(int i = 0; i < tot[o]; ++i) {
		int v = son[o][i];
		if(ori[v] <= ori[x] && ori[x] <= fin[v]) {
			ans -= sum[v].fir;
			ans += query(v, x, d+1);
			ans += 1LL * (val[o].sec - sum[v].sec) * dis[x][d];
		}
	}
	return ans;
}


const int mod = 1 << 30;
int n, q, a[N], root[N];
ll last;

vector <pi> now;
vector <pi> lik[N];
void dfs(int x, int p) {
	now.clear();
	for(int i = 0; i < lik[x].size(); ++i)
		if(lik[x][i].sec != p) now.push_back(lik[x][i]);
	
	int o = x, ran = now.size();
	for(int i = 0; i < ran; ++i) {
		add(o, now[i].sec, now[i].fir);
		if(i < ran-2) { 
			add(o, ++idx, 0);
			a[idx] = a[o], o = idx;
		}
	}
	
	for(int i = 0; i < lik[x].size(); ++i)
		if(lik[x][i].sec != p) dfs(lik[x][i].sec, x);
} // rebuild the tree, and make each node's deg <= 2


int load() {
	return read() ^ last;
}

int main() {
	n = read(), q = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 2; i <= n; ++i) {
		int u = read(), v = read(), w = read();
		lik[u].push_back(pi(w, v));
		lik[v].push_back(pi(w, u));
	}
	
	idx = n;
	dfs(1, 0);
	low[0] = n, all = n;

	root[0] = build(1, 0);
	for(int i = 1; i <= n; ++i) 
		update(root[i] = root[i-1], a[i], 0);
	
	for(int i = 1; i <= q; ++i) {
		int type = read();
		if(type == 1) {
			int l = load(), r = load(), v = load();
			last = query(root[r], v, 0) - query(root[l-1], v, 0);
			printf("%lld\n", last), last %= mod;
		} else {
			int x = load();
			swap(a[x], a[x+1]);
			update(root[x] = root[x-1], a[x], 0);
		}
	}
	return 0;
}
