#include <cstdio>
using namespace std;
typedef long long ll;
ll read() {
	char ch = getchar(); ll x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 5e5+5;
ll n, m, ans, a[maxn];
bool d[maxn], vis[maxn];

bool judge(int x) {
	int tot = 0;
	for(int i = 1; i <= n; ++i) d[i] = a[i]&(1LL<<x);
	for(int i = 1; i <= n; ++i) d[i] ^= d[i-1];
	for(int i = 1; i <= n; ++i) if(!d[i] && !vis[i]) ++tot;
	if(tot >= m && !d[n]) {
		for(int i = 1; i <= n; ++i) if(d[i]) vis[i] = 1;
		return 1;
	}
	return 0;
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 62; ~i; --i)
		if(!judge(i)) ans += (1LL<<i);
	printf("%lld\n", ans);
	return 0;
}
