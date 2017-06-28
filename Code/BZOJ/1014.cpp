#include <cstdio>
#include <cstring>
#include <algorithm>
#define half (x->s[0]->siz+1)
#define idx(x) (x-'a'+1)
#define out(x, a, b) ((x) < (a) || (x) > (b))
#define ins(x, a, b) ((a) <= (x) && (x) <= (b))
using namespace std;
typedef unsigned long long ull;
int read() {
	char ch = getchar(); int x = 0;
	while(out(ch, '0', '9')) ch = getchar();
	while(ins(ch, '0', '9')) x = x*10+ch-'0', ch = getchar();
	return x;
}

char get() {
	char ch = getchar();
	while(out(ch, 'a', 'z') && out(ch, 'A', 'Z')) ch = getchar();
	return ch;
}

const int maxn = 3e5+5;
int n, m, t, cnt;
char str[maxn], op, cr;
ull pow[maxn];
struct node {
	int val, siz;
	ull sum;
	node *p, *s[2];
	node() {}
	node(int);
	void sets(node *x, int d) { (s[d] = x)->p = this; }
	bool pos() { return this == p->s[1]; }
	void update() { 
		siz = s[0]->siz + s[1]->siz + 1; 
		sum = s[0]->sum*pow[s[1]->siz+1] + val*pow[s[1]->siz] + s[1]->sum;
	}
} *emt = new node(0), *root = emt, gen[maxn];

node::node(int v = 0) {
	val = v;
	p = s[0] = s[1] = emt;
	sum = siz = 0;
}

struct splaytree {	
	void rotate(node *x) {
		node *y = x->p, *z = y->p;
		int d = x->pos();
		y->sets(x->s[!d], d);
		if(z == emt) x->p = y->p;
		else z->sets(x, y->pos());
		y->update();
		x->sets(y, !d);
	}
	
	void splay(node *x, node *g = emt) {
		for(node *y; x->p != g; rotate(x))
			if((y = x->p)->p != g) rotate(x->pos() == y->pos() ? y : x);
		x->update();
		if(g == emt) root = x;
	}
	
	void insert(int k, char ch, node *&x = root, node *f = emt) {
		if(x == emt) {
			x = &gen[++cnt], *x = node(idx(ch)), x->p = f;
			x->update(), splay(x);
			return;
		}
		if(half <= k) insert(k-half, ch, x->s[1], x);
		else insert(k, ch, x->s[0], x);
	}
	
	node *find_kth(int k, node *x = root) {
		if(k == half) return x;
		if(k < half) return find_kth(k, x->s[0]);
		else return find_kth(k-half, x->s[1]);
	}
	
	void modify(int k, char ch) {
		node *x = find_kth(k);
		x->val = idx(ch);
		splay(x);
	}
	
	ull getval(int x, int y) {
		node *l = find_kth(x-1), *r = find_kth(y+1);
		splay(r);
		splay(l, root);
		return root->s[0]->s[1]->sum;
	}
} s;

int solve(int x, int y) {
	int l = 1, r = min(n-x+1, n-y+1)-1, ans = 0;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(s.getval(x, x+mid-1) == s.getval(y, y+mid-1))
			ans = mid, l = mid+1;
		else r = mid-1;
	}
	return ans;
}

int main() {
	pow[0] = 1;
	scanf("%s", str), m = read(), t = strlen(str)+m, emt->p = emt;
	for(int i = 1; i <= t; ++i) pow[i] = pow[i-1]*29;
	s.insert(n++, 'a'-1);
	for(int i = 0; str[i]; ++i) s.insert(n++, str[i]);
	s.insert(n++, 'a'-1);
	for(int i = 1, x; i <= m; ++i) {
		op = get();
		if(op == 'Q') printf("%d\n", solve(read()+1, read()+1));
		else {
			x = read()+1, cr = get();
			if(op == 'R') s.modify(x, cr);
			else s.insert(x, cr), ++n;
		}
	}
	return 0;
}
