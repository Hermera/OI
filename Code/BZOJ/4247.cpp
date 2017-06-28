#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2005;
int n, ans, dp[maxn][maxn];
struct ele { int w, v; } a[maxn];

bool cmp(ele x, ele y) { return x.w > y.w; }
int main() {	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].w, &a[i].v);
	memset(dp, -63, sizeof(dp));
	dp[0][1] = 0;
	
	sort(a+1, a+1+n, cmp);
	for(int i = 1; i <= n; ++i)
	for(int j = 0; j <= n; ++j)
		dp[i][j] = max(dp[i-1][j], dp[i-1][max(j-a[i].w, 0)+1]+a[i].v);
	
	int ans = 0;
	for(int i = 0; i <= n; ++i) ans = max(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}
