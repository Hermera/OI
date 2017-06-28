#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll maxk = 1e5+5;
const ll Mod = 1000000007; 
ll N, M, K;
struct Sq { ll dis, val; } sq[maxk];
inline ll read()
{
	char ch = getchar(); ll sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
ll val, tot, ans = 1, tmp;
bool cmp(Sq a, Sq b) { return a.dis != b.dis ? a.dis < b.dis : a.val < b.val; }

ll QuickPow(ll x, ll k)
{
	ll ans = 1; x %= Mod;
	for( ; k; k >>= 1, x *= x, x %= Mod)
		if(k&1) ans *= x, ans %= Mod;
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read(), K = read();
	for(int i = 1; i <= K; ++i) sq[i].dis = read(), sq[i].val = read();
	sort(sq+1, sq+1+K, cmp);
	tot = M; tmp = val = (ll)((1+N)*N/2)%Mod;
	for(int i = 1; i <= K; ++i)
	{
		if(sq[i].dis != sq[i-1].dis && i != 1)
		   ans = ans*tmp%Mod, tmp = val, --tot;
		if(sq[i].dis != sq[i-1].dis || sq[i].val != sq[i-1].val)
		{
			tmp -= sq[i].val;
			if(tmp < 0) tmp += Mod;
		}
	}
	--tot; ans = ans*tmp%Mod;
	printf("%lld\n", ans*QuickPow(val, tot)%Mod);
	return 0;
}
