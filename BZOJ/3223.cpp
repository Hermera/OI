#include <cstdio>
#include <algorithm>
#define half (u->s[0]->size+1)
#define mid ((l+r)>>1)
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
int N, M, cnt;

struct Node
{
	int size, key; bool rev;
	Node *p, *s[2];
	Node(Node *p = 0, int key = 0, Node *emt = 0) : p(p), key(key) 
		{ s[0] = s[1] = emt, size = rev = 0; }
	void sets(Node *x, int d) { (s[d] = x)->p = this; }
	void update() { size = s[0]->size+s[1]->size+1; }
	bool pos() { return this == p->s[1]; }
	void pushdown() { if(rev) s[0]->rev ^= 1, s[1]->rev ^= 1, swap(s[0], s[1]), rev = 0; }
} *emt = new Node(), *root = emt, *st[maxn], gen[maxn];

void Build(Node *&x, Node *fa, int l, int r)
{
	if(l > r) return;
	x = &gen[++cnt], *x = Node(fa, mid, emt);
	x->size = 1;
	Build(x->s[0], x, l, mid-1);
	Build(x->s[1], x, mid+1, r);
	x->update();
}

void rotate(Node *x)
{
	Node *y = x->p, *z = y->p; int d = x->pos();
	y->sets(x->s[!d], d);
	if(z == emt) x->p = y->p;
	else z->sets(x, y->pos());
	y->update();
	x->sets(y, !d);
}

void splay(Node *x, Node *g = emt)
{
	int top = 0; st[++top] = x;
	for(Node *i = x; i->p != g; i = i->p) 
		st[++top] = i->p;
	for(int i = top; i; --i) st[i]->pushdown();
	for(Node *y; (y = x->p) != g; rotate(x))
		if(y->p != g) rotate(x->pos() == y->pos() ? y : x);
	x->update();
	if(g == emt) root = x;
}

Node *find_kth(int k, Node *u = root)
{
	u->pushdown();
	if(k == half) return u;
	if(k < half) return find_kth(k, u->s[0]);
	return find_kth(k-half, u->s[1]);
}

void rever(int l, int r)
{
	Node *R = find_kth(r+1), *L = find_kth(l-1);
	splay(R);
	splay(L, root);
	root->s[0]->s[1]->rev ^= 1;
}

void print(Node *x = root)
{
	if(x == emt) return;
	x->pushdown();
	print(x->s[0]);
	if(x->key && x->key <= N) printf("%d ", x->key);
	print(x->s[1]);
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	Build(root, emt, 0, N+1);
	while(M--)
	{
		int l = read()+1, r = read()+1;
		if(l > r) swap(l, r);
		rever(l, r);
	}
	print();
	printf("\n");
	return 0;
}
