#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e4+5;
const int INF = 1e9;
struct node { 
	node *ls, *rs;
	int sum, pre, suf;
	node(); 
} *emt = new node();
node::node() { ls = rs = emt; sum = 0, pre = suf = -INF; }
node gen[maxn*20], *root[maxn];
int n, m, a, b, c, d, cnt, last;
int v[maxn], h[maxn];
vector <int> g[maxn];

#define mid (l+r>>1)
#define lc o->ls, l, mid
#define rc o->rs, mid+1, r
struct Persist_Segment {
	void pushup(node *o) {
		o->sum = o->ls->sum+o->rs->sum;
		o->pre = max(o->ls->pre, o->ls->sum+o->rs->pre);
		o->suf = max(o->rs->suf, o->rs->sum+o->ls->suf);
	}

	void build(node *&o, int l, int r) {
		o = &gen[++cnt];
		if(l == r) o->sum = o->pre = o->suf = 1;
		else build(lc), build(rc), pushup(o);
	}
	
	void modify(node *&o, int l, int r, int p, int v) {
		node *x = &gen[++cnt];
		*x = *o, o = x;
		if(l == r) { o->sum += v, o->pre += v, o->suf += v; return; }
		if(p <= mid) modify(lc, p, v);
		else modify(rc, p, v);
		pushup(o);
	}
	
	node *get(node *o, int l, int r, int L, int R) {
		if(R < l || r < L) return emt;
		if(L <= l && r <= R) return o;
		node *x = new node(), *o1 = get(lc, L, R), *o2 = get(rc, L, R);
		x->sum = o1->sum+o2->sum;
		x->pre = max(o1->pre, o1->sum+o2->pre);
		x->suf = max(o2->suf, o2->sum+o1->suf);
		return x;
	}
} T;

bool judge(int x) {
	int sum = T.get(root[x], 1, n, a, b)->suf+T.get(root[x], 1, n, c, d)->pre;
	if(b+1 <= c-1) sum += T.get(root[x], 1, n, b+1, c-1)->sum;
	return sum >= 0; 
}

int q[10];
void load() {
	for(int i = 0; i < 4; ++i) q[i] = (last+read())%n+1;
	sort(q, q+4);
	a = q[0], b = q[1], c = q[2], d = q[3];
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) v[i] = h[i] = read();
	sort(h+1, h+1+n);
	for(int i = 1; i <= n; ++i) v[i] = lower_bound(h+1, h+1+n, v[i])-h;
	for(int i = 1; i <= n; ++i) g[v[i]].push_back(i);
	for(int i = 0; i <= n; ++i) root[i] = emt;
	T.build(root[0], 1, n);
	for(int i = 1; i <= n; ++i) {
		root[i] = root[i-1];
		if(!g[i-1].empty()) for(int j = 0; j < g[i-1].size(); ++j)
			T.modify(root[i], 1, n, g[i-1][j], -2);
	}			
	
	m = read();
	for(int l, r, ans; m--; ) {
		load();
		l = 1, r = n, ans = 1;
		while(l <= r) 
			if(judge(mid)) ans = mid, l = mid+1;
			else r = mid-1;
		printf("%d\n", last = h[ans]);
	}
	return 0;
}
