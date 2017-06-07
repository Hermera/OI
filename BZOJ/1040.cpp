#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e6+5;
int N, u, v, cnt, flag=1, w[maxn], fa[maxn], head[maxn], out[maxn], check[maxn];
typedef long long ll;
struct Data { int next, to; } data[maxn<<1];
ll ans, d[maxn][2], p[maxn][2];
bool vis[maxn];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
void treedp(ll dp[maxn][2], int x, int lim)
{
	check[x] = flag;
	if(x != lim) dp[x][1] = w[x];
	for(int i = head[x]; i; i = data[i].next)
	if(check[data[i].to] != flag)
	{
		Data &e = data[i];
		treedp(dp, e.to, lim);
		if(x != lim) dp[x][1] += dp[e.to][0];
		dp[x][0] += max(dp[e.to][0], dp[e.to][1]);
	}
}

void dfs(int x, int f)
{
	vis[x] = true;
	for(int i = head[x], first = 1; i; i = data[i].next)
	{
		Data &e = data[i];
		if(first && e.to == f) { first = 0; continue; }
		if(vis[e.to] == true) u = x, v = e.to;
		else dfs(e.to, x);
	}
}

int main()
{
//	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1; i <= N; ++i) w[i] = read(), fa[i] = read(), add(fa[i], i), add(i, fa[i]), ++out[i];
	for(int i = 1; i <= N; u = v = 0, ++i)
	if(!vis[i])
	{
		dfs(i, 0); ++flag; treedp(d, i, u); ++flag; treedp(p, i, v);
		ans += max(max(d[i][0], d[i][1]), max(p[i][0], p[i][1]));
	}
	printf("%lld\n", ans);
	return 0;
}

