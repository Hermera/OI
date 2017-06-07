#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e5+5;
const int maxk = 15;
int dp[maxn][maxk], T, N, K, P;

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d", &N, &K, &P);
		dp[0][0] = 1;
		for(int i = 1; i <= N*K; ++i)
		for(int j = 1; j <= i && j <= K; ++j)
		{
			dp[i][j] = dp[i-j][j]+dp[i-j][j-1];
			if(i >= N+1) dp[i][j] -= dp[i-N-1][j-1];
			dp[i][j] %= P;
		}
		int ans = 0;
		for(int i = 0; i <= N*K; ++i)
		for(int j = 0; j <= K; ++j)
		{
			ans += dp[i][j]*dp[i][K-j];
			if(j < K) ans += dp[i][j]*dp[i][K-j-1];
			ans %= P;
		}
		printf("%d\n", (ans+P)%P);
	}
	return 0;
}

