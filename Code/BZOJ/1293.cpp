#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6+5;
const int maxk = 105;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
int N, K, cnt, ans = maxn;
struct Data { int pos, color; } data[maxn];
int check[maxk];
bool cmp(Data x, Data y) { return x.pos < y.pos; }

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), K = read();
	for(int i = 1; i <= K; ++i)
	{
		int T = read();
		for(int i = 1; i <= T; ++i) data[++cnt].pos = read(), data[cnt].color = i;
	}
	sort(data+1, data+N+1, cmp);
	for(int left = 0, right = 0, tot = 0; right <= N; )
	if(tot < K || left > right) 
	{
		++right;
		tot += !check[data[right].color];
		++check[data[right].color]; 
	}
	else
	{
		ans = min(ans, data[right].pos-data[left].pos);
		--check[data[left].color];
		tot -= !check[data[left].color];
		++left;
	}
	printf("%d\n", ans);
}
