#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
int fa[maxn], color[maxn], N, M, P, Q;

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);
	scanf("%d%d%d%d", &N, &M, &P, &Q);
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = M; i; --i)
	{
		int L = ((ll)i*P+Q)%N+1, R = ((ll)i*Q+P)%N+1;
		if(L > R) swap(L, R);
		for(int j = Find(L); j <= R; j = Find(j+1))
			color[j] = i, fa[j] = j+1;
	}
	
	for(int i = 1; i <= N; ++i) printf("%d\n", color[i]);
	return 0;
}
