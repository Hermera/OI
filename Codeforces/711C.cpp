#include <cstdio>
#include <cstring>
#define Int register int
using namespace std;
typedef long long ll;

const int maxn = 105;
int N, M, K, c[maxn];
ll v[maxn][maxn], dp[maxn][maxn][maxn];

void update(ll &x, ll y) {
	if(x < 0) x = y;
	if(y < x) x = y;
}

int main() {
	freopen("711C.in", "r", stdin);

	scanf("%d%d%d", &N, &M, &K);
	for(Int i = 1; i <= N; ++i) scanf("%d", c+i);
	for(Int i = 1; i <= N; ++i)
	for(Int j = 1; j <= M; ++j)
		scanf("%lld", &v[i][j]);
	
	memset(dp, -1, sizeof(dp));
	dp[0][0][0] = 0;
		
	for(Int i = 1; i <= N; ++i)
	if(c[i]) {
		for(Int k = 1; k <= K; ++k)
		for(Int p = 0; p <= M; ++p) {
			if(p == c[i] && (~dp[i-1][k][p]))
				update(dp[i][k][c[i]], dp[i-1][k][p]);
			if(p != c[i] && (~dp[i-1][k-1][p]))
				update(dp[i][k][c[i]], dp[i-1][k-1][p]);
		}
	} else {
		for(Int j = 1; j <= M; ++j)
		for(Int k = 1; k <= K; ++k)
		for(Int p = 0; p <= M; ++p) {
			if(j == p && (~dp[i-1][k][p]))
				update(dp[i][k][j], dp[i-1][k][p]+v[i][j]);
			if(j != p && (~dp[i-1][k-1][p]))
				update(dp[i][k][j], dp[i-1][k-1][p]+v[i][j]);
		}
	}
	
	ll ans = -1;
	for(Int i = 1; i <= M; ++i) if(~dp[N][K][i]) update(ans, dp[N][K][i]);
	printf("%lld\n", ans);
	return 0;
}
		
