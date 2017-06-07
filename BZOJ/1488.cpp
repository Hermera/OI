#include <cstdio>
using namespace std;

const int mod = 997;
const int maxn = 65;
const int maxs = 1005;
int n, ans, g[maxn][maxn], v[maxn], w[maxn], fac[maxn];
int inv[maxs];

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int pow(int x, int k) {
	int ret = 1;
	for(; k; k >>= 1, (x *= x) %= mod)
		if(k & 1) (ret *= x) %= mod;
	return ret;
}

void calc(int m) {
	int ret = 0;
	for(int i = 1; i <= m; ++i) ret += v[i] >> 1;
	for(int i = 1; i <= m; ++i)
	for(int j = 1; j != i; ++j)
		ret += g[v[i]][v[j]];
	ret = pow(2, ret);
	(ret *= fac[n]) %= mod;
	
	for(int i = 1; i <= n; ++i) w[i] = 0;
	for(int i = 1; i <= m; ++i) ++w[v[i]];
	for(int i = 1; i <= m; ++i) (ret *= inv[v[i]]) %= mod;
	for(int i = 1; i <= n; ++i) (ret *= inv[fac[w[i]]]) %= mod;
	(ans += ret) %= mod;
}


void dfs(int num, int last, int left) {
	if(!left) return calc(num-1);
	for(int i = last; i <= left; ++i)
		v[num] = i, dfs(num+1, i, left-i);
}

int main() {
	scanf("%d", &n);
	
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
	for(int i = 1; i < mod; ++i) inv[i] = pow(i, mod-2);
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j) 
		g[i][j] = gcd(i, j);
	
	dfs(1, 1, n);
	(ans *= inv[fac[n]]) %= mod;
	printf("%d\n", ans);
	return 0;
}
