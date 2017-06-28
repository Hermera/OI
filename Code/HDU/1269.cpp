#include <cstdio>
#include <cstring>
#include <algorithm>
#define mem(x) memset(x, 0, sizeof(x));
using namespace std;

const int maxn = 10005;
const int maxm = 100005;

struct Data { int next, to; } data[maxm];
int N, M, cnt, tim, tot, top;
int head[maxn], stack[maxn], low[maxn], dfn[maxn], belong[maxn];
bool ins[maxn];

inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
void init()
{
	mem(head); mem(dfn); cnt = tim = tot = top = 0;
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), add(u, v);
}

void tarjan(int x)
{
	low[x] = dfn[x] = ++tim;
	ins[x] = true; stack[++top] = x;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(!dfn[e.to]) tarjan(e.to), low[x] = min(low[e.to], low[x]);
		else if(ins[e.to]) low[x] = min(low[e.to], low[x]);
	}
	if(low[x] == dfn[x])
	{
		++tot;
		while(top)
		{
			int e = stack[top]; --top;
			belong[e] = tot; ins[e] = false;
			if(e == x) break;
		}
	}
}

int main()
{
	//freopen("data.in", "r", stdin);
	while(scanf("%d%d", &N, &M) == 2 && (N||M))
	{
		init();
		for(int i = 1; i <= N; ++i)
		if(!dfn[i]) tarjan(i);
		//for(int i = 1; i <= N; ++i) printf("%d ", belong[i]);
		printf("%s\n", tot == 1 ? "Yes" : "No");
	}
	return 0;
}
