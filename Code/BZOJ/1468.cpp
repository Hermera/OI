#include <cstdio>
#include <cstring>
#include <algorithm>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;

const int maxn = 1e5+10;
int N, K;

inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

struct Data { int next, to, wi; } data[maxn<<1];
int head[maxn], cnt, ans;
void add(int x, int y, int w) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; data[cnt].wi = w; }

int Max[maxn], size[maxn], deep[maxn], queue[maxn], tot, Root, Rize;
bool check[maxn];
void GetRoot(int x, int fa)
{
	size[x] = 1; Max[x] = 0;
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa && !check[data[i].to])
	{
		Data &e = data[i];
		GetRoot(e.to, x);
		Max[x] = max(Max[x], size[e.to]), size[x] += size[e.to];
	}
	Max[x] = max(Max[x], Rize-size[x]);
	if(Max[x] < Max[Root]) Root = x;
}

void GetDeep(int x, int fa)
{
	queue[++tot] = deep[x];
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa && !check[data[i].to])
	{
		Data &e = data[i];
		deep[e.to] = deep[x]+e.wi;
		GetDeep(e.to, x);
	}
}

int Calc(int x, int fir)
{
	int sum = 0;
	deep[x] = fir, tot = 0;
	GetDeep(x, 0);
	sort(queue+1, queue+tot+1);
	for(int left = 1, right = tot; left < right; )
	if(queue[right]+queue[left] <= K) sum += right-left, left++;
	else right--;
	return sum;
}

void Work(int x)
{
	check[x] = true;
	ans += Calc(x, 0);
	for(int i = head[x]; i; i = data[i].next)
	if(!check[data[i].to])
	{
		Data &e = data[i];
		ans -= Calc(e.to, e.wi); 
		Rize = size[e.to]; GetRoot(e.to, Root = 0);
		Work(Root);
	}
}

int main()
{
	N = read();
	for(int i = 1, u, v, w; i < N; i++)
		u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	K = read();
	size[0] = Max[0] = Rize = N;
	GetRoot(1, 0);
	Work(Root);
	printf("%d\n", ans);
	return 0;
}
