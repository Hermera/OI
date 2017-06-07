#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e6+5;
struct Q { int l, r, t; } q[maxn];
int N, C, M, tree[maxn], F[maxn], color[maxn], next[maxn], ans[maxn];

void add(int x, int v) { while(x <= N) tree[x] += v, x += x&-x; }
int query(int x)
{
	int ans = 0;
	while(x) ans += tree[x], x -= x&-x;
	return ans;
}

bool cmp(Q a, Q b) { return a.l < b.l; } 

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), C = read(), M = read();
	for(int i = 1; i <= N; ++i) F[i] = read();
	for(int i = N; i >= 1; --i) next[i] = color[F[i]], color[F[i]] = i;
	for(int i = 1; i <= M; ++i) q[i].l = read(), q[i].r = read(), q[i].t = i;
	sort(q+1, q+1+M, cmp);
	for(int i = 1; i <= C; ++i) 
		if(next[color[i]]) add(next[color[i]], 1);
	for(int i = 1, low = 1; i <= M; ++i)
	{
		Q &e = q[i];
		while(low < e.l) 
		{
			if(next[low]) add(next[low], -1);
			if(next[next[low]]) add(next[next[low]], 1);
			++low;
		}
		ans[e.t] = query(e.r)-query(e.l-1);
	}
	for(int i = 1; i <= M; ++i) printf("%d\n", ans[i]);
	return 0;
}
