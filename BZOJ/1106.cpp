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
int N, sum, a[maxn], tree[maxn], check[maxn];

void add(int x, int v) { while(x <= (N<<1)) tree[x] += v, x += x&-x; }
int query(int x)
{
	int ans = 0;
	while(x) ans += tree[x], x -= x&-x;
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read();
	for(int i = 1; i <= (N<<1); ++i) a[i] = read();
	for(int i = 1; i <= (N<<1); ++i)
	if(!check[a[i]]) check[a[i]] = i, add(i, 1);
	else sum += query(i)-query(check[a[i]]), add(check[a[i]], -1);
	
	printf("%d\n", sum);
}
