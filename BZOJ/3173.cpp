#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;

struct Node
{
	int size, key;
	Node *s[2], *p;
	Node(Node *emt = 0, Node *p = 0, int key = 0): p(p), key(key) 
	{ s[0] = s[1] = emt; size = 0; }
	void sets(Node *x, int d) { (s[d] = x)->p = this; }
	void update() { size = s[0]->size+s[1]->size+1; }
	int pos() { return p->s[1] == this; } 
} *emt = new Node(emt), *root = emt;

void rotate(Node *x)
{
	Node *y = x->p, *f = y->p; int d = x->pos();
	y->sets(x->s[!d], d);
	if(f != emt) f->sets(x, y->pos());
	else x->p = emt;
	x->sets(y, !d); y->update();
}

void splay(Node *x)
{
	for(Node *y; (y = x->p) != emt; rotate(x))
		if(y->p != emt) rotate(x->pos() == y->pos() ? y : x);
	root = x;
	x->update();
}

void insert(int k, int v, Node *&x = root, Node *f = emt)
{
	if(x == emt) 
	{ 
		x = new Node(emt, f, v);
		 x->update();
		  splay(x); 
		  return; }
	if(k <= x->s[0]->size) insert(k, v, x->s[0], x);
	else insert(k - x->s[0]->size - 1, v, x->s[1], x);
}

int N, len, cnt, ans[maxn], a[maxn], q[maxn];
void print(Node *x = root)
{
	if(x == emt) return;
	print(x->s[0]);
	a[++cnt] = x->key;
	print(x->s[1]);
}

int main()
{
	freopen("data.in", "r", stdin);	
	
	N = read();
	for(int i = 1; i <= N; ++i) insert(read(), i);
	print();
	
	for(int i = 1; i <= N; ++i)
	{
		int dis = lower_bound(q+1, q+len+1, a[i]) - q;
		ans[a[i]] = dis;
		q[dis] = !q[dis] ? a[i] : min(a[i], q[dis]);
		len = max(len, dis);
	}
	
	for(int i = 1; i <= N; ++i) printf("%d\n", ans[i] = max(ans[i], ans[i-1]));
	
	return 0;
}
