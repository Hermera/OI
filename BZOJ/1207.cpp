#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e4+5;
struct mouce { int x, y, t; } m[maxn];
int N, M, ans, dp[maxn];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= M; ++i)
		m[i].t = read(), m[i].x = read(), m[i].y = read();
	for(int i = 1; i <= M; ++i)
	{
		dp[i] = 1;
		for(int j = 1; j < i; ++j)
		if(abs(m[i].x-m[j].x)+abs(m[i].y-m[j].y) <= m[i].t-m[j].t)
			dp[i] = max(dp[i], dp[j]+1);
	}
	for(int i = 1; i <= M; ++i) ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;	
}
