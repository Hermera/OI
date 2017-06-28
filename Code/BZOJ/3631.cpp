#include <cstdio>
#include <cstring>
#include <algorithm>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;

const int maxn = 300005;
int N, a[maxn];
inline int read()
{
    char ch = getchar(); int sum = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
    return sum;
}

struct Data { int next, to; };
int w[maxn], val[maxn], head[maxn], deep[maxn], size[maxn], son[maxn], top[maxn], fa[maxn], id[maxn], cnt, tim;
int tree[maxn<<2], lazy[maxn<<2];
Data data[maxn<<1];
void add(int x, int y){ data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
void init()
{
    mem(data), mem(head), mem(son), mem(lazy), mem(tree), cnt = 0, tim = 0; deep[1] = 0;
    for(int i = 1; i <= N; i++) w[i] = read();
    for(int i = 1, u, v; i < N; i++)
        u = read(), v = read(), add(u, v), add(v, u);
}
void MakeSize(int x, int f)
{
    size[x] = 1; fa[x] = f;
    for(int i = head[x]; i; i = data[i].next)
    if(data[i].to != f)
    {
        Data &e = data[i];
        deep[e.to] = deep[x]+1;
        MakeSize(e.to, x);
        size[x] += size[e.to];
        if(size[e.to] > size[son[x]]) son[x] = e.to;
    }
}
void MakeLink(int x, int tp)
{
    top[x] = tp; id[x] = ++tim;
    if(son[x]) MakeLink(son[x], tp);
    for(int i = head[x]; i; i = data[i].next)
    if(data[i].to != fa[x] && data[i].to != son[x])
        MakeLink(data[i].to, data[i].to);
}

void pushup(int x){ tree[x] = tree[x<<1]+tree[x<<1|1]; }
void pushdown(int x, int left, int right)
{
    if(!lazy[x]) return;
    int mid = (left+right)>>1;
    lazy[x<<1] += lazy[x]; lazy[x<<1|1] += lazy[x]; 
    tree[x<<1] += lazy[x]*(mid-left+1); tree[x<<1|1] += lazy[x]*(right-mid);
    lazy[x] = 0;
}
void Update(int node, int left, int right, int L, int R, int w)
{
    if(L <= left && right <= R) { lazy[node] += w; tree[node] += w*(right-left+1); return; }
    if(left > R || right < L) return;
    int mid = (left+right)>>1;
    pushdown(node, left, right);
    Update(node<<1, left, mid, L, R, w); Update(node<<1|1, mid+1, right, L, R, w);
    pushup(node);
}
int Query(int node, int left, int right, int v)
{
    if(left == right) return tree[node];
    int mid = (left+right)>>1;
    pushdown(node, left, right);
    if(v <= mid) return Query(node<<1, left, mid, v);
    else return Query(node<<1|1, mid+1, right, v);
    return 0;
}

void Modify(int u, int v, int w)
{
    while(top[u] != top[v])
    {
        if(deep[top[u]] < deep[top[v]]) swap(u, v);
        Update(1, 1, N, id[top[u]], id[u], w);
        u = fa[top[u]]; 
    }
    if(deep[u] > deep[v]) swap(u, v);
    Update(1, 1, N, id[u], id[v], w);
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
	MakeSize(1, 0); MakeLink(1, 1);
	for(int i = 2; i <= N; ++i) Modify(a[i-1], a[i], 1), Modify(a[i], a[i], -1);
	for(int i = 1; i <= N; ++i) printf("%d\n", Query(1, 1, N, id[i]));
    return 0;
}
