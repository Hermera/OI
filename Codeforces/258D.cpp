#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1005;
int N, M, a[maxn];
double f[maxn][maxn], p[maxn], q[maxn];

int main() {
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= N; ++j)
		f[i][j] = (a[i] > a[j]);
	
	for(int i = 1, x, y; i <= M; ++i) {
		x = read(), y = read();
		f[x][y] = f[y][x] = 0.5;
		for(int j = 1; j <= N; ++j) if(j != x && j != y) {
			f[x][j] = f[y][j] = 0.5*(f[x][j]+f[y][j]);
			f[j][x] = f[j][y] = 0.5*(f[j][x]+f[j][y]);
		}
	}
	
	double ans = 0;
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j < i; ++j)
		ans += f[j][i];
	
	printf("%.8lf\n", ans);
	return 0;
}
