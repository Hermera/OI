#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e7+5, Mod = 100000001;
int N, A, B, C, a[maxn];

int main()
{
	double ans = 0;
	scanf("%d%d%d%d%d", &N, &A, &B, &C, a+1);
	for(int i = 2; i <= N; ++i) a[i] = ((ll)a[i-1]*A+B)%Mod;
	for(int i = 1; i <= N; ++i) a[i] %= C, a[i] += 1;
	a[0] = a[N];
	
	for(int i = 1; i <= N; ++i)
		ans += 1.0/(double)max(a[i-1], a[i]);
	
	printf("%.3lf\n", ans);
	return 0;
}
