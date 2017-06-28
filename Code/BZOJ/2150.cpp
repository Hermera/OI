#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <queue>
#define clear(x, a) memset(x, a, sizeof(x))
using namespace std;

const int maxn = 5005;
const int inf = 100000000;
int N, M, R, C, S, T, sum;
struct Edge { int to, cap, rev; };
vector <Edge> G[maxn];
int level[maxn], iter[maxn];
char s[maxn][maxn];

inline int read()
{
	int sum = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

void add(int from, int to, int cap)
{
	G[from].push_back((Edge){to, cap, G[to].size()});
	G[to].push_back((Edge){from, 0, G[from].size()-1});
}

bool bfs(int s, int t)
{
	clear(iter, 0), clear(level, -1);
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

long long MaxFlow(int s, int t)
{
	long long flow = 0;
	while(bfs(s, t))
		for(int f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read(), R = read(), C = read(); S = 0, T = 2*N*M+1;
	int fx[4] = {R, R, C, C};
	int fy[4] = {C, -C, R, -R};
	for(int i = 1; i <= N; ++i)
		scanf("%s", s[i]+1);
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
	if(s[i][j] == '.')
		add(S, (i-1)*M+j, 1), add((i-1)*M+j+N*M, T, 1), ++sum;
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
	if(s[i][j] == '.')
	{
		for(int d = 0; d < 4; ++d)
		{
			int nx = i+fx[d], ny = j+fy[d];
			if(nx <= N && ny <= M && nx > 0 && ny > 0) 
				if(s[nx][ny] == '.') add((i-1)*M+j, (nx-1)*M+ny+N*M, 1);
		}
	}
	printf("%lld\n", sum-MaxFlow(S, T));
	return 0;
}
