#include <cstdio>
using namespace std;
const int maxn = 505;
int t, n, m, d[maxn];
double p[maxn], f[maxn][maxn], g[maxn][maxn];

int main() {
	freopen("4008.in", "r", stdin);

	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%lf%d", p+i, d+i);
		
		for(int i = 1; i <= n; ++i) g[i][0] = 1;
		for(int j = 1; j <= m; ++j) {
			double now = 1;
			for(int i = 1; i <= n; ++i) {
				f[i][j] = now*g[i][j-1]*p[i];
				now *= g[i][j-1]*(1-p[i]);
				g[i][j] = g[i][j-1]-f[i][j];
			}
		}
		
		double ans = 0;
		for(int i = 1; i <= n; ++i) {
			double sum = 0;
			for(int j = 1; j <= m; ++j)
				sum += f[i][j];
			ans += sum*d[i];
		}
		printf("%.10lf\n", ans);
	}
	return 0;
}
