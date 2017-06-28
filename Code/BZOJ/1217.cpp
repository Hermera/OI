#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e6+5;
struct Data { int next, to; } data[maxn];
int N, cnt, head[maxn], dp[maxn][3];

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }

void dfs(int x)
{
	int son = -1;
	dp[x][1] = 1;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		dfs(e.to);
		dp[x][1] += min(dp[e.to][2], dp[e.to][1]);
		dp[x][2] += min(dp[e.to][0], dp[e.to][1]);
		if(son < 0 || dp[son][1] > dp[e.to][1]) son = e.to;
	}
	dp[x][0] = dp[x][2]-min(dp[son][0], dp[son][1])+dp[son][1];
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 2; i <= N; ++i)
	{
		int f = read();
		add(f, i);
	}
	dfs(1);
	printf("%d\n", min(dp[1][1], dp[1][0]));
	return 0;
}
