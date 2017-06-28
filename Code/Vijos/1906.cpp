#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
const int mod = 10007;
int n, cnt, bst, h[maxn], fa[maxn], w[maxn], mx[maxn];
ll rt[maxn], ans;

struct Data { int next, to; } G[maxn<<1];
void add(int x, int y) {
	G[++cnt] = (Data){ h[x], y }; h[x] = cnt;
}

void dfs(int x) {
	if(fa[fa[x]]) {
		int ga = fa[fa[x]];
		rt[ga] += w[x];
		mx[ga] = max(mx[ga], w[x]);
	}
	
	ll tmp = 0;
	int fir = 0, sec = 0;
	for(int i = h[x], v; i; i = G[i].next) 
		if((v = G[i].to) != fa[x]) {
			fa[v] = x, dfs(v);
			(ans += w[v]*tmp)%= mod;
			(tmp += w[v])%= mod;
			if(w[v] > fir) sec = fir, fir = w[v];
			else if(w[v] > sec) sec = w[v];
		}
	bst = max(bst, fir*sec);
}

int main() {
	scanf("%d", &n);
	for(int i = 2, u, v; i <= n; ++i)
		scanf("%d%d", &u, &v), add(u, v), add(v, u);
	for(int i = 1; i <= n; ++i) scanf("%d", w+i);
	dfs(1);
	
	for(int i = 1; i <= n; ++i) (ans += w[i]*rt[i])%= mod;
	for(int i = 1; i <= n; ++i) bst = max(bst, w[i]*mx[i]);
	printf("%d %lld\n", bst, (ans*2)%mod);
	return 0;
}
