#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 1005;
const int maxm = 10005;
const double INF = 1e20;
const double eps = 1e-7;

int n, m;
namespace LinearProgramming {
	double a[maxn][maxm], b[maxn], c[maxm], ans;
	
	void pivot(int x, int y) {
		b[x] /= a[x][y];
		for(int i = 1; i <= n; ++i)
			if(i != y) a[x][i] /= a[x][y];
		a[x][y] = 1.0/a[x][y];
		
		for(int i = 1; i <= m; ++i)
			if(i != x && fabs(a[i][y]) > eps) {
				b[i] -= a[i][y]*b[x];
				for(int j = 1; j <= n; ++j)
					if(j != y) a[i][j] -= a[i][y]*a[x][j];
				a[i][y] = -a[i][y]*a[x][y];
			}
		
		ans += b[x]*c[y];
		for(int i = 1; i <= n; ++i)
			if(i != y) c[i] -= c[y]*a[x][i];
		c[y] = -c[y]*a[x][y];
	}

	double simplex() {
		while(1) {
			int u, v = 1;
			for(; v <= n; ++v) if(c[v] > eps) break;
			if(v > n) return ans;
		
			double tmp = INF;
			for(int i = 1; i <= m; ++i)
				if(a[i][v] > eps && b[i]/a[i][v] < tmp)
					tmp = b[i]/a[i][v], u = i;
			if(tmp == INF) return INF;
			pivot(u, v);
		}
	}
}

int main() {
	using namespace LinearProgramming;
	
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; ++i) scanf("%lf", b+i);
	for(int x, y, i = 1; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		for(int j = x; j <= y; ++j) a[j][i] = 1;
		scanf("%lf", c+i);
	}
	
	int ans = int(simplex()+0.5);
	printf("%d\n", ans);
	return 0;
}
