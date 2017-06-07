#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 20;
const double eps = 1e-10;
int n, m, cas;
int dp[1<<maxn], f[maxn][maxn];
double x[maxn], y[maxn];

int dfs(int s) {
	if(dp[s] <= n) return dp[s];
	int x = 0;	
	while(!(s&(1<<x))) ++x;
	for(int i = x+1; i < n; ++i)
		if(f[x][i] && (s&(1<<i)))
			dp[s] = min(dp[s], dfs(s^(s&f[x][i]))+1);
	dp[s] = min(dp[s], dfs(s^(1<<x))+1);
	return dp[s];
}

int main() {
	freopen("265.in", "r", stdin);

	scanf("%d", &cas);
	while(cas--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i) scanf("%lf%lf", x+i, y+i);
		
		memset(f, 0, sizeof(f));
		for(int i = 0; i < n; ++i)
		for(int j = i+1; j < n; ++j) {
			if(x[i] == x[j]) continue;
			double A = (y[i]*(x[j]/x[i])-y[j])/(x[i]*x[j]-x[j]*x[j]);
			double B = (y[i]-A*x[i]*x[i])/x[i];
			if(A > -eps) continue;

			for(int k = 0; k < n; ++k)
				if(abs(A*x[k]*x[k] + B*x[k] - y[k]) < eps)
					f[i][j] |= (1<<k);
		}
		
		memset(dp, 63, sizeof(dp));
		dp[0] = 0;
		printf("%d\n", dfs((1<<n)-1));
	}
	return 0;
}
