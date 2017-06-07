#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 55005;
const int inf = 1e9;
int N, M, S, T, level[maxn], iter[maxn];
ll C;

struct Edge { int to, cap, rev; };
vector <Edge> G[maxn];
void add(int x, int y, int c)
{
	G[x].push_back((Edge){y, c, G[y].size()});
	G[y].push_back((Edge){x, 0, G[x].size()-1});
}

void init()
{
	M = read(), N = read(); S = 0, T = N+1;
	while(1)
	{
		int u = read(), v = read();
		if(u < 0 || v < 0) break;
		add(u, v, 1);
	}
	for(int i = 1; i <= M; ++i) add(S, i, 1);
	for(int i = M+1; i <= N; ++i) add(i, T, 1);
}

bool bfs(int s)
{
	queue <int> q;
	mem(level, -1), mem(iter, 0);
	level[s] = 0; q.push(s);
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i)
		{
			Edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0)
				level[e.to] = level[v]+1, q.push(e.to);
		}
	}
	return level[T] != -1;
}

ll dfs(int v, int t, int f)
{	
	if(v == t || f == 0) return f;
	for(int &i = iter[v]; i < G[v].size(); ++i)
	{
		Edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v])
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0) { e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}

ll MaxFlow(int s, int t)
{
	ll flow = 0;
	while(bfs(s))
		for(int f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read(); S = 0, T = N+M+1;
	for(int i = 1, val; i <= N; ++i)
		val = read(), add(S, i, val);
	for(int i = N+1, a, b, c; i <= N+M; ++i)
		a = read(), b = read(), c = read(), add(a, i, inf), add(b, i, inf), add(i, T, c), C += c;
	printf("%lld\n", C-MaxFlow(S, T));
}
