#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 505;
int n, m, x[maxn*maxn], y[maxn*maxn], deg[maxn], g[maxn][maxn];
double f[maxn][maxn], val[maxn*maxn], ans[maxn], sum;

void gauss() {
	for(int i = 1; i <= n; ++i) {
		int t = i;
		for(int j = i+1; j <= n; ++j)
			if(fabs(f[j][i]) > fabs(f[t][i])) t = j;
		for(int j = 1; j <= n+1; ++j) swap(f[i][j], f[t][j]);
		for(int j = i+1; j <= n; ++j) if(i != j) {
			double p = f[j][i]/f[i][i];
			for(int k = i; k <= n+1; ++k) f[j][k] -= f[i][k]*p;
		}
	}
	
	for(int i = n; i; --i) {
		for(int j = i+1; j <= n; ++j)
			f[i][n+1] -= f[i][j]*ans[j];
		ans[i] = f[i][n+1] / f[i][i];
	}
}

bool cmp(double x, double y) { return x > y; }
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d", x+i, y+i), 
		++deg[x[i]], ++deg[y[i]], 
		g[x[i]][y[i]] = g[y[i]][x[i]] = 1;
	--n;
	f[1][n+1] = -1;
	for(int i = 1; i <= n; ++i) f[i][i] = -1;
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
		if(g[i][j]) f[i][j] = 1.0/deg[j];
	
	gauss();
	for(int i = 1; i <= m; ++i) 
		val[i] = ans[x[i]]/deg[x[i]] + ans[y[i]]/deg[y[i]];
	sort(val+1, val+1+m, cmp);
	for(int i = 1; i <= m; ++i) sum += val[i]*i;
	printf("%.3lf\n", sum);
	return 0;
}
