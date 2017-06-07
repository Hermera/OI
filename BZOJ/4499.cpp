#include <cstdio>
#define mid ((left+right)>>1)
#define lc o<<1, left, mid
#define rc o<<1|1, mid+1, right
using namespace std;
typedef long long ll;
const int Mod = 1e9+7;
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
	ll k, b; bool flag;
	friend Tree operator +(const Tree &a, const Tree &b)
	{
		Tree ret;
		if(!a.flag) return b;
		if(!b.flag) return a;
		ret.k = a.k*b.k%Mod;
		ret.b = (a.b*b.k+b.b)%Mod;
		ret.flag = true;
		return ret;
	}
} tree[maxn<<2];
int N, M;
char s[5];

void Build(int o, int left, int right)
{
	if(left == right) { tree[o].k = read(), tree[o].b = read(), tree[o].flag = true; return; }
	Build(lc), Build(rc);
	tree[o] = tree[o<<1]+tree[o<<1|1];
}

void Modify(int o, int left, int right, int pos, int k, int b)
{
	if(left == right) { tree[o] = (Tree){k, b, 1}; return; }
	if(pos <= mid) Modify(lc, pos, k, b);
	else Modify(rc, pos, k, b);
	tree[o] = tree[o<<1]+tree[o<<1|1];
}

Tree Query(int o, int left, int right, int L, int R)
{
	if(L <= left && right <= R) return tree[o];
	if(R < left || right < L) return (Tree){0, 0, false};
	return Query(lc, L, R)+Query(rc, L, R);
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	Build(1, 1, N);
	
	for(int i = 1; i <= M; ++i)
	{
		scanf("%s", s);
		int a = read(), b = read(), c = read();
		if(*s == 'M') Modify(1, 1, N, a, b, c);
		else
		{
			Tree ans = Query(1, 1, N, a, b);
			printf("%lld\n", (ans.k*c+ans.b)%Mod);
		}
	}
	return 0;
}
