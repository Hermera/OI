#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn = 505;
int t, n, m, d[maxn];
double p[maxn], f[maxn][maxn];

int main() {
	scanf("%d", &t);
	while(t--) {
		memset(f, 0, sizeof(f));
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) 
			scanf("%lf%d", p+i, d+i);
		
		f[0][m] = 1;		
		double ans = 0;
		for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			f[i][j] = f[i-1][j]*pow(1-p[i-1], j) + f[i-1][j+1]*(1-pow(1-p[i-1], j+1));
			ans += f[i][j]*(1-pow(1-p[i], j))*d[i];
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}
