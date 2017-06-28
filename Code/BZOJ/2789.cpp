#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
int N, r[maxn];
char a[maxn], b[maxn];
queue <int> q[26];
ll tree[maxn], ans;

void Modify(int x, int v) { while(x <= N) tree[x] += v, x += x&-x; }
ll Query(int x)
{
	ll ans = 0;
	while(x) ans += tree[x], x -= x&-x;
	return ans;
}

int main()
{
	scanf("%d%s%s", &N, a+1, b+1);
	for(int i = 1; i <= N; ++i)	q[a[i]-'A'].push(i);
	for(int i = 1; i <= N; ++i)	
		r[i] = q[b[i]-'A'].front(), q[b[i]-'A'].pop();
		
	for(int i = 1; i <= N; ++i)
		ans += Query(N)-Query(r[i]), Modify(r[i], 1);
	
	printf("%lld\n", ans);
	return 0;
}
