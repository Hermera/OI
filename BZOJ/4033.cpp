#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
typedef long long ll;
const int maxn = 4005;
struct Data { int next, to; ll w; } data[maxn<<1];
int N, K, cnt, size[maxn], head[maxn];
ll dp[maxn][maxn];

void add(int x, int y, int w)
{ data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; data[cnt].w = w; }

void dfs(int x, int fa)
{
	size[x] = 1;
	dp[x][0] = dp[x][1] = 0;
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa)
	{
		Data &e = data[i];
		dfs(e.to, x);
		size[x] += size[e.to];
		for(int j = size[x]; j >= 0; --j)
		for(int l = 0; l <= min(size[e.to], j); ++l)
		dp[x][j] = max(dp[x][j], dp[x][j-l]+dp[e.to][l]+((l*(K-l))+(size[e.to]-l)*(N-K-(size[e.to]-l)))*e.w);
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), K = read();
	memset(dp, 128, sizeof(dp));
	for(int i = 1, u, v, w; i < N; ++i)
		u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	dfs(1, 0);
	printf("%lld\n", dp[1][K]);
	return 0;
}
