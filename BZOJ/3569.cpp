#include <cstdio>
#include <cstdlib>
#include <cstring>
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
int N, M, K, Q, top, last, cnt = 1;
int stack[maxn], a[maxn], b[maxn], head[maxn];
bool vis[maxn];
struct Data { int next, to; } data[maxn<<1];

void add(int x, int y) { data[++cnt] = (Data){ head[x], y }; head[x] = cnt; }

void DFS1(int x, int fa)
{
	vis[x] = true;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to == fa) continue;
		if(!vis[e.to]) DFS1(e.to, x);
		else if(!~a[i>>1]) a[i>>1] = rand(), b[e.to] ^= a[i>>1], b[x] ^= a[i>>1];
	}
}

void DFS2(int x, int fa)
{
	vis[x] = true;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(vis[e.to]) continue;
		DFS2(e.to, x);
		a[i>>1] = b[e.to], b[x] ^= b[e.to];
	}
}

bool Gauss()
{
	int i, j, k = 0;
	for(j = 1<<30; j; j >>= 1)
	{
		for(i = k+1; i <= top; ++i) if(stack[i]&j) break;
		if(i == top+1) continue;
		swap(stack[i], stack[++k]);
		for(i = 1; i <= top; ++i) if(stack[i]&j && i != k) stack[i] ^= stack[k];
	}
	last += (bool)stack[top];
	return stack[top];
}

int main()
{
	freopen("data.in", "r", stdin);
	srand(20000909);
	
	N = read(), M = read();
	for(int i = 1, x, y; i <= M; ++i)
		x = read(), y = read(), add(x, y), add(y, x);
		
	memset(a, -1, sizeof(a));
	DFS1(1, 0);
	memset(vis, 0, sizeof(vis));
	DFS2(1, 0);
	
	Q = read();
	for(int i = 1; i <= Q; ++i)
	{
		K = read(), top = 0;
		for(int j = 1; j <= K; ++j) stack[++top] = a[read()^last];
		printf("%s\n", Gauss() ? "Connected" : "Disconnected");
	}
	
	return 0;
}
