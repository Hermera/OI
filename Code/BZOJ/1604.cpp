#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
const ll inf = 1e16;
int N, C, Max, tot, head = 1, sum[maxn], fa[maxn];
struct Cow
{
	ll x, y;
	bool operator <(const Cow &b) const
	{ return x != b.x ? x < b.x : y < b.y; }
} cow[maxn];
set <Cow> S;

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void Union(int x, int y) { x = Find(x), y = Find(y), fa[x] = y; }

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), C = read();
	for(int i = 1, x, y; i <= N; ++i)
		x = read(), y = read(), cow[i] = (Cow){x+y, x-y}, fa[i] = i;
	
	sort(cow+1, cow+1+N);
	S.insert((Cow){-inf, 0}), S.insert((Cow){inf, 0});
	for(int i = 1; i <= N; ++i)
	{
		while(cow[i].x-cow[head].x > C)
			S.erase(S.lower_bound((Cow){cow[head].y, head})), ++head;
			
		ll y = cow[i].y;
		set <Cow> ::iterator it = S.lower_bound((Cow){ cow[i].y, i });
		Cow R = *it, L = *(--it);
		if(R.x-y <= C) Union(R.y, i);
		if(y-L.x <= C) Union(L.y, i);
		
		S.insert((Cow){cow[i].y, i});
	}
	
	for(int i = 1; i <= N; ++i) ++sum[Find(i)];
	for(int i = 1; i <= N; ++i) Max = max(Max, sum[i]), tot += Find(i)==i;
	printf("%d %d\n", tot, Max);
	return 0;
}
