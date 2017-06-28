#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 65;
const int Mod = 10000007;
ll C[maxn][maxn], N;
int num[maxn], len;

void GetComb()
{
	C[0][0] = C[1][0] = C[1][1] = 1;
	for(int i = 2; i < maxn; ++i)
	for(int j = 0; j < maxn; ++j)
		if(j == 0) C[i][j] = 1;
		else C[i][j] = C[i-1][j-1]+C[i-1][j];
}

ll Solve(int x)
{
	ll ans = 0;
	for(int i = len; i >= 1 && x >= 0; --i)
	if(num[i])
		ans += C[i-1][x], --x;
	return ans;
}

ll QuickPow(ll x, ll k)
{
	ll ans = 1;
	x %= Mod;
	for( ; k; k >>= 1, x *= x, x %= Mod)
	if(k&1) ans *= x, ans %= Mod;
	return ans; 
}

int main()
{
	scanf("%lld", &N); ++N;
	GetComb();
	while(N) num[++len] = N&1, N >>= 1;
	ll ret = 1;
	for(int i = 1; i <= len; ++i)
		ret *= QuickPow(i, Solve(i)), ret %= Mod;
	printf("%lld\n", ret);
	return 0;
}
