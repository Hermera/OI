#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, oo = 1<<30;
int N, P, mod, cnt, root, sum;
int size[maxn], pre[maxn], suf[maxn], head[maxn], pow[maxn], inv[maxn];
bool vis[maxn];
ll ans;
struct Data { int next, to, w; } data[maxn<<1];
struct chain { int fir, sec; };
vector <chain> F, G;
void add(int x, int y, int w) {
	data[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
}

void Find(int x, int fa, int tot) {
	size[x] = 1;
	int ret = 0;
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa && !vis[data[i].to]) {
		Data &e = data[i];
		Find(e.to, x, tot);
		size[x] += size[e.to];
		ret = max(ret, size[e.to]);
	}
	ret = max(ret, tot-size[x]);
	if(ret < sum) root = x, sum = ret;
}

void dfs(int x, int fa, int d, int w1, int w2) {
	G.push_back((chain){ w1, 1LL*(mod-w2)*inv[d]%mod });
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa && !vis[data[i].to]) {
		Data &e = data[i];
		dfs(e.to, x, d+1, (w1+1LL*e.w*pow[d])%mod, (10LL*w2%mod+e.w)%mod);
	}
}

ll calc(vector <chain> &s) {
	ll ret = 0, n = s.size();
	for(int i = 0; i < n; ++i)
		pre[i+1] = s[i].fir, suf[i+1] = s[i].sec;
		
	sort(pre+1, pre+1+n);
	sort(suf+1, suf+1+n);
	for(int l = 1, r = 1, i = 1; i <= n; ++i) {
		while(l <= n && pre[l] < suf[i]) ++l;
		while(r <= n && pre[r] <= suf[i]) ++r;
		ret += r-l;
	}
	return ret;
}

void solve(int x, int tot) {
	sum = oo, Find(x, 0, tot);
	vis[root] = 1;
	
	F.clear();
	F.push_back((chain){ 0, 0 }); --ans;
	for(int i = head[root]; i; i = data[i].next) 
	if(!vis[data[i].to]) {
		Data &e = data[i];	
		G.clear();
		dfs(e.to, 0, 1, e.w%mod, e.w%mod);	
		size[e.to] = G.size();
		ans -= calc(G);
		F.insert(F.end(), G.begin(), G.end());
	}
	
	ans += calc(F);
	for(int i = head[root]; i; i = data[i].next) 
		if(!vis[data[i].to]) solve(data[i].to, size[data[i].to]);
}

int GetPhi(int n) {
	int ret = 1;
	for(int i = 2; i*i <= n; ++i) 
		if(n%i == 0) {
			n /= i, ret *= i-1;
			while(n%i == 0) n /= i, ret *= i;
		}
	if(n > 1) ret *= n-1;
	return ret;
}

ll quickpow(ll x, ll k) {
	ll ret = 1;
	for( ; k; k >>= 1, (x *= x)%= mod)
		if(k&1) (ret *= x)%= mod;
	return ret;
}

int main() {
//	freopen("715C.in", "r", stdin);
	N = read(), mod = read();
	for(int i = 1, u, v, w; i < N; ++i) {
		u = read()+1, v = read()+1, w = read();
		add(u, v, w), add(v, u, w);
	}
	
	pow[0] = inv[0] = 1, P = GetPhi(mod);
	for(int i = 1; i <= N; ++i) pow[i] = 10LL*pow[i-1]%mod;
	for(int i = 1; i <= N; ++i) inv[i] = quickpow(pow[i], P-1);
	
	solve(1, N);
	printf("%lld\n", ans);
	return 0;
}
