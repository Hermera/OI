#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 5005;
const int mod = 998244353;

struct ele {
	int x, y, fow, type;
	ele() {}
	ele(int a, int b, int c, int d): x(a), y(b), fow(c), type(d) {}
	bool operator <(const ele &b) const {
		return x < b.x;
	}
} a[maxn], b[maxn];
int n, m, t, k, mx, tot;
ll c[maxn][maxn];

bool judge(int type, int x) {
	k = 0;
	for(int i = 1; i <= tot; ++i) {
		if(a[i].type == type) continue;
		b[++k] = ele(a[i].x, a[i].fow ? x-a[i].y : a[i].y, 0, 0);
		
		if(b[k].y < 0 || b[k].y > x) return 0;
		if(b[k].x < b[k].y) return 0;
		if(b[k].x-b[k-1].x < b[k].y-b[k-1].y) return 0;
		if(b[k].y < b[k-1].y) return 0;
	}
	return 1;
}

int main() {
	for(int i = 0; i < maxn; ++i) c[i][0] = 1;
	for(int i = 1; i < maxn; ++i)
	for(int j = 1; j <= i; ++j)
		c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m), tot = mx = 0;
		for(int i = 1, x, y; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			if(x > y) a[++tot] = ele(x, y, 0, 0);
			if(x < y) a[++tot] = ele(n-y, x, 1, 0);
			if(x == y) mx = max(mx, x);
		}
		a[++tot] = ele(mx, mx, 0, 1);
		a[++tot] = ele(n-mx, mx, 1, 2);
		sort(a+1, a+1+tot);
		
		ll ans = 0;
		for(int o = 1; o <= 3; ++o)
		for(int i = 1; i <= n; ++i) if(judge(o, i))	{
			ll sum = 1;
			for(int j = 1; j <= k; ++j) 
				(sum *= c[b[j].x-b[j-1].x][b[j].y-b[j-1].y])%= mod;
			(sum *= c[n-b[k].x][i-b[k].y])%= mod;
			if(o <= 2) (ans += sum)%= mod;
			else (ans -= sum)%= mod;
		}
		printf("%lld\n", (ans+mod)%mod);
	}
	return 0;
}	
		
