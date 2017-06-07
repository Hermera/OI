#include <cstdio>
#include <algorithm>
#include <queue>
#define bin(x) (1<<x)
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum*t;
}
const int maxn = 5e5+5, Size = 19;
int N, K, L, R, A[maxn], Log[maxn], ST[maxn][Size];

/*void pre()
{
	Log[0]=-1;for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)mx[i][0]=i;
	for(int i=n;i;i--)
		for(int j=1;j<=18;j++)
			if(i+bin[j]-1<=n)
			{
				int t1=mx[i][j-1],t2=mx[i+bin[j-1]][j-1];
				mx[i][j]=a[t1]>a[t2]?t1:t2;
			}
			else break;
}*/

void init()
{
	N = read(), K = read(), L = read(), R = read();
	for(int i = 1; i <= N; ++i) A[i] = A[i-1]+read();
	Log[0] = -1;
	for(int i = 1; i <= N; ++i) Log[i] = Log[i>>1]+1;
	for(int i = 1; i <= N; ++i) ST[i][0] = i;
	
	for(int j = 1; j < Size; ++j)
	for(int i = 1; i <= N; ++i)
		if(i+bin(j)-1 <= N)
			ST[i][j] = A[ST[i][j-1]] > A[ST[i+bin(j-1)][j-1]] ? ST[i][j-1] : ST[i+bin(j-1)][j-1];
		else break;
}

int Query(int L, int R)
{
	if(L == R) return L;
	int t = Log[R-L+1], t1 = ST[L][t], t2 = ST[R-bin(t)+1][t];
	return A[t1] > A[t2] ? t1 : t2; 
}

struct Node
{
	int i, l, r, mid; ll val;
	bool operator <(const Node &b) const
		{ return val < b.val; }
};
ll solve()
{
	ll ans = 0, tot = 0;
	priority_queue <Node, vector<Node> >q;
	for(int i = 1; i <= N; ++i)
	if(i+L-1 <= N)
	{
		int l = i+L-1, r = min(N, i+R-1);
		q.push((Node){ i, l, r, Query(l, r), A[Query(l, r)]-A[i-1] });
	}
	while(tot < K)
	{
		Node v = q.top(); q.pop();
		ans += v.val; ++tot;
		if(v.mid > v.l)
			q.push((Node){v.i, v.l, v.mid-1, Query(v.l, v.mid-1), A[Query(v.l, v.mid-1)]-A[v.i]});
		if(v.mid < v.r)
			q.push((Node){v.i, v.mid+1, v.r, Query(v.mid+1, v.r), A[Query(v.mid+1, v.r)]-A[v.i]});
	}
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	init();
	printf("%lld\n", solve());
	return 0;
}
