#include <cstdio>
using namespace std;
const int maxn = 1e5+5;
double x1[maxn], x2[maxn], a[maxn], dp[maxn];
int N;

int main()
{
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i)
	{
		scanf("%lf", a+i);
		x1[i] = (x1[i-1]+1)*a[i];
		x2[i] = (x2[i-1]+2*x1[i-1]+1)*a[i];
		dp[i] = dp[i-1]+(3*x2[i-1]+3*x1[i-1]+1)*a[i];
	}
	printf("%.1lf\n", dp[N]);
	return 0;
}
