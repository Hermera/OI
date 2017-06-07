#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
const int maxn = 305*305;
struct Edge
{ 
	int u, v, w; 
	bool operator <(const Edge &b) const
	{ return w < b.w; }
} e[maxn];
int N, cnt, fa[maxn];
ll ans;

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
bool Union(int x, int y)
{
	x = Find(x), y = Find(y);
	if(x == y) return false;
	fa[x] = y; return true;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read();
	for(int i = 1; i <= N; ++i) e[++cnt] = (Edge){ N+1, i, read() };
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= N; ++j) e[++cnt] = (Edge){ i, j, read() };
	
	sort(e+1, e+1+cnt);
	for(int i = 1; i <= N+1; ++i) fa[i] = i;
	
	for(int i = 1; i <= cnt; ++i)
	if(Union(e[i].u, e[i].v)) ans += e[i].w;
	
	printf("%lld\n", ans);
	return 0;
}
