#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 105;
int len, dp[maxn][maxn];
char s[maxn];

bool judge(int x1, int x2, int y1, int y2)
{
	int cir = x2-x1+1;
	if((y2-y1+1)%cir != 0) return false;
	for(int i = y1; i <= y2; ++i)
	if(s[i] != s[i-cir]) return false;
	return true;
}
int calc(int x)
{
	int ans = 0;
	while(x) x /= 10, ++ans;
	return ans;
}
int dfs(int l, int r)
{
	if(l == r) return 1;
	if(dp[l][r]) return dp[l][r];
	int &ans = dp[l][r]; ans = r-l+1;
	for(int i = l; i < r; ++i)
	{
		ans = min(ans, dfs(l, i)+dfs(i+1, r));
		if(judge(l, i, i+1, r))
			ans = min(ans, dfs(l, i)+calc((r-i)/(i-l+1)+1)+2);
	}
	return ans;
}

int main()
{
	//freopen("data.in", "r", stdin);
	scanf("%s", s);
	printf("%d\n", dfs(0, strlen(s)-1));
	return 0;
}
