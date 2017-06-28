#include <cstdio>
#include <algorithm>
using namespace std;
const int Mod = 12345678;
int dp[305][155][25][25], N, M, K;

int main()
{
	scanf("%d%d%d", &N, &M, &K);
	dp[0][0][0][0] = 1;
	for(int i = 0; i <= N+M; ++i)
	for(int j = 0; j <= N; ++j)
	for(int x = 0; x <= K; ++x)
	for(int y = 0; y <= K; ++y)
	if(dp[i][j][x][y])
	{
		if(x+1 <= K && j+1 <= N)
			(dp[i+1][j+1][x+1][max(y-1, 0)] += dp[i][j][x][y]) %= Mod;
		if(y+1 <= K && i-j+1 <= M)
			(dp[i+1][j][max(x-1, 0)][y+1] += dp[i][j][x][y]) %= Mod;
	}
	int ans = 0;
	for(int i = 0; i <= N; ++i)
	for(int x = 0; x <= K; ++x)
	for(int y = 0; y <= K; ++y)
		(ans += dp[N+M][i][x][y]) %= Mod;
	printf("%d\n", ans);
	return 0;
}
