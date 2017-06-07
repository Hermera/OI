#include <cstdio>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 2e6+5;
int N, M, K, fa[maxn];
struct Edge { int u, v; } e[maxn];

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
bool Union(int x, int y)
{
	x = Find(x), y = Find(y);
	if(x == y) return true;
	fa[x] = y; return false;
}

int main()
{
	freopen("data.in", "r", stdin);
	
	N = read(), M = read(), K = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), e[i] = (Edge){ u, v };
		
	int ans = 0;
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = 1; i <= M; ++i)
	if(e[i].u > K && e[i].v > K) Union(e[i].u, e[i].v);
	
	for(int i = 1; i <= M; ++i)
	if(e[i].u <= K || e[i].v <= K)
		ans += Union(e[i].u, e[i].v);
	
	printf("%d\n", ans);
	return 0;
}
