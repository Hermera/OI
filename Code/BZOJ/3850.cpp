#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
struct Work { ll e, k; } work[maxn];

bool cmp(Work a, Work b) { return a.e*b.k < a.k*b.e; }

int main()
{
	freopen("data.in", "r", stdin);
	int N = read();
	for(int i = 1; i <= N; ++i) work[i].e = read();
	for(int i = 1; i <= N; ++i) work[i].k = read();
	
	sort(work+1, work+N+1, cmp);
	
	ll tim = 0, ans = 0;
	for(int i = 1; i <= N; ++i)
		tim += work[i].e, ans += work[i].k*tim;
		
	printf("%lld\n", ans);
}
