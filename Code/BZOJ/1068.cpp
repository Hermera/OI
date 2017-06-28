#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 55;
const int inf = 1e9;
int dp[maxn][maxn][2];
char s[maxn];

bool same(int l, int r)
{
	int len = r-l+1;
	if(len&1) return false;
	for(int i = l; i <= (l+r)>>1; ++i)
		if(s[i] != s[i+(len>>1)]) return false;
	return true;
}

int dfs(int l, int r, bool t)
{
	if(dp[l][r][t]) return dp[l][r][t];
	int &ans = dp[l][r][t];
	ans = r-l+1;
	if(t) for(int i = l; i < r; ++i) ans = min(ans, dfs(l, i, 1)+dfs(i+1, r, 1)+1);
	for(int i = l; i < r; ++i) ans = min(ans, dfs(l, i, t)+r-i);
	if(same(l, r)) ans = min(ans, dfs(l, (l+r)>>1, 0)+1);
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%s", s);
	printf("%d\n", dfs(0, strlen(s)-1, 1));
	return 0;
}
