#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 600005;
int N, M, K, cnt, tot;
struct Data { int next, to; } data[maxn<<1];
int head[maxn], q[maxn], fa[maxn], ans[maxn];
bool check[maxn], used[maxn];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

bool Union(int x, int y)
{ 
	x = Find(x); y = Find(y); 
	if(x == y) return false;
	fa[x] = y; return true;
}

int main()
{
//	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = 1, u, v; i <= M; ++i)
		u = read()+1, v = read()+1, add(u, v), add(v, u);
	K = read();
	tot = N-K;
	for(int i = 1; i <= K; ++i) q[i] = read()+1, check[q[i]] = true;
	for(int i = 1, j = K; i <= N; ++i)
	if(!check[i]) q[++j] = i;
	for(int i = 1; i <= N/2; ++i) swap(q[i], q[N-i+1]);
	for(int i = 1, count = 0; i <= N; ++i)
	{
		used[q[i]] = true;
		if(check[q[i]]) ans[++count] = tot;
		for(int j = head[q[i]]; j; j = data[j].next)
		if(used[data[j].to])
			if(Union(q[i], data[j].to)) --tot;
		if(check[q[i]]) ++tot;
	}
	printf("%d\n", tot);
	for(int i = K; i >= 1; --i) printf("%d\n", ans[i]);
	return 0;
}
