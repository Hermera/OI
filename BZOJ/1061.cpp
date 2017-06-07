#include <cstdio>
#include <cmath>
using namespace std;

const int maxn = 10005, maxm = 1005;
const double inf = 1e10, eps = 1e-7;
int N, M;

struct Simplex {
	double a[maxn][maxm], b[maxn], c[maxm], ans;
	
	void init() {
		scanf("%d%d", &N, &M);
		for(int i = 1; i <= N; ++i) scanf("%lf", c+i);
		for(int i = 1, x, y; i <= M; ++i) {
			scanf("%d%d", &x, &y);
			for(int j = x; j <= y; ++j) a[i][j] = 1;
			scanf("%lf", b+i);
		}
	}
	
	void pivot(int x, int y) {
		b[x] /= a[x][y];
		for(int i = 1; i <= N; ++i)
			if(i != y) a[x][i] /= a[x][y];
		a[x][y] = 1.0/a[x][y];
		
		for(int i = 1; i <= M; ++i)
			if(i != x && fabs(a[i][y]) > eps) {
				b[i] -= a[i][y]*b[x];
				for(int j = 1; j <= N; ++j)
					if(j != y) a[i][j] -= a[i][y]*a[x][j];
				a[i][y] = -a[i][y]*a[x][y];
			}
		
		ans += b[x]*c[y];
		for(int i = 1; i <= N; ++i)
			if(i != y) c[i] -= c[y]*a[x][i];
		c[y] = -c[y]*a[x][y];
	}
	
	double solve() {
		while(true) {
			int v = 1, l;
			for( ; v <= N; ++v) if(c[v] > eps) break;
			if(v == N+1) return ans;
			
			double tmp = inf;
			for(int i = 1; i <= M; ++i)
				if(a[i][v] > eps && b[i]/a[i][v] < tmp)
					tmp = b[i]/a[i][v], l = i;
			if(tmp == inf) return inf;
			pivot(l, v);
		}
	}
	
} op;

int main() {
	freopen("1061.in", "r", stdin);

	op.init();
	printf("%d\n", int(op.solve()+0.5));
	return 0;
}	
