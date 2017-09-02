#include <cstdio>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 1e6+5;
const int L = 20;
const int mod = 1e9+7;

int n, q, r;
int low[N], tag[N], vis[N];
ll dp[N][L];

void prework() {
	n = 1e6;
	for(int i = 2; i <= n; ++i)
		if(!vis[i]) {
			low[i] = i;
			for(ll j = i, t = 0; j <= n; j *= i) tag[j] = ++t;
			for(int j = i+i; j <= n; j += i) {
				vis[j] = 1;
				low[j] = low[j/i];
				if(!(low[j]%i)) low[j] *= i;
			}
		}
	
	ll sum = 0;
	dp[0][0] = 1;
	for(int i = 1; i <= 20; ++i) dp[0][i] = 2;	
	for(int i = 1; i <= n; ++i) {
		sum = 0;
		for(int j = 0; j <= 20; ++j) {
			(sum += dp[i-1][j]) %= mod;
			dp[i][j] = sum;
		}
	}
}

ll f(int x, int y) {
	if(y == 1) return 1;
	if(tag[y]) return dp[x][tag[y]];
	return f(x, low[y]) * f(x, y / low[y]) % mod;
}


int main() {
	prework();
	q = read();
	while(q--) {
		r = read(), n = read();
		printf("%lld\n", f(r, n));
	}
	return 0;
}
