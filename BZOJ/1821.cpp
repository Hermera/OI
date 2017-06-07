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
const int maxn = 1e3+5;
int N, K, cnt, fa[maxn];
struct P { int x, y; } p[maxn];
struct Edge { int x, y; double dis; } e[maxn*maxn];

bool cmp(Edge x, Edge y) { return x.dis < y.dis; }
int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
bool Union(int x, int y) 
{ 
	x = Find(x), y = Find(y); 
	if(x == y) return false;
	fa[x] = y; return true; 
}

bool Judge(double x)
{
	int scc = N;
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = 1; i <= cnt; ++i)
		if(e[i].dis < x*x) scc -= Union(e[i].x, e[i].y);
		else break;
	return scc >= K;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), K = read();
	for(int i = 1; i <= N; ++i)
		p[i].x = read(), p[i].y = read();
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j < i; ++j)
		e[++cnt] = (Edge){i, j, (double)(p[i].x-p[j].x)*(p[i].x-p[j].x)+(double)(p[i].y-p[j].y)*(p[i].y-p[j].y)};
	sort(e+1, e+cnt+1, cmp);
	double left = 0, right = 1e9;
	while(right-left > 1e-5)
	{
		double mid = (right+left)/2.0;
		if(Judge(mid)) left = mid;
		else right = mid;
	}
	printf("%.2lf\n", left);
	return 0;
}
