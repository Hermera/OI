#include <cmath>
#include <cstdio>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 10005;
const int maxm = 1005;
const double EPS = 1e-7;
const double INF = 1e20;

int n, m;
namespace LinearProgramming {
	double a[maxn][maxm], b[maxn], c[maxm], ans;
	
	void pivot(int u, int v) {
		b[u] /= a[u][v];
		for(int i = 1; i <= m; ++i)
			if(i != v) a[u][i] /= a[u][v];
		a[u][v] = 1.0 / a[u][v];
		for(int i = 1; i <= n; ++i)
			if(i != u && fabs(a[i][v]) > EPS) {
				b[i] -= a[i][v] * b[u];
				for(int j = 1; j <= m; ++j)
					if(j != v) a[i][j] -= a[i][v] * a[u][j];
				a[i][v] = -a[i][v] * a[u][v];
			}
		ans += c[v] * b[u];
		for(int i = 1; i <= m; ++i)
			if(i != v) c[i] -= a[u][i] * c[v];
		c[v] = -c[v] * a[u][v];
	}
	
	double simplex() {
		for(int i, u, v;; pivot(u, v)) {
			for(i = 1, v = -1; i <= m; ++i) if(c[i] > EPS) 
				if(v < 0 || c[i] > c[v]) v = i;
			if(v < 0) return ans;
			
			double tmp = INF;
			for(i = 1; i <= n; ++i) 
				if(a[i][v] > EPS && b[i]/a[i][v] < tmp)
					tmp = b[i]/a[i][v], u = i;
			if(tmp == INF) return INF;
		}
	}
}


int main() {
	using namespace LinearProgramming;

	m = read(), n = read();
	for(int i = 1; i <= m; ++i) c[i] = read();
	for(int i = 1; i <= n; ++i) {
		for(int l, r, k = read(); k--;) {
			l = read(), r = read();
			for(int j = l; j <= r; ++j) a[i][j] = 1;
		}
		b[i] = read();
	}
	
	long long ans = round(simplex());
	printf("%lld\n", ans);
	return 0;
}
