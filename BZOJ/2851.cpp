#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e6+5, maxl = 18;
int N, Q, cnt, tim;
int deep[maxn], no[maxn], head[maxn], dfn[maxn], fa[maxn][maxl];
struct Data { int next, to; } data[maxn];

int LCA(int x, int y) {
	if(deep[x] < deep[y]) swap(x, y);
	
	int d = deep[x]-deep[y];
	for(int i = 0; i < maxl; ++i)
		if(d&(1<<i)) x = fa[x][i];
	if(x == y) return x;
	for(int i = maxl-1; ~i; --i)
		if(fa[x][i] != fa[y][i]) 
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

void dfs(int x) {
	dfn[x] = ++tim;
	for(int i = head[x]; i; i = data[i].next) dfs(data[i].to);
}

bool cmp(int x, int y) { return dfn[x] < dfn[y]; }

int main() {
	freopen("2851.in", "r", stdin);

	N = read();
	for(int i = 1, k, tar; i <= N; ++i) {
		k = read(), tar = 0;
		if(k) tar = read();
		for(int j = 2; j <= k; ++j) tar = LCA(tar, read());
		
		add(tar, i);
		fa[i][0] = tar, deep[i] = deep[tar]+1;
		for(int j = 1; j < maxl; ++j)
			fa[i][j] = fa[fa[i][j-1]][j-1];
	}
	
	dfs(0);
	for(Q = read(); Q; --Q) {
		int ans = 0, k = read();
		for(int i = 1; i <= k; ++i) no[i] = read();
		sort(no+1, no+1+k, cmp);
		
		for(int i = 1; i < k; ++i) ans += deep[no[i]]-deep[LCA(no[i], no[i+1])];
		ans += deep[no[k]];
		printf("%d\n", ans);
	}
	return 0;
}
		
