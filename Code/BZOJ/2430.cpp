#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 25000;
struct CUT{ int dir, wi;};
CUT cut[maxn];

bool cmp(CUT x, CUT y){		return x.wi > y.wi;		}
	
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	n--; m--;
	for(int i = 1; i <= n; i++)
	scanf("%d", &cut[i].wi), cut[i].dir = 0;
	for(int i = n + 1; i <= m + n; i++)
	scanf("%d", &cut[i].wi), cut[i].dir = 1;
	int add[2] = {1, 1};
	sort(cut + 1, cut + m + n + 1, cmp);
	long long ans = 0;
	for(int i = 1; i <= m + n; i++)
	{
		ans += cut[i].wi * add[cut[i].dir];
		add[!cut[i].dir]++;
	}
	printf("%lld", ans);
	return 0;
}
