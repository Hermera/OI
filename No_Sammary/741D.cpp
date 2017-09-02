#include <cstdio>
#include <cstring>
#include <assert.h>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 5e5+5;
const int INF = 1e9;

int n, cnt, h[N];
struct Data { int next, to; } g[N];
void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}

int tim, ori[N], fin[N], seq[N];
int siz[N], dep[N], val[N], dis[N], fa[N], son[N];
void dfs(int x) {
	siz[x] = 1;
	ori[x] = ++tim, seq[ori[x]] = x;
	for(int i = h[x]; i; i = g[i].next) {
		int v = g[i].to;
		dep[v] = dep[x]+1;
		dis[v] = dis[x] ^ val[v];
		dfs(v);
		siz[x] += siz[v];
		if(siz[v] > siz[son[x]]) son[x] = v;
	}
	fin[x] = tim;
}


void cmax(int &x, int y) {
	x = x < y ? y : x;
}

int now[(1<<22)+5], ans[N];
int query(int x) {
	int ret = -INF;
	cmax(ret, now[x]);
	for(int i = 0; i < 22; ++i)
		cmax(ret, now[x ^ (1<<i)]);
	return ret;
}


void dfs(int x, int tp) {
	for(int i = h[x]; i; i = g[i].next)
		if(g[i].to != son[x]) dfs(g[i].to, 0);
	if(son[x]) dfs(son[x], 1), cmax(ans[x], ans[son[x]]);
	
	cmax(ans[x], query(dis[x]) - dep[x]);
	cmax(now[dis[x]], dep[x]);
	for(int v, i = h[x]; i; i = g[i].next)
		if((v = g[i].to) != son[x]) {
			cmax(ans[x], ans[v]);
			for(int j = ori[v]; j <= fin[v]; ++j)
				cmax(ans[x], query(dis[seq[j]]) + dep[seq[j]] - 2*dep[x]);
			for(int j = ori[v]; j <= fin[v]; ++j)
				cmax(now[dis[seq[j]]], dep[seq[j]]);
		}
		
	if(!tp) {
		for(int i = ori[x]; i <= fin[x]; ++i)
			now[dis[seq[i]]] = -INF;
	}
}

int get() {
	char ch = getchar();
	if(ch < 'a' || ch > 'z') ch = getchar();
	return ch - 'a';
}

int main() {
	n = read();
	memset(now, -63, sizeof(now));
	for(int i = 2; i <= n; ++i) {
		fa[i] = read();
		val[i] = 1 << get();
		add(fa[i], i);
	}
	
	dfs(1);
	dfs(1, 1);
	for(int i = 1; i <= n; ++i)
		printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
