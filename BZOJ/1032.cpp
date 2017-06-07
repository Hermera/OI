#include<cstdio>
#include<cstring>
#include<algorithm>
#define col first
#define num second
using namespace std;
const int maxn = 505;
const int inf = 1e9;
int n, i, x, tot, dp[maxn][maxn];
pair<int, int> s[maxn];

int main()
{
	scanf("%d", &i);
	while(i--)
	{
		scanf("%d", &x);
		if(x != s[n].col || !n) s[n].num = tot, s[++n].col = x, tot = 1;
		else ++tot;
	}
	s[n].num = tot;
	for(i = 1; i <= n; ++i) dp[i][i] = 1 + (s[i].num == 1);
	for(i = 1; i <= n; ++i)
	for(int r, l = 1; (r = l + i) <= n; ++l)
	{
		if(s[l].col == s[r].col) dp[l][r] = dp[l+1][r-1] + (s[l].num + s[r].num == 2);
		else dp[l][r] = inf;
		for(int k = l; k < r; ++k)
			dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
	}
	printf("%d\n", dp[1][n]);
	return 0;
}
