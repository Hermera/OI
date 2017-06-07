#include <cstdio>
using namespace std;
const int maxn = 500005;
int N, M, cnt, tim, tree[maxn], head[maxn], fa[maxn], left[maxn], right[maxn];
struct Data { int next, to; } data[maxn];
char s[5];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }

void modify(int x, int v) { while(x <= (N<<1)) tree[x] += v, x += x&-x; }
int query(int x)
{
	int ans = 0;
	while(x) ans += tree[x], x -= x&-x;
	return ans;
}

void dfs(int x)
{
	modify(left[x] = ++tim, 1);
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa[x])
		fa[data[i].to] = x, dfs(data[i].to);
	modify(right[x] = ++tim, -1);
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
	dfs(1);
	M = read();
	for(int i = 1, u, v; i <= M+N-1; ++i)
	{
		scanf("%s", s);
		if(*s == 'W') printf("%d\n", query(left[read()])-1);
		else 
		u = read(), v = read(), modify(fa[u] == v ? left[u] : left[v], -1), modify(fa[u] == v ? right[u] : right[v], 1);
	}
	return 0;
}
