#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e6+5;
int N, M, ans, cnt, size[maxn], c[maxn], fir[maxn], head[maxn];
struct Data { int next, to; } data[maxn];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }

void Union(int a, int b)
{
	if(a == b) return;
	if(size[fir[a]] > size[fir[b]]) swap(fir[a], fir[b]);
	a = fir[a], b = fir[b];
	if(size[a] == 0) return;
	size[b] += size[a]; size[a] = 0;
	for(int i = head[a]; i; i = data[i].next)
	{
		if(c[data[i].to-1] == b) --ans;
		if(c[data[i].to+1] == b) --ans;
	}
	for(int i = head[a]; ; i = data[i].next)
	{
		c[data[i].to] = b;
		if(!data[i].next) { data[i].next = head[b]; break; }
	}
	head[b] = head[a]; head[a] = 0;
	
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= N; ++i)
	{
		c[i] = read(); add(c[i], i); fir[c[i]] = c[i]; ++size[c[i]];
		if(c[i] != c[i-1]) ++ans;
	}
	for(int i = 1; i <= M; ++i)
	{
		int op = read(), a, b;
		if(op == 2) printf("%d\n", ans);
		else a = read(), b = read(), Union(a, b);
	}
	return 0;
}
