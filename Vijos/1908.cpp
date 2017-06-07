#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 150;
int d, n, ans = -1, sum, a[maxn][maxn];

int Get(int x, int y) {
	int ret = 0;
	for(int i = max(0, x-d); i <= min(128, x+d); ++i)
	for(int j = max(0, y-d); j <= min(128, y+d); ++j)
		ret += a[i][j];
	return ret;
}		

int main() {
	scanf("%d%d", &d, &n);
	for(int i = 1, x, y, k; i <= n; ++i)
		scanf("%d%d%d", &x, &y, &k), a[x][y] += k;
	
	for(int i = 0; i < 129; ++i)
	for(int j = 0; j < 129; ++j) {
		int now = Get(i, j);
		if(now > ans) ans = now, sum = 1;
		else if(now == ans) ++sum;
	}
	
	printf("%d %d\n", sum, ans);
	return 0;
}
