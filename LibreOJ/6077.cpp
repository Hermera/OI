#include <cstdio>
using namespace std;


const int S = 455;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int quickpow(int x, int k) {
	int ret = 1;
	for (; k; k >>= 1, x = 1LL * x * x % mod)
		if (k & 1) ret = 1LL * ret * x % mod;
	return ret;
}


int fac[N << 1], inv[N << 1];
void prepare(int x) {
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= x; ++i) fac[i] = 1LL * fac[i-1] * i % mod;
	for (int i = 1; i <= x; ++i) inv[i] = quickpow(fac[i], mod - 2);
}

int combine(int n, int m) {
	return 1LL * fac[n] * inv[m] % mod * inv[n-m] % mod;
}

void update(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
}


int n, k, s;
int dp[S][N];

int main() {
	freopen("6077.in", "r", stdin);

	scanf("%d%d", &n, &k);
	prepare(2e5);

	dp[0][0] = 1, s = 450;
	for (int i = 1; i <= s; ++i)
		for (int j = 0; j <= k; ++j) {
			if (j >= i) update(dp[i][j], mod - dp[i - 1][j - i]);
			if (j >= i) update(dp[i][j], dp[i][j - i]);
			if (j > n)  update(dp[i][j], dp[i - 1][j - n - 1]);
		}

	int ans = 0;
	for (int i = 0; i <= k; ++i) {
		int ret = 0;
		for (int j = 0; j <= s; ++j)
			update(ret, dp[j][i]);
		update(ans, 1LL * ret * combine(k - i + n - 1, n - 1) % mod);
	}
	printf("%d\n", ans);
	return 0;
}