#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 105;
double x[maxn], y[maxn], ans[maxn], f[maxn][maxn];
int n;

void gauss() {
	for(int i = 1; i <= n; ++i) {
		int t = i;
		for(int j = i+1; j <= n; ++j)
			if(fabs(f[j][i]) > fabs(f[t][i])) t = j;
		for(int j = 1; j <= n+1; ++j) swap(f[i][j], f[t][j]);
		for(int j = i+1; j <= n; ++j) {
			double p = f[j][i]/f[i][i];
			for(int k = i; k <= n+1; ++k) f[j][k] -= p*f[i][k];
		}
	}
	
	for(int i = n; i; --i) {
		for(int j = i+1; j <= n; ++j)
			f[i][n+1] -= f[i][j]*ans[j];
		ans[i] = f[i][n+1]/f[i][i];
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%lf", x+i);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) scanf("%lf", y+j);
		for(int j = 1; j <= n; ++j)
			f[i][j] = -2.0*(x[j]-y[j]),
			f[i][n+1] += y[j]*y[j]-x[j]*x[j];
	}
	
	gauss();
	for(int i = 1; i <= n; ++i) 
		printf("%.3lf%c", ans[i], i == n ? '\n' : ' ');
	
	return 0;
}
