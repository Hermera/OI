#include <cstdio>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int n, m, q, cnt, root[maxn], fa[maxn], v[maxn];
struct Segment {
	#define mid (l+r>>1)
	#define lc t[o].l, l, mid
	#define rc t[o].r, mid+1, r
	struct Node { int l, r, size, id; } t[maxn*20];
	void insert(int &o, int l, int r, int p, int v) {
		o = ++cnt;
		++t[o].size, t[o].id = v;
		if(l == r) return;
		if(p <= mid) insert(lc, p, v);
		else insert(rc, p, v);
	}
	
	int merge(int o1, int o2) {
		if(!o1 || !o2) return o1|o2;
		t[o1].l = merge(t[o1].l, t[o2].l);
		t[o1].r = merge(t[o1].r, t[o2].r);
		t[o1].size = t[t[o1].l].size + t[t[o1].r].size;
		return o1;
	}
	
	int count(int o) { return t[o].size; }
	int query(int o, int l, int r, int p) {
		if(l == r) return t[o].id;
		if(t[t[o].l].size >= p) return query(lc, p);
		else return query(rc, p-t[t[o].l].size);
	}
} T;

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
void Union(int x, int y) {
	x = Find(x), y = Find(y), fa[x] = y;
	root[y] = T.merge(root[x], root[y]);
}

char op[3];
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i) T.insert(root[i], 1, n, v[i] = read(), i);
	for(int i = 1, x, y; i <= m; ++i) Union(read(), read());
	
	q = read();
	for(int i = 1, x, k; i <= q; ++i) {
		scanf("%s", op);
		if(*op == 'B') Union(read(), read());
		else {
			x = Find(read()), k = read();
			if(T.count(root[x]) < k) printf("-1\n");
			else printf("%d\n", T.query(root[x], 1, n, k));
		}
	}
	return 0;
}
