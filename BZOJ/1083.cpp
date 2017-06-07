#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 305;
const int maxm = 305*305;
int N, M, fa[maxn];
struct Data { int u, v, w; } data[maxm];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
bool Union(int x, int y)
{
	x = Find(x); y = Find(y);
	if(x == y) return false;
	fa[x] = y; return true;
}
bool cmp(Data a, Data b) { return a.w < b.w; }
int main()
{
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = 1, u, v, w; i <= M; ++i)
		u = read(), v = read(), w = read(), data[i] = (Data){u, v, w};
	sort(data+1, data+M+1, cmp);
	for(int i = 1, tot = 0; i <= M; ++i)
	if(Union(data[i].u, data[i].v))
		if(++tot == N-1)
			{ printf("%d %d\n", N-1, data[i].w); return 0; }
	return 0;
}
