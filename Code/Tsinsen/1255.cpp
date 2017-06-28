#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 2e6+5, Mod = 19930726;
int N, p[maxn];
ll cnt[maxn], K, sum;
char s[maxn];

ll QuickPow(ll x, ll k) {
	ll ans = 1;
	x %= Mod;
	for( ; k; k >>= 1, (x *= x)%= Mod)
		if(k&1) (ans *= x) %= Mod;
	return ans;
}

int main() {
	freopen("data.in", "r", stdin);

	scanf("%d%lld%s", &N, &K, s);
	
	int len = strlen(s), id = 0;
	for(int i = len; ~i; --i) s[i+i+2] = s[i], s[i+i+1] = '#';
	s[0] = '*';
	
	for(int i = 2; i <= (len<<1); ++i) {
		if(p[id]+id > i) p[i] = min(p[2*id-i], p[id]+id-i);
		else p[i] = 1;
		
		while(s[i-p[i]] == s[i+p[i]]) ++p[i];
		if(id+p[id] < i+p[i]) id = i;
	}
	
	for(int i = 2; i <= (len<<1); ++i) 
		if(s[i] != '#') p[i] >>= 1, ++cnt[0], --cnt[p[i]];
	for(int i = 1; i <= len; ++i) cnt[i] += cnt[i-1];
	for(int i = 0; i <= len; ++i) sum += cnt[i];
	
	if(sum < K) printf("-1\n");
	else {
		ll ans = 1;
		for(int i = len; i; --i) {
			(ans *= QuickPow(i*2+1, min(cnt[i], K)))%= Mod;
			K -= cnt[i];
			if(K <= 0) break;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
