#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

void cmin(int &x, int y) { x = x > y ? y : x; }
void cmax(int &x, int y) { x = x < y ? y : x; }

const int N = 1e5+5;
const int L = 20;

struct BIT {
	int len;
	vector <int> t;
	void init(int x) {
		len = ++x;
		t.resize(x + 1);
	}
	
	void modify(int x, int v) {
		if(!(++x)) return;
		for(; x <= len; x += x&-x) t[x] += v;
	}
	
	int query(int x) {
		int ret = 0;
		x = min(++x, len);
		for(; x; x -= x&-x) ret += t[x];
		return ret;
	}
} val[N], sum[N];


int n, m, cnt, h[N], w[N], vis[N];
struct Data { int next, to; } g[N<<1];
void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
	g[++cnt] = (Data) { h[y], x }; h[y] = cnt;
}

int root, all, low[N], siz[N];
int dis[N][L], fa[N][L], dep[N], len;

void getroot(int x, int p) {
	siz[x] = 1, low[x] = 0;
	for(int v, i = h[x]; i; i = g[i].next) 
		if(g[i].to != p && !vis[g[i].to]) {
			getroot(v = g[i].to, x);
			cmax(low[x], siz[v]);
			siz[x] += siz[v];
		}
	cmax(low[x], all - siz[x]);
	if(low[x] < low[root]) root = x;
}

void getship(int x, int tp, int p, int d) {
	cmax(len, d);
	for(int v, i = h[x]; i; i = g[i].next)
		if(g[i].to != p && !vis[g[i].to]) {
			++dep[v = g[i].to];
			fa[v][dep[v]] = tp;
			dis[v][dep[v]] = d;
			getship(v, tp, x, d+1);
		}
}

void build(int x, int prelen) {
	vis[x] = 1, len = 0;
	getship(x, x, 0, 1);
	val[x].init(all);
	sum[x].init(all);
	
	int nowsiz = all;
	for(int v, i = h[x]; i; i = g[i].next)
		if(!vis[v = g[i].to]) {
			if(siz[v] < siz[x]) all = siz[v];
			else all = nowsiz - siz[x];
			getroot(v, root = 0);
			build(root, len);
		}
}


void modify(int x, int v) {
	val[x].modify(0, v);
	sum[x].modify(dis[x][dep[x]], v);
	for(int i = dep[x]; i; --i) {
		val[fa[x][i]].modify(dis[x][ i ], v);
		sum[fa[x][i]].modify(dis[x][i-1], v);
	}
}

int query(int x, int k) {
	int ret = val[x].query(k);
	for(int i = dep[x]; i; --i)
		if(dis[x][i] <= k) {
			ret += val[fa[x][ i ]].query(k-dis[x][i]);
			ret -= sum[fa[x][i+1]].query(k-dis[x][i]);
		}
	return ret;
}

int last;
int load() {
	return read();
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) w[i] = read();
	for(int i = 2; i <= n; ++i) add(read(), read());
	memset(dis, -1, sizeof(dis));

	all = low[0] = n;
	getroot(1, root = 0);
	build(root, n);
	for(int i = 1; i <= n; ++i) fa[i][dep[i]+1] = i;
	for(int i = 1; i <= n; ++i) modify(i, w[i]);
	
	for(int t, x, y; m--;) {	
		t = read(), x = load(), y = load();
		if(!t) printf("%d\n", last = query(x, y));
		else modify(x, y - w[x]), w[x] = y;
	}
	return 0;
}
