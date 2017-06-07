#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
const int maxn = 2e6+5;
const int maxm = 2e6+5;
const int inf = 1e9;
struct Data {int u, v, dis; } e[maxm];
struct Edge {int to, cap, rev; };
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
int N, M, U, V, D, cnt, level[maxn], iter[maxn];
vector <Edge> G[maxn];
bool cmp(Data x, Data y) { return x.dis < y.dis; }
void add(int x, int y, int c)
{
	G[x].push_back((Edge){y, c, G[y].size()});
	G[y].push_back((Edge){x, c, G[x].size()-1});
}

bool bfs(int s, int t)
{
	mem(level, -1); mem(iter, 0);
	queue <int> q;
	level[s] = 0; q.push(s);
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i)
		{
			Edge &e = G[v][i];
			if(level[e.to] < 0 && e.cap > 0) level[e.to] = level[v]+1, q.push(e.to);
		}
	}
	return level[t] >= 0;
}

int dfs(int v, int t, int f)
{
	if(v == t) return f;
	for(int &i = iter[v]; i < G[v].size(); ++i)
	{
		Edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v])
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0) { e.cap -= d; G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}

int MaxFlow(int s, int t)
{
	int flow = 0;
	while(bfs(s, t)) 
		for(int f; (f = dfs(s, t, inf)); ) flow += f;
	return flow;
}

int main()
{
	//freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= M; ++i) e[i].u = read(), e[i].v = read(), e[i].dis = read();
	U = read(), V = read(), D = read();
	sort(e+1, e+M, cmp);
	for(int i = 1; i <= M; ++i) if(e[i].dis < D) add(e[i].u, e[i].v, 1);
	cnt += MaxFlow(U, V);
	for(int i = 1; i <= N; ++i) G[i].clear();
	for(int i = 1; i <= M; ++i) if(e[i].dis > D) add(e[i].u, e[i].v, 1);
	cnt += MaxFlow(U, V);
	printf("%d\n", cnt);
	return 0;
}
