#include <cstdio>
#include <algorithm>
#define mid ((l+r)>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum*t;
}
const int maxn = 2e5+5;
int N, M;
ll K, D;
struct Tree 
{ 
	ll sum, lx, rx, mx; 
	void init() { sum = lx = rx = mx = -K; }
	void modify(ll v) { sum += v, lx += v, rx += v, mx += v; }
	ll getmax() { return max(lx, max(mx, rx)); }
} tree[maxn<<2];

void pushup(int o)
{
	tree[o].sum = tree[o<<1].sum+tree[o<<1|1].sum;
	tree[o].lx = max(tree[o<<1].lx, tree[o<<1].sum+tree[o<<1|1].lx);
	tree[o].rx = max(tree[o<<1|1].rx, tree[o<<1|1].sum+tree[o<<1].rx);
	tree[o].mx = max(tree[o<<1].rx+tree[o<<1|1].lx, max(tree[o<<1].mx, tree[o<<1|1].mx));
}

void Build(int o, int l, int r)
{
	if(l == r) { tree[o].init(); return; }
	Build(lc); Build(rc);
	pushup(o);
}

void Update(int o, int l, int r, int p, ll v)
{
	if(l == r) { tree[o].modify(v); return; }
	if(p <= mid) Update(lc, p, v);
	else Update(rc, p, v);
	pushup(o);
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read(), K = read(), D = read();
	N -= D;
	Build(1, 1, N);
	for(int i = 1; i <= M; ++i)
	{
		int ri = read(), xi = read();
		Update(1, 1, N, ri, xi);
		printf("%s\n", tree[1].getmax() <= D*K ? "TAK" : "NIE");
	}
	return 0;
}
