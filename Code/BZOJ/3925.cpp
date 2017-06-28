#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 11, maxm = 50;
int n, m, e[maxn], size[1<<maxn], cnt[1<<maxn];
ll c[maxm][maxm], f[1<<maxn][maxm], g[1<<maxn][maxm];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v; i < m; ++i) {
		scanf("%d%d", &u, &v), --u, --v;
		e[u] |= 1<<v;
		e[v] |= 1<<u;
	}
	
	for(int i = 0; i <= m; ++i) c[i][0] = 1;
	for(int i = 1; i <= m; ++i)
	for(int j = 1; j <= i; ++j)
		c[i][j] = c[i-1][j-1]+c[i-1][j];
		
	for(int s = 1; s < (1<<n); ++s) {
		size[s] = size[s>>1]+(s&1);
		if(size[s] == 1) {
			g[s][0] = 1;
			continue;
		}
		
		for(int i = 0; i < n; ++i)
			if(s&(1<<i)) cnt[s] += size[e[i]&s];
		cnt[s] >>= 1;
		for(int t = (s-1)&s; t; (--t)&= s)
			if(t&(s&-s)) 
				for(int i = 0; i <= cnt[t]; ++i)
				for(int j = 0; j <= cnt[s^t]; ++j)
					f[s][i+j] += g[t][i]*c[cnt[s^t]][j];
		
		for(int i = 0; i <= cnt[s]; ++i)
			g[s][i] = c[cnt[s]][i]-f[s][i];
	}
	
	double ans = 0;
	for(int i = 0; i <= m; ++i)
		ans += 1.0*f[(1<<n)-1][i]/c[cnt[(1<<n)-1]][i];
	ans /= m+1;
	printf("%.6f\n", ans);
	return 0;
}
