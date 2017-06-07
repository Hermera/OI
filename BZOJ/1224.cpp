#include <cstdio>
#include <cmath>
using namespace std;
const double EPS = 1e-10;
int N, M, X, Y, tot;
double ans, sum[55];

int sgn(double x)
{
	if(fabs(x) < EPS) return 0;
	return x > 0 ? 1 : -1;
}

void dfs(double now, int use, int pos)
{
	int next = N-use;
	if(use == N)
	{
		if(!sgn(now-ans)) ++tot;
		return;
	}
	if(next > M-pos+1) return;
	if(sgn(now+sum[M]-sum[M-next]-ans) == 1) return;
	if(sgn(now+sum[pos+next]-sum[pos]-ans) == -1) return;
	dfs(now+1.0/(double)(pos+1), use+1, pos+1); dfs(now, use, pos+1);
}

int main()
{
	scanf("%d%d%d%d", &N, &M, &X, &Y);
	ans = (double)X*1.0/Y;
	for(int i = 1; i <= M; ++i) sum[i] = sum[i-1]+(1.0/(double)i);
	dfs(0, 0, 0);
	printf("%d\n", tot);
	return 0;
}
