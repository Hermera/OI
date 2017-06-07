#include <cstdio>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e6+5;
int n, cnt, ans, dp[maxn], siz[maxn], head[maxn];
struct Data { int next, to; } G[maxn<<1];
void add(int x, int y) {
	G[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

int dfs(int x, int fa) {
	siz[x] = 1;
	for(int i = head[x], v; i; i = G[i].next)
		if((v = G[i].to) != fa) 
			dfs(v, x), siz[x] += siz[v];
	++dp[siz[x]];
}

int main() {
	n = read();
	for(int i = 2, x, y; i <= n; ++i)
		x = read(), y = read(), add(x, y), add(y, x);
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) {
		for(int j = i+i; j <= n; j += i)
			dp[i] += dp[j];
		if(i*dp[i] == n) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}	
