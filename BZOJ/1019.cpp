#include <cstdio>
using namespace std;
const int maxn = 35;
int N, trans[maxn][4];
long long dp[maxn][4];
char s[5];

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d", &N);
	for(int i = 1; i <= 6; ++i)
	{
		scanf("%s", s);
		int a = s[0]-'A'+1, b = s[1]-'A'+1;
		if(!trans[1][a]) trans[1][a] = b, dp[1][a] = 1;
	}
	for(int i = 2; i <= N; ++i)
	for(int x = 1; x <= 3; ++x)
	{
		int y = trans[i-1][x], z = 6-x-y;
		dp[i][x] = dp[i-1][x]+1+dp[i-1][y];
		if(trans[i-1][y] == z) trans[i][x] = z;
		else dp[i][x] += 1+dp[i-1][x], trans[i][x] = y;
	}
	printf("%lld\n", dp[N][1]);
	return 0;
}
