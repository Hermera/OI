#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5, inf = 1e9;
int N, M, K, Y, last, cnt, root[maxn];

struct Node {
	bool rev;
	int val;
	Node *s[2], *p, *mn;
	void sets(Node *x, int d) { (s[d] = x)->p = this; }
	bool isroot() { return this != p->s[0] && this != p->s[1]; }
	bool pos() { return this == p->s[1]; }
	void update(Node *emt) {
		mn = this;
		if(s[0]->mn->val < mn->val) mn = s[0]->mn;
		if(s[1]->mn->val < mn->val) mn = s[1]->mn;
	}
	void pushdown() { if(rev) s[0]->rev ^= 1, s[1]->rev ^= 1, swap(s[0], s[1]), rev = 0; }
} s[maxn], *st[maxn], *emt;

struct LinkCutTree {
	void rotate(Node *x) {
		Node *y = x->p, *z = y->p;
		int d = x->pos();
		y->sets(x->s[!d], d);
		if(y->isroot()) x->p = y->p;
		else z->sets(x, y->pos());
		x->sets(y, !d);
		y->update(emt);
	}
	
	void splay(Node *x) {
		int top = 0; st[++top] = x;
		for(Node *i = x; !i->isroot(); i = i->p) st[++top] = i->p;
		for(int i = top; i; --i) st[i]->pushdown();
		for(Node *y; !x->isroot(); rotate(x))
			if(!(y = x->p)->isroot()) rotate(x->pos() == y->pos() ? y : x);
		x->update(emt);
	}
	
	void access(Node *x) {
		for(Node *y = emt; x != emt; y = x, x = x->p) 
			splay(x), x->s[1] = y;
	}
	
	void makeroot(Node *x) 
	{ 
		access(x);
		 splay(x); x->rev ^= 1; }
	void link(Node *x, Node *y) { makeroot(x), x->p = y, splay(x); }
	void cut(Node *x, Node *y) { makeroot(x), access(y), splay(y); y->s[0] = x->p = emt; }
	
	Node *query(Node *x, Node *y) 
	{ 
		makeroot(x);
		access(y);
		splay(y); 
		return y->mn; 
	}
	Node *getroot(Node *x) {
		access(x), splay(x);
		Node *y = x; x->pushdown();
		while(y->s[0] != emt) y = y->s[0], y->pushdown();
		return y;
	}
} S;

#define lc tree[o].l, l, mid
#define rc tree[o].r, mid+1, r
struct Tree { int l, r, tot; } tree[25*maxn];
struct ChairmanTree {
	void insert(int &o, int l, int r, int p) {
		tree[++cnt] = tree[o]; o = cnt;
		++tree[o].tot;
		if(l == r) return;
		int mid = (l+r)>>1;
		if(p <= mid) insert(lc, p);
		else insert(rc, p);
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return tree[o].tot;
		if(r < L || R < l) return 0;
		int mid = (l+r)>>1;
		return query(lc, L, R)+query(rc, L, R);
	}
} T;

int main() {
	freopen("3514.in", "r", stdin);

	N = read(), M = read(), K = read(), Y = read();
	emt = new Node();
	for(int i = 1; i <= N+M; ++i) 
		s[i].p = s[i].s[0] = s[i].s[1] = emt, s[i].mn = s+i, s[i].val = inf;
	emt->val = inf, emt->mn = emt;
	
	Node *newpo = s+N;
	for(int i = 1; i <= M; ++i) {
		Node *u = s+read(), *v = s+read();
		
		int p = u == v ? i : 0;
		if(u != v) {
			if(S.getroot(u) == S.getroot(v)) {
				Node *t = S.query(u, v); p = t->val;
				S.cut(u, t), S.cut(v, t);
			}
			++newpo;
			newpo->val = i, newpo->mn = newpo;
			S.link(u, newpo), S.link(v, newpo);	
		}
		T.insert(root[i] = root[i-1], 0, M, p);
	}
	
	for(int i = 1, l, r; i <= K; ++i) {
		l = read(), r = read();
		if(Y) l ^= last, r ^= last;
		printf("%d\n", last = 
			N-(T.query(root[r], 0, M, 0, l-1) - T.query(root[l-1], 0, M, 0, l-1)));
	}
	return 0;
}
