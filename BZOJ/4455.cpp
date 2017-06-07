#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 50;
int n, m, t, cnt, p[maxn], head[maxn], ok[maxn][maxn];
ll f[maxn][maxn], ans;
struct Data { int next, to; } data[maxn];
void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

void dfs(int x, int fa) {
	for(int i = head[x]; i; i = data[i].next)
		if(data[i].to != fa) dfs(data[i].to, x);
	for(int i = 1; i <= t; ++i) {
		f[x][i] = 1;
		for(int j = head[x], v; j; j = data[j].next)
			if((v = data[j].to) != fa) {
				ll sum = 0;
				for(int k = 1; k <= t; ++k)
					if(ok[p[i]][p[k]]) sum += f[v][k];
				f[x][i] *= sum;
			}
	} 
}		

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; ++i) 
		scanf("%d%d", &x, &y), ok[x][y] = ok[y][x] = 1;
	for(int i = 1, x, y; i < n; ++i)
		scanf("%d%d", &x, &y), add(x, y), add(y, x);
	
	for(int i = 1; i < (1<<n); ++i) {
		t = 0;
		for(int j = 1; j <= n; ++j) 
			if(i&(1<<j-1)) p[++t] = j;
		
		dfs(1, 0);
		for(int j = 1; j <= t; ++j)
			if((n-t)&1) ans -= f[1][j];
			else        ans += f[1][j];
	}
	printf("%lld\n", ans);
	return 0;
}
			
