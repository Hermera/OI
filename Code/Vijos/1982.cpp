#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1005;
const int maxm = 205;
const int mod = 1e9+7;
int n, m, k, o, dp[2][maxn][maxm][2];
char s[maxn], t[maxm];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s%s", s+1, t+1);
	
	#define f dp[o]
	#define g dp[!o]
	for(int i = 0; i <= n; ++i) g[i][0][0] = 1;
	for(int i = 1; i <= m; ++i, o ^= 1) {
		memset(f, 0, sizeof(f));
		for(int j = 1; j <= n; ++j)
		for(int d = 0; d <= k; ++d) {
			(f[j][d][0] = f[j-1][d][0]+f[j-1][d][1])%= mod;
			if(t[i] == s[j]) {
				if(d) (f[j][d][1] += g[j-1][d-1][0]+g[j-1][d-1][1])%= mod;
				(f[j][d][1] += g[j-1][d][1])%= mod;
			}
		}
	}
	
	printf("%d\n", (g[n][k][0]+g[n][k][1])%mod);
	return 0;	
}
