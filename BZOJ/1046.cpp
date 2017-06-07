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
const int maxn = 1e4+5;
const int inf = 1e9;
int N, M, top, MaxLen, a[maxn], q[maxn], len[maxn], ans[maxn];
bool less(int x, int y) { return x > y; }

void print(int x)
{
	int pre = -inf, count = x;
	for(int i = 1; i <= N && count; ++i)
	if(len[i] >= count && a[i] > pre)
	{
		printf("%d", a[i]);
		--count; pre = a[i];
		if(count) printf(" ");
	}
	printf("\n");
}

int main()
{
//	freopen("data.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = N; i >= 1; --i)
	{
		int pos = lower_bound(q+1, q+1+top, a[i], less)-q;
		q[pos] = a[i]; len[i] = pos;
		MaxLen = max(MaxLen, pos); top = max(top, pos);
	}
	M = read();
	for(int i = 1; i <= M; ++i)
	{
		int Li = read();
		if(Li <= MaxLen) print(Li);
		else printf("Impossible\n");
	}
	return 0;
}
