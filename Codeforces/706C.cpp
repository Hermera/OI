#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 1e5+5;
const ll inf = 1e16;
struct String {
	vector <char> s;
	void init() {
		char ch = getchar();
		while('a' > ch || ch > 'z') ch = getchar();
		while('a' <= ch && ch <= 'z') s.push_back(ch), ch = getchar();
	}
	
	void reserve() {
		int sz = s.size();
		for(int i = 0; i < sz/2; ++i) swap(s[i], s[sz-i-1]);
	}
	
	bool operator <(const String &b) const {
		int n = s.size(), m = b.s.size();
		for(int i = 0; i < min(n, m); ++i)
			if(s[i] != b.s[i]) return s[i] < b.s[i];
		return n <= m;
	}
} a[maxn][2];
int n, c[maxn];
ll dp[maxn][2];

void update(ll &x, ll y) {
	if(y < x) x = y;
}

int main() {
	freopen("706C.in", "r", stdin);

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", c+i);
	for(int i = 1; i <= n; ++i) 
		a[i][0].init(), a[i][1] = a[i][0], a[i][1].reserve();
	
	memset(dp, 63, sizeof(dp));
	dp[1][0] = 0, dp[1][1] = c[1];
	for(int i = 2; i <= n; ++i) {
		if(a[i-1][0] < a[i][0]) update(dp[i][0], dp[i-1][0]);
		if(a[i-1][1] < a[i][0]) update(dp[i][0], dp[i-1][1]);
		if(a[i-1][0] < a[i][1]) update(dp[i][1], dp[i-1][0]+c[i]);
		if(a[i-1][1] < a[i][1]) update(dp[i][1], dp[i-1][1]+c[i]);
	}
	
	ll ans = min(dp[n][0], dp[n][1]);
	printf("%lld\n", ans > inf ? -1 : ans);
	return 0;
}
