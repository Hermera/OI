#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

const int maxn = 2e4+5;
const int maxb = 150;
int N, M, S, ans, a[maxn], tree[maxn], hash[maxn], belong[maxn];
struct Block
{
	int s[maxn];
	void modify(int x, int v) { while(x <= N) s[x] += v, x += x&-x; }
	int query(int x)
	{
		int ans = 0;
		while(x) ans += s[x], x -= x&-x;
		return ans;
	}
} block[maxb];

bool judge(int x, int y, int on)
{
	if(!on) return x < y;
	else return y < x;
}

void Modify(int x, int v) { while(x <= N) tree[x] += v, x += x&-x; }
int Query(int x)
{
	int ans = 0;
	while(x) ans += tree[x], x -= x&-x;
	return ans;
}

int Ask(int L, int R, int val, int on)
{
	if(R < L) return 0;
	int sum = 0;
	if(belong[L] == belong[R])
		for(int i = L; i <= R; ++i) sum += judge(a[i], val, on);
	else
	{
		for(int i = L; i <= belong[L]*S; ++i) sum += judge(a[i], val, on);
		for(int i = (belong[R]-1)*S+1; i <= R; ++i) sum += judge(a[i], val, on);
	}
	for(int i = belong[L]+1; i < belong[R]; ++i)
		if(!on) sum += block[i].query(val-1);
		else sum += block[i].query(N)-block[i].query(val);
	return sum;
}

void Change(int L, int R)
{
	if(a[R] > a[L]) ++ans;
	if(a[R] < a[L]) --ans;
	ans += Ask(L+1, R-1, a[R], 0)-Ask(L+1, R-1, a[R], 1);
	ans += Ask(L+1, R-1, a[L], 1)-Ask(L+1, R-1, a[L], 0);
	block[belong[L]].modify(a[L], -1);
	block[belong[L]].modify(a[R], 1);
	block[belong[R]].modify(a[R], -1);
	block[belong[R]].modify(a[L], 1);
	swap(a[L], a[R]);
}

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);

	N = read(), S = sqrt(N);
	for(int i = 1; i <= N; ++i) a[i] = read(), hash[i] = a[i];
	sort(hash+1, hash+N+1);
	
	for(int i = 1; i <= N; ++i) belong[i] = (i-1)/S+1;
	for(int i = 1; i <= N; ++i) a[i] = lower_bound(hash+1, hash+N+1, a[i])-hash;
	for(int i = 1; i <= N; ++i)
		ans += Query(N)-Query(a[i]), Modify(a[i], 1);
	printf("%d\n", ans);
	
	M = read();
	for(int i = 1; i <= N; ++i) block[belong[i]].modify(a[i], 1);
	for(int i = 1; i <= M; ++i)
	{
		int l = read(), r = read();
		if(l > r) swap(l, r);
		Change(l, r);
		printf("%d\n", ans);
	}
	
	return 0;
}
