#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 5e5+5;
const double EPS = 1e-10;
typedef long long ll;
struct Data { int next, to; } data[maxn<<1];
int N, cnt, ans, a[maxn], head[maxn], deg[maxn];
double s[maxn];

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
void dfs(int x, int fa)
{
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to != fa)
		{
			s[e.to] = s[x]+log(deg[x]);
			dfs(e.to, x);
		}
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u), ++deg[u], ++deg[v];
	for(int i = 2; i <= N; ++i) --deg[i];
	s[1] = 1;
	dfs(1, 0);
	for(int i = 1; i <= N; ++i) s[i] += log(a[i]);
	sort(s+1, s+1+N);
	for(int i = 2, tot = 1; i <= N+1; ++i)
		if(fabs(s[i]-s[i-1]) < EPS) ++tot;
		else ans = max(tot, ans), tot = 1;
	printf("%d\n", N-ans);
	return 0;
}
