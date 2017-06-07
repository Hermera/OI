#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 6e4+5;
const int maxs = 305;

struct Block
{
	int a[maxs], size;
	void insert(int x)
	{
		int i = ++size;
		for(; i > 1 && a[i-1] > x; --i) a[i] = a[i-1];
		a[i] = x;
	}
	void modify(int x, int y)
	{
		int tmp = lower_bound(a+1, a+size+1, x)-a;
		for(; tmp < size && a[tmp+1] < y; ++tmp) a[tmp] = a[tmp+1];
		for(; tmp > 1 && a[tmp-1] > y; --tmp) a[tmp] = a[tmp-1];
		a[tmp] = y;
	}
	int query(int x) { return size-(upper_bound(a+1, a+size+1, x)-a)+1; }
	
} blocks[maxn>>2];
struct Data { int next, to; } data[maxn<<1], _data[maxn<<1];
int N, M, tot, _tot, cnt, ans, head[maxn], _head[maxn], a[maxn], be[maxn], fa[maxn], Blocks;

void AddEdge(int x, int y) { data[++tot] = (Data){ head[x], y }; head[x] = tot; }
void AddBlock(int x, int y) { _data[++_tot] = (Data){ _head[x], y }; _head[x] = _tot; }

void TreeDfs(int x)
{
	if(blocks[be[fa[x]]].size == Blocks) blocks[be[x] = ++cnt].insert(a[x]), AddBlock(be[fa[x]], cnt);
	else blocks[be[x] = be[fa[x]]].insert(a[x]);
	
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa[x])
		fa[data[i].to] = x, TreeDfs(data[i].to);
}

void BlockDfs(int x, int y)
{
	ans += blocks[x].query(y);
	for(int i = _head[x]; i; i = _data[i].next)
		BlockDfs(_data[i].to, y);
}

void Solve(int x, int y)
{
	if(a[x] > y) ++ans;
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa[x])
		if(be[data[i].to] == be[x]) Solve(data[i].to, y);
		else BlockDfs(be[data[i].to], y);
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), AddEdge(u, v), AddEdge(v, u);
	for(int i = 1; i <= N; ++i) a[i] = read();
	Blocks = sqrt(N);
	M = read(); 
	TreeDfs(1);
	for(int i = 1; i <= M; ++i)
	{
		int op = read(), x = read()^ans, y = read()^ans;
		if(op == 0) ans = 0, Solve(x, y), printf("%d\n", ans);
		if(op == 1) blocks[be[x]].modify(a[x], y), a[x] = y;
		if(op == 2)
		{
			a[++N] = y, AddEdge(x, N), fa[N] = x;
			if(blocks[be[x]].size == Blocks)
				blocks[be[N] = ++cnt].insert(y), AddBlock(be[x], cnt);
			else blocks[be[N] = be[x]].insert(y);
		}
	}
	return 0;
}
