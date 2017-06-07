#include <cstdio>
using namespace std;
const int maxn = 505, Mod = 1024523;
int N, M, dp[maxn][maxn][maxn];
char up[maxn], down[maxn];

int main()
{
	printf("%d\n", (int)sizeof(dp)/1000000);
	freopen("data.in", "r", stdin);
	scanf("%d%d%s%s", &N, &M, up+1, down+1);
	dp[0][0][0] = 1;
	for(int i = 0; i <= N; ++i)
	for(int j = 0; j <= M; ++j)
	for(int k = 0; k <= N; ++k)
	{
		int &ret = dp[i][j][k];
		if(!ret) continue;
		if(up[i+1] == up[k+1]) (dp[i+1][j][k+1] += ret) %= Mod;
		if(down[j+1] == up[k+1]) (dp[i][j+1][k+1] += ret) %= Mod;
		if(up[i+1] == down[i+j-k+1]) (dp[i+1][j][k] += ret) %= Mod;
		if(down[j+1] == down[i+j-k+1]) (dp[i][j+1][k] += ret) %= Mod;
	}
	printf("%d\n", dp[N][M][N]);
	return 0;
}
