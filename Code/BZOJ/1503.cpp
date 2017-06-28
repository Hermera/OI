#include <cstdio>
#define mid ((l+r)>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 3e5+5, U = 2e5, D = -1e5;
int N, K, C, now, sum, tree[maxn<<2];
bool lazy[maxn<<2];
char s[5];

void pushup(int x) { tree[x] = tree[x<<1]+tree[x<<1|1]; }
void pushdown(int x)
{
	if(!lazy[x]) return;
	lazy[x] = false;
	tree[x<<1] = tree[x<<1|1] = 0;
	lazy[x<<1] = lazy[x<<1|1] = true;
}

void Modify(int o, int l, int r, int pos)
{
	if(l == r) { ++tree[o]; return; }
	pushdown(o);
	if(pos <= mid) Modify(lc, pos);
	else Modify(rc, pos);
	pushup(o);
}

void Update(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) { tree[o] = 0, lazy[o] = true; return; }
	if(r < L || R < l) return;
	pushdown(o);
	Update(lc, L, R), Update(rc, L, R);
	pushup(o);
}

int Query(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return tree[o];
	if(r < L || R < l) return 0;
	pushdown(o);
	int ans = Query(lc, L, R)+Query(rc, L, R);
	pushup(o);
	return ans;
}

int Find(int o, int l, int r, int k)
{
	if(l == r) return l;
	pushdown(o);
	int ans = k<=tree[o<<1] ? Find(lc, k) : Find(rc, k-tree[o<<1]);
	pushup(o);
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);

	N = read(), K = read();
	for(int i = 1; i <= N; ++i)
	{
		scanf("%s", s);
		if(*s == 'I') 
		{
			int val = read();
			if(val < K) continue;
			else ++now, ++sum, Modify(1, D, U, val-C);
		}
		if(*s == 'A' || *s == 'S')
		{
			C += (*s=='A'?1:-1)*read();
			if(K-C-1 > D) now -= Query(1, D, U, D, K-C-1), Update(1, D, U, D, K-C-1);
		}
		if(*s == 'F')
		{
			int node = read();
			if(node > now) printf("-1\n");
			else printf("%d\n", Find(1, D, U, now-node+1)+C);
		}
	}
	printf("%d\n", sum-now);
	return 0;
}
