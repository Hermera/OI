#include <cstdio>
#include <algorithm>
#include <cstring>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
const int maxn = 2505;
const int maxt = 2505;
int N, M, T, ans, sum[maxn];
int dp[maxn][maxn], f[maxn], b[maxt][maxn];
char map[maxn][maxn];

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);
	scanf("%d%d%d", &N, &M, &T);
	for(int i = 1; i <= N; ++i) scanf("%s", map[i]+1);
	for(int i = 1; i <= N; ++i)
	{
		mem(dp, 0); mem(f, 0); mem(sum, 0);
		for(int j = 1; j <= M; ++j) sum[j] = sum[j-1]+(map[i][j] == '0');
		for(int j = 1; j <= M; ++j)
		for(int t = 1; t <= j; ++t)
		{
			dp[j][t] = dp[j][t-1];
			for(int k = t-1; k <= j; ++k)
			dp[j][t] = max(dp[j][t], dp[k][t-1]+max(sum[j]-sum[k], j-k-(sum[j]-sum[k])));
			f[t] = max(f[t], dp[j][t]);
		}
		for(int j = 1; j <= T; ++j)
		for(int t = 1; t <= min(j, M); ++t)
			b[i][j] = max(b[i][j], b[i-1][j-t]+f[t]), ans = max(ans, b[i][j]);
	}
	printf("%d\n", ans);
	return 0;
}
