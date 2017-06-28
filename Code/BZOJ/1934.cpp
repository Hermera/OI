#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 305;
const int inf = 1e9;
int N, M, S, T, level[maxn], iter[maxn];
struct Edge { int to, cap, rev; };
vector <Edge> G[maxn];
void AddEdge(int x, int y, int c)
{
	G[x].push_back((Edge){y, c, G[y].size()});
	G[y].push_back((Edge){x, 0, G[x].size()-1});
}

bool bfs(int s, int t)
{
	mem(level, -1), mem(iter, 0);
	queue <int> q;
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
	return level[t] != -1;
}

int dfs(int v, int t, int f)
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

int MaxFlow(int s, int t)
{
	int flow = 0;
	while(bfs(s, t))
		for(int f; (f = dfs(s, t, inf)) > 0; )
			flow += f;
	return flow;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read(), S = 0, T = N+1;
	for(int i = 1; i <= N; ++i)
		if(read() == 1) AddEdge(S, i, 1);
		else AddEdge(i, T, 1);
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), AddEdge(u, v, 1), AddEdge(v, u, 1);
	printf("%d\n", MaxFlow(S, T));
	return 0;
}
