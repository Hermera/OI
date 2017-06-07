#include <cstdio>
using namespace std;
const int MaxS = 1e5+5;
typedef long long ll;
ll F[MaxS];
int C[10], D[10], tot;
int main()
{
	freopen("data.in", "r", stdin);
	for(int i = 0; i < 4; ++i) scanf("%d", C+i);
	scanf("%d", &tot);
	F[0] = 1;
	for(int j = 0; j < 4; ++j)
	for(int i = C[j]; i <= MaxS; ++i)
		F[i] += F[i-C[j]];
	for(int i = 1, sum; i <= tot; ++i)
	{
		ll ans = 0;
		for(int i = 0; i < 4; ++i) scanf("%d", D+i);
		scanf("%d", &sum);
		for(int i = 0; i < (1<<4); ++i)
		{
			int d = 0, s = sum;
			for(int j = 0; j < 4; ++j)
			if(i&(1<<j)) ++d, s -= (D[j]+1)*C[j];
			if(s < 0) continue;
			ans += d&1 ? -F[s] : F[s];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
