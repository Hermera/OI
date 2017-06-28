#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 3e5+5;
int N, M, ans, tot, tim, top, cnt;
int belong[maxn], stack[maxn], dfn[maxn], low[maxn], size[maxn], deg[maxn], head[maxn], brain[maxn];
struct Data { int next, to; } data[maxn<<1];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

void add(int x, int y) { data[++cnt].next = head[x]; data[cnt].to = y; head[x] = cnt; }

void Tarjan(int x)
{
	dfn[x] = low[x] = ++tim;
	stack[++top] = x;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(!dfn[e.to]) Tarjan(e.to), low[x] = min(low[x], low[e.to]);
		else if(!belong[e.to]) low[x] = min(low[x], dfn[e.to]);
	}
	if(low[x] == dfn[x])
	{
		brain[++tot] = x;
		while(top)
		{
			int v = stack[top--];
			belong[v] = tot; ++size[tot];
			if(x == v) break;
		}
	}
}

bool Judge(int x)
{
	x = brain[x];
	for(int i = head[x]; i; i = data[i].next)
	if(deg[belong[data[i].to]] == 1) return false;
	return true;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1, x, y; i <= M; ++i)
		x = read(), y = read(), add(x, y);
	for(int i = 1; i <= N; ++i)
		if(!dfn[i]) Tarjan(i);
	
	for(int i = 1; i <= N; ++i)
	for(int j = head[i]; j; j = data[j].next)
		if(belong[i] != belong[data[j].to])
			++deg[belong[data[j].to]];
	
	for(int i = 1; i <= tot; ++i) if(!deg[i]) ++ans;
	for(int i = 1; i <= tot; ++i)
	if(size[i] == 1 && !deg[i] && Judge(i)) { --ans; break; }
	
	printf("%.6lf\n", (N-ans)*1.0/(double)N);
	return 0;
}
