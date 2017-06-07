#include <cstdio>
#include <cmath>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
typedef long long ll;
int N, M, like[maxn], fa[maxn];
ll tree[maxn];

void add(int x, int v) { while(x <= N) tree[x] += v, x += x&-x; }
ll query(int x)
{
	ll ans = 0;
	while(x) ans += tree[x], x -= x&-x;
	return ans;
}

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1; i <= N; ++i) 
		like[i] = read(), fa[i] = like[i] <= 1 ? i+1 : i, add(i, like[i]); 
	fa[N+1] = N+1;
	M = read();
	for(int i = 1; i <= M; ++i)
	{
		int op = read(), l = read(), r = read();
		if(op == 1) printf("%lld\n", query(r)-query(l-1));
		else
		for(int j = Find(l); j <= r; j = Find(j+1))
		{
			int temp = (int)sqrt(like[j]);
			add(j, temp-like[j]);
			like[j] = temp;
			if(like[j] <= 1) fa[j] = Find(j+1);
		}
	}
	return 0;
}
