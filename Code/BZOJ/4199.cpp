#include <cstdio>
#include <algorithm>
#include <vector>
#define R(x, y) for(int i = x; i <= y; ++i)
#define D(x, y) for(int i = x; i >= y; --i)
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum*t;
}

const int maxn = 3e5+5, M = 130;
const ll inf = 1e18;
int N, c[maxn], X[maxn], Y[maxn], sa[maxn], Rank[maxn], fa[maxn], height[maxn];
ll mx[maxn], mn[maxn], ans[maxn], size[maxn], tot[maxn], sum, ret = -inf;
char s[maxn];
vector <int> G[maxn];

void BuildSa(int N, int M)
{
	int *x = X, *y = Y;
	R(0, M-1) c[i] = 0;
	R(0, N-1) ++c[x[i] = s[i]];
	R(1, M-1) c[i] += c[i-1];
	D(N-1, 0) sa[--c[x[i]]] = i;
	
	for(int k = 1; k <= N; k <<= 1)
	{
		int p = 0;
		R(N-k, N-1) y[p++] = i;
		R(0, N-1) if(sa[i] >= k) y[p++] = sa[i]-k;
		
		R(0, M-1) c[i] = 0;
		R(0, N-1) ++c[x[y[i]]];
		R(0, M-1) c[i] += c[i-1];
		D(N-1, 0) sa[--c[x[y[i]]]] = y[i];
		
		swap(x, y);
		p = 1, x[sa[0]] = 0;
		R(1, N-1) x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
		
		if(p >= N) break;
		M = p;
	}
}

void GetHeight(int N)
{
	int k = 0;
	R(0, N-1) Rank[sa[i]] = i;
	R(0, N-1)
	{
		if(k) --k;
		int j = sa[Rank[i]-1];
		while(s[i+k] == s[j+k]) ++k;
		height[Rank[i]] = k;
	}
}

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void Union(int x, int y)
{
	x = Find(x), y = Find(y);
	ret = max(ret, mn[x]*mn[y]);
	ret = max(ret, mx[x]*mx[y]);
	sum += size[x]*size[y];
	mx[x] = max(mx[x], mx[y]);
	mn[x] = min(mn[x], mn[y]);
	size[x] += size[y];
	fa[y] = x;
}

int main()
{
	N = read();
	scanf("%s", s);
	
	s[N] = '#';
	BuildSa(N+1, M);
	GetHeight(N+1);
	
	R(2, N) G[height[i]].push_back(i);
	R(0, N-1) fa[i] = i, size[i] = 1, mn[i] = mx[i] = read();
	D(N-1, 0)
	{
		for(int j = 0; j < G[i].size(); ++j) Union(sa[G[i][j]], sa[G[i][j]-1]);
		if(sum) ans[i] = ret, tot[i] = sum;
		else ans[i] = tot[i] = 0LL;
	}
	
	R(0, N-1) printf("%lld %lld\n", tot[i], ans[i]);
	return 0;
}
