#include <cstdio>
using namespace std;
int main()
{
	int N;
	long long ans = 0;
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) ans += N/i;
	printf("%lld\n", ans);
	return 0;
}
