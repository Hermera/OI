#include <cstdio>
#include <algorithm>
#define L(x) b[x].L
#define W(x) b[x].W
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 50005;
struct Matrix
{
	int L, W;
	bool operator <(const Matrix &b) const
	{ return L != b.L ? L < b.L : W < b.W; } 
} a[maxn], b[maxn];

int N, cnt, dp[maxn], q[maxn];

bool best1(int i, int j, int k)
{ return L(i)*(W(j+1)-W(k+1)) < dp[k]-dp[j]; }

bool best2(int i, int j, int k)
{ return (dp[i]-dp[k])*(W(j+1)-W(i+1)) >= (dp[i]-dp[j])*(W(k+1)-W(i+1)); }


int main()
{
	freopen("data.in", "r", stdin);

	N = read();
	for(int i = 1; i <= N; ++i) a[i].L = read(), a[i].W = read();
	sort(a+1, a+1+N);
	for(int i = 1; i <= N; ++i)
	if(a[i].L <= a[i+1].L || i == N) b[++cnt] = a[i];
	
	N = cnt;
	int h = 0, t = 0;
	for(int i = 1; i <= N; ++i)
	{
		while(h < t && best1(i, q[h+1], q[h])) ++h;
		dp[i] = dp[q[h]] + L(i)*W(q[h]+1);
		while(h < t && best2(i, q[t], q[t-1])) --t;
		q[++t] = i;
	}
	
	printf("%d\n", dp[N]);
	return 0;
}
