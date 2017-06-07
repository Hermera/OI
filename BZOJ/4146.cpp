#include <cstdio>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 2e6+5;
int sum[maxn], N;
ll ans;

int main()
{
	N = read();
	for(int i = 1; i <= N; ++i) ++sum[read()];
	
	for(int i = 1; i < maxn; ++i)
	if(sum[i])
	for(int j = i; j < maxn; j += i)
		if(j == i) ans += (ll)sum[j]*(sum[j]-1);
		else ans += (ll)sum[j]*sum[i];
	
	printf("%lld\n", ans);
	return 0;
}
