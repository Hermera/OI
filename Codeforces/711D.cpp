#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5, mod = 1e9+7;
int n, a[maxn], q[maxn], fa[maxn], deg[maxn];
vector <int> G[maxn];

ll pow(ll x, ll k) {
	ll ret = 1;
	for(; k; k >>= 1, (x *= x)%= mod)
		if(k&1) (ret *= x)%= mod;
	return ret;
}

ll solve(vector <int> &T) {
	int h = 1, t = 0, sz = T.size();
	for(int i = 0; i < sz; ++i) if(deg[T[i]] == 1) q[++t] = T[i];
	while(h <= t) {
		int v = q[h++];
		if((--deg[a[v]]) == 1) q[++t] = a[v];
	}
	return (pow(2, sz) - 2LL*pow(2, t))%mod;
}

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void Union(int x, int y) { fa[Find(x)] = Find(y); }

int main() {
	freopen("711D.in", "r", stdin);

	n = read();
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i) Union(i, a[i] = read());
	for(int i = 1; i <= n; ++i) ++deg[i], ++deg[a[i]];
	for(int i = 1; i <= n; ++i) G[Find(i)].push_back(i);
	
	ll ans = 1;
	for(int i = 1; i <= n; ++i) 
		if(G[i].size()) (ans *= solve(G[i]))%= mod;
	printf("%lld\n", (ans+mod)%mod);
	return 0;
}
	
