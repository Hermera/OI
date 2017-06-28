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
const int Mod = 2147483648;
typedef long long ll;
struct Tree { int x, y, yh; } tree[maxn];
ll N, M, W, K, ans, up[maxn], down[maxn], Y[maxn], bit[maxn], vis[maxn], C[maxn][15];

void GetComb()
{
	C[1][1] = C[1][0] = 1;
	for(int i = 2; i <= W; ++i)
	for(int j = 0; j <= min((ll)i, K); ++j)
		if(j) C[i][j] = (C[i-1][j]+C[i-1][j-1])%Mod;
		else C[i][j] = 1;
}

void add(int x, ll v) { while(x <= W) bit[x] += v, x += x&-x; }
ll query(int x)
{
	ll ans = 0;
	while(x) ans += bit[x], x -= x&-x;
	return ans;
}

bool cmp(Tree a, Tree b) { return a.x != b.x ? a.x < b.x : a.y < b.y; }

int main()
{
	freopen("data.in", "r", stdin);
	N = read()+1, M = read()+1, W = read();
	for(int i = 1; i <= W; ++i) tree[i].x = read()+1, tree[i].y = read()+1, Y[i] = tree[i].y;
	K = read(); GetComb();
	sort(Y+1, Y+W+1);
	for(int i = 1, fy; i <= W; ++i) 
		fy = lower_bound(Y+1, Y+W+1, tree[i].y)-Y, ++down[fy], tree[i].yh = fy;
	sort(tree+1, tree+W+1, cmp);
	for(int i = 1; i <= W; )
	{
		int l = i, r = i;
		while(tree[r].x == tree[r+1].x && r < W) ++r;
		for(int j = l+1; j <= r; ++j)
			ans += (query(tree[j].yh-1)-query(tree[j-1].yh))%Mod*C[j-l][K]*C[r-j+1][K]%Mod, ans %= Mod;
		for(int j = l; j <= r; ++j)
		{
			++up[tree[j].yh], --down[tree[j].yh];
			ll temp = C[up[tree[j].yh]][K]*C[down[tree[j].yh]][K]%Mod;
			add(tree[j].yh, temp-vis[tree[j].yh]);
			vis[tree[j].yh] = temp;
		}
		i = r+1;
	}
	printf("%lld\n", ans%Mod);
	return 0;
}
