#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 5e4+5;
const int maxm = 1e5+5;
const int inf = 1e9;
struct Load { int u, v, a, b; } load[maxm];
struct Data { int next, to, a, b; } data[maxm<<1];
int N, M, cnt, ans = inf, head[maxn], dis[maxn];
bool inq[maxn];
queue <int> q;

void add(int x, int y, int a, int b) 
{ data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; data[cnt].a = a; data[cnt].b = b; }
bool cmp(Load x, Load y) { return x.a < y.a; }

void SPFA()
{
	while(!q.empty())
	{
		int v = q.front(); q.pop(); inq[v] = false;
		for(int i = head[v]; i; i = data[i].next)
		{
			Data &e = data[i];
			if(max(dis[v], e.b) < dis[e.to]) 
			{
				dis[e.to] = max(dis[v], e.b);
				if(!inq[e.to]) inq[e.to] = true, q.push(e.to);
			}
		}
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= M; ++i) 
		load[i].u = read(), load[i].v = read(), load[i].a = read(), load[i].b = read();
	sort(load+1, load+M+1, cmp);
	mem(dis, 63);
	dis[1] = 0;
	for(int i = 1; i <= M; ++i)
	{
		Load &e = load[i];
		add(e.u, e.v, e.a, e.b); add(e.v, e.u, e.a, e.b);
		if(!inq[e.u]) inq[e.u] = true, q.push(e.u);
		if(!inq[e.v]) inq[e.v] = true, q.push(e.v);
		SPFA();
		ans = min(ans, e.a+dis[N]);
	}
	printf("%d\n", ans >= inf ? -1 : ans);
	return 0;
}
