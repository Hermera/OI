#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
const ll oo = 1e16;
int n, m;
ll a[maxn], dp[maxn];

int main() {
	freopen("244.in", "r", stdin);

	n = read()+1;
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n/2; ++i) swap(a[i], a[n-i+1]);
	
	ll mn = oo, tot = 2*n-2, sum = 0;
	for(int i = 1; i <= n; ++i) {
		mn = min(mn, a[i]);
		dp[i] = sum + a[i] + mn*tot;
		tot -= 2;
		sum += a[i]+mn;
	}
	
	ll ans = oo;
	for(int i = 1; i <= n; ++i)
		ans = min((dp[i]<<1)-a[i], ans);
	printf("%lld\n", ans);
	return 0;
}
		
