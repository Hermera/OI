#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <queue>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
typedef long long ll;
const int maxn = 40000, inf = 1e9;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
struct Edge { int to, cap, rev; };
vector <Edge> G[maxn];
int N, M, K, S, T, cnt;
int level[maxn], iter[maxn];
ll ans;

void add(int from, int to, int cap)
{
	G[from].push_back((Edge){to, cap, G[to].size()});
	G[to].push_back((Edge){from, 0, G[from].size()-1});
}

bool bfs(int s, int t)
{
	mset(iter, 0), mset(level, -1);
	queue <int> q;
	level[s] = 0; q.push(s);
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); i++)
		{
			Edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0)
				level[e.to] = level[v] + 1, q.push(e.to);
		}
	}
	return level[t] != -1;
}

int dfs(int v, int t, int f)
{
	if(v == t || f == 0) return f;
	for(int &i = iter[v]; i < G[v].size(); i++)
	{
		Edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v])
		{
			int d = dfs(e.to, t, min(e.cap, f));
			if(d > 0)
			{ e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}

ll MaxFlow(int s, int t)
{
	ll flow = 0;
	while(bfs(s, t))
		for(int f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

void init()
{
	N = read(), M = read(), K = read();
	S = 0, cnt = T = N+1;
	for(int i = 1, a; i <= N; ++i) a = read(), ans += a, add(S, i, a);
	for(int i = 1, a; i <= N; ++i) a = read(), ans += a, add(i, T, a);
	for(int i = 1, u, v, k; i <= M; ++i)
		u = read(), v = read(), k = read(), add(u, v, k), add(v, u, k);
	for(int i = 1; i <= K; ++i)
	{
		int t = read(), a = read(), b = read(); ans += b;
		if(!a) add(S, ++cnt, b);
		else add(++cnt, T, b);
		for(int j = 1; j <= t; ++j) 
			if(!a) add(cnt, read(), inf);
			else add(read(), cnt, inf);
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	init();
	printf("%lld\n", ans - MaxFlow(S, T));
	return 0;
}
