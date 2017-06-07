#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int n, k, m, q, tim, cnt;
int h[maxn], vis[maxn], fir[maxn], sum[maxn];

struct Data { int next, to; } g[maxn * 10];
void add(int x, int y) {
	g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
	g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
}

void dfs(int x) {
	vis[x] = ++tim;
	for(int i = h[x]; i; i = g[i].next)
		if(!vis[g[i].to]) dfs(g[i].to);
}

bool judge(int x, int l, int r) {
	if(fir[x]) return 0;
	for(int i = h[x]; i; i = g[i].next)
		if(l <= g[i].to && g[i].to <= r)
			if(vis[g[i].to] < vis[x]) return 0;
	return 1;
}

int main() {
	n = read(), k = read(), m = read();
	for(int i = 1; i <= m; ++i) add(read(), read());
	for(int i = 1; i <= n; ++i) 
		if(!vis[i]) dfs(i), fir[i] = 1;
	for(int i = 1; i <= n; ++i) sum[i] = sum[i-1] + fir[i];
	
	q = read();
	for(int l, r, ans; q--;) {
		l = read(), r = read();
		ans = sum[r] - sum[l-1];
		for(int i = l; i <= min(r, l+k-1); ++i)   ans += judge(i, l, r);
		for(int i = max(l+k, r-k+1); i <= r; ++i) ans += judge(i, l, r);
		printf("%d\n", ans);
	}
	return 0;
}
