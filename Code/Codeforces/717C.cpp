#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5+5, Mod = 10007;
int N, a[maxn];
long long ans;

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) scanf("%d", a+i);
	sort(a+1, a+1+N);
	for(int i = 1; i <= N; ++i)
		(ans += 1LL*a[i]*a[N-i+1])%= Mod;

	printf("%lld\n", ans);
	return 0;
}
