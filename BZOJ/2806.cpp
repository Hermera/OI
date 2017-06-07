#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1100005;
const int INF = 1e9;
int n, m, k, f[maxn], g[maxn];
char str[maxn];

struct Queue {
	int h, t, q[maxn];
	void init() { h = 1, t = 0; }
	void insert(int x) {
		while(h <= t && f[q[t]]-q[t] < f[x]-x) --t;
		q[++t] = x;
	}
	
	int query(int x) {
		while(h <= t && q[h] < x) ++h;
		return h <= t ? q[h] : -1;
	}
} q;

bool check(int x) {
	q.init();
	for(int i = 1; i <= n; ++i) f[i] = INF;
	for(int i = 1, v; i <= n; ++i) {
		f[i] = f[i-1];
		if(i-x >= 0) q.insert(i-x);
		v = q.query(i-g[i]);
		if(~v) f[i] = max(f[i], f[v] + i-v);
	}
	return 10*f[n] >= 9*n;
}

int solve() {
	int l = 1, r = n, ans = 0;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(check(mid)) ans = mid, l = mid+1;
		else r = mid-1;
	}
	return ans;
}


struct node {
	node *p, *s[2];
	int len;
	node(int x = 0): p(0), len(x) { memset(s, 0, sizeof(s)); }
};

struct SAM {
	node *root, *last, gen[maxn];
	int cnt;
	SAM() { cnt = 0, root = last = &gen[++cnt], *root = node(); }
	
	void extend(int w) {
		node *fa = last, *o = &gen[++cnt]; *o = node(fa->len+1);
		while(fa && !fa->s[w]) fa->s[w] = o, fa = fa->p;
		if(!fa) o->p = root;
		else {
			node *now = fa->s[w];
			if(now->len == fa->len+1) o->p = now;
			else {
				node *np = &gen[++cnt]; *np = node(fa->len+1);
				memcpy(np->s, now->s, sizeof(now->s));
				np->p = now->p, now->p = o->p = np;
				while(fa && fa->s[w] == now) fa->s[w] = np, fa = fa->p;
			}
		}
		last = o;
	}
} t;

int idx(char ch) { return ch - '0'; }
int main() {
	scanf("%d%d", &k, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%s", str), t.last = t.root;
		for(int j = 0; str[j]; ++j) t.extend(idx(str[j]));
	}

	while(k--) {
		scanf("%s", str+1), n = strlen(str+1);
		node *now = t.root;
		for(int i = 1; str[i]; ++i) {
			while(!now->s[idx(str[i])] && now != t.root) now = now->p;
			g[i] = min(g[i-1], now->len)+1;
			if(now->s[idx(str[i])]) now = now->s[idx(str[i])];
		}
		printf("%d\n", solve());
	}
	return 0;
}
