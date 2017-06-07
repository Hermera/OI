#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const int mod = 1000000001;
const int maxt = 20;
const int r = 18, c = 11;
int n, b[maxt], a[maxt][maxt], f[maxt][(1<<c)+5];
bool vis[maxn];

ll solve(int x) {
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	memset(f, 0, sizeof f);
	a[1][1] = x;
	for(int i = 2; i <= c; ++i)
		if(a[1][i-1]*3 <= n) a[1][i] = a[1][i-1]*3;
	for(int i = 2; i <= r; ++i)
	for(int j = 1; j <= c; ++j)
		if(a[i-1][j]*2 <= n) a[i][j] = a[i-1][j]*2;
	for(int i = 1; i <= r; ++i)
	for(int j = 1; j <= c; ++j)
		if(a[i][j]) b[i] += (1<<j-1), vis[a[i][j]] = 1;
	
	f[0][0] = 1;
	for(int i = 1; i <= r; ++i)
		for(int s = 0; s <= b[i-1]; ++s) if(f[i-1][s])
		for(int t = 0; t <= b[i]; ++t) 
			if(!(s&t) && !(t&(t>>1))) 
				(f[i][t] += f[i-1][s])%= mod;
	ll ret = 0;
	for(int s = 0; s <= b[r]; ++s) ret += f[r][s];
	return ret;
}

int main() {
	ll ans = 1;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) (ans *= solve(i))%= mod;
	printf("%lld\n", ans);
	return 0;
}
