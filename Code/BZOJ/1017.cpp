#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline void cmin(int &x, int y) { if(y < x) x = y; }
inline void cmax(int &x, int y) { if(y > x) x = y; }

const int maxn = 60;
const int maxm = 2005;
const int INF = 1e9;
int n, m, c, root, ans, cnt;
int h[maxn], deg[maxn], p[maxn], l[maxn], w[maxn];
int q[maxn], dp[maxm], g[maxn][maxm], f[maxn][maxn<<1][maxm];
char ch[5];

struct Edge { int next, to, w; } d[maxn*maxn];
void add(int x, int y, int w) { 
	d[++cnt] = (Edge) { h[x], y, w };
	h[x] = cnt, ++deg[y]; 
}

void dfs(int x) {
	if(!h[x]) {
		cmin(l[x], m/w[x]);
		for(int i = 0; i <= l[x]; ++i)
		for(int j = 0; j <= i; ++j)
			f[x][j][i*w[x]] = (i-j)*p[x];
		return;
	}
	
	l[x] = INF;
	for(int i = h[x]; i; i = d[i].next)
		dfs(d[i].to),
		cmin(l[x], l[d[i].to]/d[i].w),
		w[x] += w[d[i].to]*d[i].w;
	cmin(l[x], m/w[x]);
	
	memset(g, -63, sizeof(g));
	g[0][0] = 0;
	for(int z = l[x], t; ~z; --z) {
		t = 0;
		for(int k = h[x]; k; k = d[k].next) {
			++t;
			for(int i = 0; i <= m; ++i)
			for(int j = 0; j <= i; ++j)
				cmax(g[t][i], g[t-1][i-j] + f[d[k].to][d[k].w*z][j]);
		}
		
		for(int i = 0; i <= z; ++i)
		for(int j = 0; j <= m; ++j)
			cmax(f[x][i][j], g[t][j] + (z-i)*p[x]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, t, x, v; i <= n; ++i) {
		scanf("%d%s", p+i, ch);
		if(*ch == 'A') {
			scanf("%d", &t);
			while(t--) scanf("%d%d", &x, &v), add(i, x, v);
		} else scanf("%d%d", w+i, l+i);
	}
	
	memset(f, -63, sizeof(f));
	for(int i = 1; i <= n; ++i) if(!deg[i]) dfs(i), q[++c] = i;

	memset(g, -63, sizeof(g));
	for(int i = 1; i <= n; ++i) if(!deg[i])
		for(int j = 0; j <= l[i]; ++j)
		for(int k = 0; k <= m; ++k)
			cmax(g[i][k], f[i][j][k]);
		
	memset(dp, -63, sizeof(dp));
	dp[0] = 0;
	for(int i = 1; i <= c; ++i)
	for(int j = m; ~j; --j)
	for(int k = j; ~k; --k)
		cmax(dp[j], dp[j-k] + g[q[i]][k]);
	for(int i = 0; i <= m; ++i) cmax(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}
