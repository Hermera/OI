#include <cstdio>
#include <algorithm>
#include <cstring>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;

const int maxn = 10005;
const int maxm = 50005;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
struct Data { int next, to; } data[maxm], rdata[maxm];
int N, M, cnt, rcnt, top;
int head[maxn], rhead[maxn], belong[maxn], q[maxn];
bool used[maxn];
void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
void radd(int x, int y) { rdata[++rcnt].next = rhead[x]; rhead[x] = rcnt; rdata[rcnt].to = y; }

void dfs(int x)
{
	used[x] = true;
	for(int i = head[x]; i; i = data[i].next)
		if(!used[data[i].to]) dfs(data[i].to);
	q[++top] = x;
}

void rdfs(int x, int k)
{
	used[x] = true; belong[x] = k;
	for(int i = rhead[x]; i; i = rdata[i].next)
		if(!used[rdata[i].to]) rdfs(rdata[i].to, k);
}

int scc()
{
	mem(used);
	for(int i = 1; i <= N; ++i) if(!used[i]) dfs(i);
	mem(used);
	int tot = 0;
	for(int i = N; i > 0; --i) if(!used[q[i]]) rdfs(q[i], ++tot);
	return tot;
}

int solve()
{
	int tot = scc(), u, ans = 0;
	for(int i = 1; i <= N; ++i)
		if(belong[i] == tot) u = i, ++ans;
	mem(used); rdfs(u, 0);
	for(int i = 1; i <= N; ++i)
		if(!used[i]) return 0;
	return ans;
}

int main()
{
//	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), add(u, v), radd(v, u);
	printf("%d\n", solve());
	return 0;
}
