#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 55;
const double eps = 1e-10;
double a[maxn][maxn], tmp = 1;
int n;

bool cmp(double x, double y) { return fabs(x-y) < eps; }
double gauss() {
	--n;
	for(int i = 1; i <= n; ++i) {
		int v = i;
		for(int j = i; j <= n; ++j) 
			if(fabs(a[v][i]) < fabs(a[j][i])) v = j;
		for(int j = 1; j <= n; ++j) swap(a[i][j], a[v][j]);
		for(int j = i+1; j <= n; ++j) {
			double t = a[j][i] / a[i][i];
			for(int k = i; k <= n; ++k) a[j][k] -= a[i][k] * t;
		}
	}
	
	double ret = 1;
	for(int i = 1; i <= n; ++i) ret *= a[i][i];
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j) {
		scanf("%lf", &a[i][j]);
		double t = cmp(a[i][j], 1) ? eps : 1 - a[i][j];
		if(i < j) tmp *= t;
		a[i][j] /= t;
	}
	
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
		if(i != j) a[i][i] -= a[i][j];
	printf("%.10f\n", fabs(gauss()) * tmp);
	return 0;
}
