#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <assert.h>
using namespace std;
typedef long long ll;

const int maxn = 65;
const int maxb = 25;
int n, m, r, b, g, mod;
int a[maxn], v[maxn], vis[maxn];
int dp[maxn][maxb][maxb][maxb];
ll ans;

void inc(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}

int exgcd(int x, int y, int &a, int &b) {
	if(!y) return a = 1, b = 0, x;
	int ret = exgcd(y, x % y, b, a);
	return b -= x/y*a, ret;
}

int inv(int x) {
	int a, b, ret = exgcd(x, mod, a, b);
	if(ret != 1) return -1;
	return (a % mod + mod) % mod;
}

void calc(int t) {
	memset(dp, 0, sizeof(dp));

	dp[0][0][0][0] = 1;
	for(int i = 1; i <= t; ++i)
	for(int x = 0; x <= r; ++x)
	for(int y = 0; y <= b; ++y)
	for(int z = 0; z <= g; ++z) if(dp[i-1][x][y][z]) {
		int &ret = dp[i-1][x][y][z];
		if(x+v[i] <= r) inc(dp[i][x+v[i]][y][z], ret);
		if(y+v[i] <= b) inc(dp[i][x][y+v[i]][z], ret);
		if(z+v[i] <= g) inc(dp[i][x][y][z+v[i]], ret);
	}
	(ans += dp[t][r][b][g]) %= mod;
}

vector <int> p;
set < vector <int> > s;
set < vector <int> >:: iterator it;

int main() {
	scanf("%d%d%d%d%d", &r, &b, &g, &m, &mod);
	n = r + b + g;
	for(int j = 1; j <= m; ++j) {
		p.clear();
		for(int i = 1, x; i <= n; ++i) 
			scanf("%d", &x), p.push_back(x);
		s.insert(p);
	}
	p.clear();
	for(int i = 1; i <= n; ++i) p.push_back(i);
	s.insert(p);
	
	m = 0;
	for(it = s.begin(); it != s.end(); ++it) {
		int t = 0;
		for(int i = 1; i <= n; ++i) a[i] = (*it)[i-1];
		for(int i = 1; i <= n; ++i) vis[i] = 0;
		for(int i = 1; i <= n; ++i) 
			if(!vis[i]) {
				int siz = 0, x = i;
				do ++siz, vis[x] = 1, x = a[x];
				while(x != i);
				v[++t] = siz;
			}
		calc(t), ++m;
	}
	
	(ans *= inv(m)) %= mod;
	printf("%lld\n", ans);
	return 0;
}
