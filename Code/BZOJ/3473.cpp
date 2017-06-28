#include <cstdio>
#include <vector>
#include <cstring>
#define pb push_back
using namespace std;

const int maxn = 4e5+5;
const int maxs = 26;

namespace FenwickTree {
	int t[maxn], c;
	void init(int x) { c = x; }
	void modify(int x, int v) {
		for(; x <= c; x += x&-x) t[x] += v;
	}
	
	int query(int x) {
		int ret = 0;
		for( ; x; x -= x&-x) ret += t[x];
		return ret;
	}
};


#define FOR(x, y) for(int (x) = 0; (x) < (y).size(); ++(x))
#define REP(x) for(it = x.begin(); it != x.end(); ++it)
vector <int> a[maxn], b[maxn], g[maxn];
vector <int>:: iterator it;

int n, k;
char str[maxn];

namespace SuffixAutomation {
	int last, root, cnt, tim;
	int p[maxn], pre[maxn], val[maxn], sum[maxn], len[maxn], dfn[maxn], s[maxn][maxs];
	int newnode(int x) { ++cnt, p[cnt] = 0, len[cnt] = x; return cnt; }
	void init() { cnt = 0, last = root = newnode(0); }
	void reset() { last = root; }
	
	void extend(int w, int id) {
		int fa = last, o = newnode(len[fa]+1);
		while(!s[fa][w] && fa) s[fa][w] = o, fa = p[fa];
		if(!fa) p[o] = root;
		else {
			int now = s[fa][w];
			if(len[now] == len[fa]+1) p[o] = now;
			else {
				int np = newnode(len[fa]+1);
				memcpy(s[np], s[now], sizeof s[now]);
				p[np] = p[now], p[now] = p[o] = np;
				while(fa && s[fa][w] == now) s[fa][w] = np, fa = p[fa];
			}
		}		
		last = o, a[id].pb(o), b[o].pb(id);
	}
	
	
	void dfs(int x) {
		if(sum[x] < k) val[x] = val[p[x]];
		else val[x] = len[x];
		FOR(i, g[x]) dfs(g[x][i]);
	}
	
	void solve(int x) {
		using namespace FenwickTree;
		dfn[x] = ++tim;
		FOR(i, g[x]) solve(g[x][i]);
		REP(b[x]) {
			if(pre[*it]) modify(pre[*it], -1);
			modify(pre[*it] = dfn[x], 1);
		}
		sum[x] = query(tim)-query(dfn[x]-1);
	}
	
};

int main() {
	using namespace SuffixAutomation;

	init();
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", str), reset();
		for(int j = 0; str[j]; ++j) 
			extend(str[j]-'a', i);
	}
	for(int i = 1; i <= cnt; ++i) g[p[i]].pb(i);
	
	FenwickTree::init(cnt+5);
	solve(root);
	dfs(root);
	
	for(int i = 1; i <= n; ++i) {
		long long ans = 0;
		REP(a[i]) ans += val[*it];
		printf("%lld", ans);
		if(i != n) printf(" ");
	}
	return 0;
}
