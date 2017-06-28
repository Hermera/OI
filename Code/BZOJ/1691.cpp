#include <cstdio>
#include <algorithm>
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
const int maxn = 2e5+5;
int N, M, cnt, hash[maxn<<1], tree[maxn<<2];
long long ans;
struct Data
{ 
	int flesh, cost; 
	void init() { cost = read(); flesh = read(); hash[++cnt] = cost; }
	void update() { cost = lower_bound(hash+1, hash+cnt+1, cost) - hash; }
	bool operator <(const Data &b) const
		{ return flesh >= b.flesh; }
} cow[maxn], grass[maxn];

void pushup(int x) { tree[x] = tree[x<<1]+tree[x<<1|1]; }

void Modify(int o, int l, int r, int pos, int val)
{
	if(l == r) { tree[o] += val; return; }
	if(pos <= mid) Modify(lc, pos, val);
	else Modify(rc, pos, val);
	pushup(o);
}

int Query(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return tree[o];
	if(r < L || R < l) return 0;
	int ans = Query(lc, L, R)+Query(rc, L, R);
	pushup(o);
	return ans;
}

long long Find(int s, int t)
{
	int l = s, r = t, ans;
	while(l <= r)
		if(Query(1, 1, cnt, s, mid)) ans = mid, r = mid-1;
		else l = mid+1;
	Modify(1, 1, cnt, ans, -1);
	return hash[ans];
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i) cow[i].init();
	for(int i = 1; i <= M; ++i) grass[i].init();
	sort(hash+1, hash+N+1);
	for(int i = 1; i <= N; ++i) cow[i].update();
	for(int i = 1; i <= M; ++i) grass[i].update();
	
	sort(cow+1, cow+N+1);
	sort(grass+1, grass+M+1);
	
	for(int i = 1, j = 1; i <= N; ++i)
	{
		while(grass[j] < cow[i] && j <= M) 
			Modify(1, 1, cnt, grass[j].cost, 1), ++j;
		if(!Query(1, 1, cnt, cow[i].cost, cnt)) { printf("-1\n"); return 0; }
		ans += Find(cow[i].cost, cnt);
	}
	printf("%lld\n", ans);
	return 0;
}
