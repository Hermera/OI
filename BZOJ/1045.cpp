#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6+5;
typedef long long ll;
ll c[maxn], a[maxn], N;
ll ans, mid, ave;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

int main()
{
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read(), ave += a[i];
	ave /= N;
	for(int i = 2; i <= N; ++i) c[i] = c[i-1]+a[i]-ave;
	sort(c+1, c+1+N);
	mid = c[(N>>1)+1];
	for(int i = 1; i <= N; ++i) ans += abs(c[i]-mid);
	printf("%lld\n", ans);
	return 0;
}
