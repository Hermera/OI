#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
const int maxn = 5e5+5;
int N, M, cnt;
struct Year{ int t, d; } year[maxn<<1];
struct Tree{ int d; bool app; } tree[maxn<<3];
bool cmp(Year a, Year b) { return a.t < b.t; }

void Build(int node, int left, int right)
{
	if(left == right) 
	{ 
		if(year[left].d < 0) tree[node].app = false; 
		else tree[node] = (Tree){year[left].d, true};
		return;
	}
	int mid = (left+right)>>1;
	Build(node<<1, left, mid);
	Build(node<<1|1, mid+1, right);
	tree[node] =  (Tree){max(tree[node<<1].d, tree[node<<1|1].d), min(tree[node<<1].app, tree[node<<1|1].app)};
}

Tree Query(int node, int left, int right, int L, int R)
{
	if(L <= left && right <= R) return tree[node];
	if(right < L || R < left) return (Tree){0, 1};
	int mid = (left+right)>>1;
	Tree ls = Query(node<<1, left, mid, L, R), rs = Query(node<<1|1, mid+1, right, L, R);
	return (Tree){max(ls.d, rs.d), min(ls.app, rs.app)};
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1; i <= N; ++i) 
		year[i].t = read(), year[i].d = read();
	sort(year+1, year+N+1, cmp);
	cnt = N;
	for(int i = 2; i <= N; ++i)
		if(year[i].t - year[i-1].t > 1) year[++cnt].t = year[i].t-1, year[cnt].d = -1;
	sort(year+1, year+cnt+1, cmp);
	Build(1, 1, cnt);
	M = read();
	for(int i = 1; i <= M; ++i)
	{
		int l = read(), r = read();
		l = lower_bound(year+1, year+cnt, (Year){l, 0}, cmp)-year;
		r = lower_bound(year+1, year+cnt, (Year){r, 0}, cmp)-year;
		if(r-l > 1)
		{
			Tree ans = Query(1, 1, cnt, l+1, r-1);
			if(ans.d >= year[r].d || (year[l].d < year[r].d && year[l].d >= 0)) printf("false\n");
			else printf("%s\n", (!ans.app || year[l].d < 0 || year[r].d < 0) ? "maybe" : "true");
		}
		else if(year[l].d < year[r].d && year[l].d >= 0) printf("false\n");
		else printf("%s\n", (year[l].d < 0 || year[r].d < 0) ? "maybe" : "true");
	}
	return 0;
}
