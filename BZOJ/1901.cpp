#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e4+5;
struct node {
	int sum;
	node *ls, *rs;
	node();
} *emt = new node(), gen[maxn*100];
node::node() { sum = 0, ls = rs = emt; }
node *root[maxn], *L[maxn], *R[maxn];
int n, m, p, q, c, cnt;
int h[maxn], a[maxn];

#define mid (l+r>>1)
struct Persist_Segment {
	void add(node *&o, int l, int r, int p, int v) {
		if(o == emt) {
			node *x = &gen[++cnt]; 
			*x = *o, o = x;
		}
		o->sum += v;
		if(l == r) return;
		if(p <= mid) add(o->ls, l, mid, p, v);
		else add(o->rs, mid+1, r, p, v);
	}
	
	int query(int l, int r, int k) {
		if(l == r) return l;
		int sum = 0;
		for(int i = 1; i <= p; ++i) sum -= L[i]->ls->sum;
		for(int i = 1; i <= q; ++i) sum += R[i]->ls->sum;
		if(sum >= k) {
			for(int i = 1; i <= p; ++i) L[i] = L[i]->ls;
			for(int i = 1; i <= q; ++i) R[i] = R[i]->ls;
			return query(l, mid, k);
		} else {
			for(int i = 1; i <= p; ++i) L[i] = L[i]->rs;
			for(int i = 1; i <= q; ++i) R[i] = R[i]->rs;
			return query(mid+1, r, k-sum);
		}
	}
} T;

char str[10];
struct Opt { int x, y, z; } op[maxn];
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = h[++c] = read();
	for(int i = 1; i <= m; ++i) {
		scanf("%s", str);
		op[i].x = read(), op[i].y = read();
		if(*str == 'Q') op[i].z = read();
		else h[++c] = op[i].y;
	}
	sort(h+1, h+1+c);
	c = unique(h+1, h+1+c)-h-1;
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(h+1, h+1+c, a[i])-h;
	for(int i = 1; i <= m; ++i)
		if(!op[i].z) op[i].y = lower_bound(h+1, h+1+c, op[i].y)-h;
	
	emt->ls = emt->rs = emt;
	for(int i = 1; i <= n; ++i) root[i] = emt;
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; j += j&-j)
			T.add(root[j], 1, c, a[i], 1);
	for(int i = 1; i <= m; ++i) {
		Opt &e = op[i];
		if(e.z) {
			p = q = 0, --e.x;
			for(int j = e.x; j; j -= j&-j) L[++p] = root[j];
			for(int j = e.y; j; j -= j&-j) R[++q] = root[j];
			printf("%d\n", h[T.query(1, c, e.z)]);
		} else {
			for(int j = e.x; j <= n; j += j&-j) T.add(root[j], 1, c, a[e.x], -1);
			a[e.x] = e.y;
			for(int j = e.x; j <= n; j += j&-j) T.add(root[j], 1, c, a[e.x], 1);
		}
	}
	return 0;
}
