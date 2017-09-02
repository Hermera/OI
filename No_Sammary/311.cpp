#include <cstdio>
#include <cstring>
using namespace std;

const int N = 405;
const int mod = 998244353;

int n, m, w[N];
int fac[N][N];
int dp[2][N][N], h[N], o;
#define f dp[o]
#define g dp[!o]

void update(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}


int main() {
	freopen("311.in", "r", stdin);

	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	for (int i = 0; i <= n; ++i) {
		fac[i][0] = 1; 
		for (int j = 1; j <= n; ++j)
			fac[i][j] = 1LL * fac[i][j - 1] * i % mod;
	}
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			g[i][j] = 1LL * fac[i - 1][j - 1] * w[i] % mod;
	
	for (int i = m + 1; i <= n; ++i) {
		memset(f, 0, sizeof(f));
		memset(h, 0, sizeof(h));
		for (int j = 1; j <= n; ++j) 
			for (int k = 1; k <= m; ++k)
				update(h[j], 1LL * g[j][k] * fac[j][m - k] % mod);
				
		for (int j = 1; j <= n; ++j) {
			// bigger
			for (int k = 1; k < j; ++k)
				update(f[j][m], h[k]);
			
			// equal
			for (int k = 2; k <= m; ++k) 
				update(f[j][k - 1], g[j][k]);
			for (int k = 1; k <= m; ++k)
				update(f[j][k], 1LL * g[j][1] * fac[j - 1][k - 1] % mod);
			
			// smaller
			int total = 0;
			for (int k = j + 1; k <= n; ++k)
				update(total, g[k][1]);
			for (int k = 1; k <= m; ++k)
				update(f[j][k], 1LL * total * fac[j - 1][k - 1] % mod);
				
			for (int k = 1; k <= m; ++k)
				f[j][k] = 1LL * f[j][k] * w[j] % mod;
		}
		o ^= 1;
	}
	
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		for (int k = 1; k <= m; ++k)
			update(ans, 1LL * g[i][k] * fac[i][m - k] % mod);
	update(ans, mod);
	printf("%d\n", ans);
	return 0;
}
