#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1000005;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
int N, M, S, sum, c[maxn], belong[maxn], ans[maxn];
int check[maxn];
struct Query { int l, r, id; } query[maxn];

bool cmp(Query x, Query y) { return belong[x.l] != belong[y.l] ? belong[x.l] < belong[y.l] : x.r < y.r; }

inline void update(int pos, int val)
{
	if(check[c[pos]]+val > 0 && !check[c[pos]]) ++sum;
	if(check[c[pos]]+val == 0 && check[c[pos]]) --sum;
	check[c[pos]] += val;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), S = sqrt(N);
	for(int i = 1; i <= N; ++i) c[i] = read(), belong[i] = (i-1)/S+1;
	M = read();
	for(int i = 1; i <= M; ++i) query[i].l = read(), query[i].r = read(), query[i].id = i;
	sort(query+1, query+1+M, cmp);
	for(int i = 1, l = 1, r = 0; i <= M; ++i)
	{
		for(; r < query[i].r; ++r) update(r+1, 1);
		for(; r > query[i].r; --r) update(r, -1);
		for(; l < query[i].l; ++l) update(l, -1);
		for(; l > query[i].l; --l) update(l-1, 1);
		ans[query[i].id] = sum;
	}
	for(int i = 1; i <= M; ++i) printf("%d\n", ans[i]);
	return 0;
}
