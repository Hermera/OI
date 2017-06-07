#include <cstdio>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e4+5;
int N, Mod, p[maxn], cnt;
bool vis[maxn];

void PreWork() {
	for(int i = 2; i < maxn; ++i) {
		if(!vis[i]) vis[i] = true, p[++cnt] = i;
		for(int j = 1; j <= cnt && i*p[j] < maxn; ++j) {
			vis[i*p[j]] = true;
			if(i%p[j] == 0) break;
		}
	}
}

ll QuickPow(ll x, ll k) {
	ll ret = 1; x %= Mod;
	for( ; k; k >>= 1, (x *= x)%= Mod) 
		if(k&1) (ret *= x)%= Mod;
	return ret;
}

int Phi(int n) {
	int ret = n;
	for(int i = 1; p[i]*p[i] <= n; ++i)
		if(n%p[i] == 0) {
			ret = ret-ret/p[i];
			while(n%p[i] == 0) n /= p[i];
		}
	if(n > 1) ret -= ret/n;
	return ret%Mod;
}

int main() {
	PreWork();
	for(int T = read(); T; --T) {
		ll ans = 0;
		N = read(), Mod = read();
		for(int i = 1; i*i <= N; ++i) { 
			if(N%i == 0) {
				(ans += QuickPow(N, i-1)*Phi(N/i)) %= Mod;
				if(i != N/i) (ans += QuickPow(N, N/i-1)*Phi(i)) %= Mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
