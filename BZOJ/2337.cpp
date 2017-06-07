#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 205;
const double INF = 1e20;
double a[maxn][maxn];

struct Edge { int to, w; };
vector <Edge> g[maxn];
int n, m, deg[maxn];

double gauss() {
	for(int i = 1; i <= n; ++i) {
		int t = i;
		for(int j = i; j <= n; ++j) 
			if(fabs(a[j][i]) > fabs(a[i][i])) t = j;
		for(int j = 1; j <= n+1; ++j) swap(a[i][j], a[t][j]);
			
		if(a[i][i] == 0) continue;
		for(int j = 1; j <= n; ++j) 
			if(i != j && a[j][i] != 0) {
				double t = a[j][i]/a[i][i];
				for(int k = 1; k <= n+1; ++k)
					a[j][k] -= a[i][k]*t;
			}
	}
	return a[1][n+1] / a[1][1];
}

double solve(int x) {
	memset(a, 0, sizeof a);
	for(int i = 1; i <= n; ++i) a[i][i] = 1;
	for(int i = 1; i != n; ++i) 
	for(int j = 0; j < g[i].size(); ++j) {
		Edge &e = g[i][j];
		if(e.w & (1<<x)) {
			a[i][e.to] += 1.0/deg[i];
			a[i][n+1] += 1.0/deg[i];
		} else a[i][e.to] -= 1.0/deg[i];
	}
	
	return gauss();
}


void add(int x, int y, int w) {
	g[x].push_back((Edge){ y, w }), ++deg[x];
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = m, x, y, w; i--; ) {
		scanf("%d%d%d", &x, &y, &w);
		add(x, y, w);
		if(x != y) add(y, x, w);
	}
		
	double ans = 0;
	for(int i = 30; ~i; --i)
		ans += solve(i) * (1<<i);
	printf("%.3lf\n", ans);
	return 0;
}
