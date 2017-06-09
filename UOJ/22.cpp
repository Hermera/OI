#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 5005;
const int mod = 998244353;

int n, m, x;
int a[N], b[N], c[N][N], p[N][N];
ll fac[N], dp[N];

int main() {
	scanf("%d%d", &n, &x);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + 1 + n);
	
	m = max(m, x);
	for(int i = 1; i <= n; ++i) m = max(m, a[i]);
	for(int i = 1; i <= n; ++i) ++b[a[i]];
	for(int i = 1; i <= m; ++i) b[i] += b[i-1];
	
	fac[0] = 1;
	for(int i = 1; i <= m; ++i) fac[i] = fac[i-1] * i % mod;
	for(int i = 0; i <= m; ++i) c[i][0] = p[i][0] = 1;
	for(int i = 1; i <= m; ++i)
	for(int j = 1; j <= i; ++j) {
		c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
		p[i][j] = fac[j] * c[i][j] % mod;
	}
		
	dp[x] = p[n][b[m]-b[x]];
	for(int i = x; i; --i) if(dp[i])
		for(int j = 1; j <= n; ++j)
			if(a[j] <= i) {
				int v = i % a[j];
				(dp[v] += dp[i] * p[b[i]-1][b[i]-b[v]-1]) %= mod;
			}
	
	for(int i = a[1]-1; ~i; --i) 
		if(dp[i]) {
			printf("%d\n%lld\n", i, dp[i]);
			return 0;
		}
}
