#include <cstdio>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
int N, M, a[maxn];
long long ans;

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	if(N < 3) return printf("0\n"), 0;
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), ++a[u], ++a[v];
	ans = (long long)N*(N-1)*(N-2)/6;
	
	for(int i = 1; i <= N; ++i)
		ans -= a[i]*(N-1-a[i])/2;
	
	printf("%lld\n", ans);
}
