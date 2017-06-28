#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 5e5+5;
const ll oo = 1LL<<62;
int n, m, len, type, last, cnt, root;
int seq[maxn], ls[maxn], rs[maxn];
char s[maxn], op[3];
struct Node {
	int key; ll id;
} g[maxn];
bool cmp(int x, int y) {
	if(s[x] == s[y]) return g[x-1].id < g[y-1].id;
	return s[x] < s[y];
}

struct Treap {
	void rebuild(int &o, ll l, ll r) {
		if(!o) return;
		g[o].id = (l+r)>>1;
		rebuild(ls[o], l, g[o].id);
		rebuild(rs[o], g[o].id, r);
	}
	
	void zig(int &o, ll l, ll r) {
		int k = ls[o];
		ls[o] = rs[k], rs[k] = o, o = k;
		rebuild(o, l, r);
	}
	
	void zag(int &o, ll l, ll r) {
		int k = rs[o];
		rs[o] = ls[k], ls[k] = o, o = k;
		rebuild(o, l, r);
	}
		
	void insert(int &o, ll l, ll r, int p) {
		if(!o) {
			o = p;
			g[o].key = rand(), g[o].id = (l+r)>>1;
			return;
		}
		if(cmp(p, o)) {
			insert(ls[o], l, g[o].id, p);
			if(g[ls[o]].key > g[o].key) zig(o, l, r);
		} else {
			insert(rs[o], g[o].id, r, p);
			if(g[rs[o]].key > g[o].key) zag(o, l, r);
		}
	}
} T;

#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Segment {
	int t[maxn<<2];
	int merge(int x, int y) {
		if(!x || !y) return x|y;
		return g[seq[x]].id <= g[seq[y]].id ? x : y;
	}
	
	void build(int o, int l, int r) {
		if(l == r) t[o] = l;
		else build(lc), build(rc), t[o] = merge(t[o<<1], t[o<<1|1]);
	}
	
	void modify(int o, int l, int r, int p) {
		if(l == r) return;
		if(p <= mid) modify(lc, p);
		else modify(rc, p);
		t[o] = merge(t[o<<1], t[o<<1|1]);
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[o];
		if(R < l || r < L) return 0;
		return merge(query(lc, L, R), query(rc, L, R));
	}
} S;

int main() {
	n = read(), m = read();
	len = read(), type = read();
	scanf("%s", s+1);
	
	for(int i = 1; i <= len; ++i) s[i] -= 'a';
	for(int i = 1; i <= (len>>1); ++i) swap(s[i], s[len-i+1]);
	for(int i = 1; i <= n; ++i) seq[i] = read();
	for(int i = 1; i <= len; ++i) 
		T.insert(root, 0, oo, i);
	
	S.build(1, 1, n);
	for(int x; m; --m) {
		scanf("%s", op), x = read(), last *= type;
		if(*op == 'I') s[++len] = (x^last), T.insert(root, 0, oo, len);
		else if(*op == 'C') seq[x] = read(), S.modify(1, 1, n, x);
		else printf("%d\n", last = S.query(1, 1, n, x, read()));
	}
	return 0;
}
