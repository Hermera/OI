#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5+5;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

struct Tree
{
	int size;
	Tree *son[2], *par;
	Tree(Tree *par = 0, Tree *null = 0): par(par) { son[0] = son[1] = null; }
	inline void sets(Tree *x, int d) { (son[d] = x)->par = this; }
	inline void update() { size = son[0]->size + son[1]->size + 1; }
	inline bool iroot() { return this != par->son[0] && this != par->son[1]; }
	inline bool pos() { return this == par->son[1]; }
} s[maxn];
int N, M;

inline void rotate(Tree *x)
{
	int d = x->pos();
	Tree *y = x->par, *z = y->par;
	y->sets(x->son[!d], d);
	if(y->iroot()) x->par = y->par;
	else z->sets(x, y->pos());
	x->sets(y, !d);
	y->update();
}

inline void splay(Tree *x)
{
	for(Tree *y; !x->iroot(); rotate(x))
		if(!(y = x->par)->iroot()) rotate(x->pos() == y->pos() ? y : x);
	x->update();
}

inline void access(Tree *x)
{
	for(Tree *y = s; x != s; y = x, x = x->par)
		splay(x), x->son[1] = y, x->update();
}

inline void link(Tree *x, Tree *y) { x->par = y; }

inline void cut(Tree *x)
{
	splay(x);
	x->son[0]->par = x->par, x->son[0] = s;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read();
	for(int i = 1, k; i <= N; ++i)
		k = read(), s[i] = Tree(s+min(i+k, N+1), s), (s+i)->size = 1;	
	s[N+1] = *s = Tree(s, s);
	(s+N+1)->size = 1, s->size = 0;
	
	for(M = read(); M; --M)
	{
		int op = read(), y = read()+1, k;
		if(op == 1) access(s+y), splay(s+y), printf("%d\n", (s+y)->son[0]->size);
		else k = read(), cut(s+y), link(s+y, s+min(y+k, N+1));
	}
	
	return 0;
}
