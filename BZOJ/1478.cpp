#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 60;
int n, c, mod, tot;
int g[maxn][maxn];
ll ans, fac[maxn], sum[maxn], val[maxn];

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
ll pow(ll x, ll k) {
	ll ret = 1;
	for(; k; k >>= 1, (x *= x) %= mod)
		if(k & 1) (ret *= x) %= mod;
	return ret;
}
ll inv(ll x) { return pow(x, mod-2); }

void calc(int m) {
	ll ret = 0, bot = 1;
	for(int i = 1; i <= m; ++i) ret += (val[i] >> 1) * sum[i];
	for(int i = 1; i <= m; ++i) ret += val[i] * sum[i] * (sum[i]-1) >> 1;
	for(int i = 1; i <= m; ++i)
	for(int j = 1; j != i; ++j)
		ret += g[val[i]][val[j]] * sum[i] * sum[j];
	ret = pow(c, ret) * fac[n] % mod;
	for(int i = 1; i <= m; ++i) (bot *= pow(val[i], sum[i])) %= mod;
	for(int i = 1; i <= m; ++i) (bot *= fac[sum[i]]) %= mod;
	(ans += ret * inv(bot)) %= mod;
}


void dfs(int num, int left) {
	if(!left) return calc(tot);
	if(num > left) return;
	dfs(num+1, left);
	for(int i = 1; i*num <= left; ++i) {
		sum[++tot] = i;
		val[tot] = num;
		dfs(num+1, left - i*num);
		--tot;
	}
}

int main() {
	scanf("%d%d%d", &n, &c, &mod);
	
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j) 
		g[i][j] = gcd(i, j);
	
	dfs(1, n);
	(ans *= inv(fac[n])) %= mod;
	printf("%lld\n", ans);
	return 0;
}
