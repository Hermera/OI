#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 505;
const int maxm = 5005;
const int inf = 1e9;
int N, M, S, T, fa[maxn];
struct Load { int u, v, w; } data[maxm];

inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

bool cmp(Load a, Load b) { return a.w < b.w; }
int Find(int x){ return fa[x] == x ? x : fa[x] = Find(fa[x]); }
bool Union(int x, int y)
{
	x = Find(x), y = Find(y);
	if(x == y) return false;
	fa[x] = y; return true;
}
int gcd(int x, int y) { if(x < y) swap(x, y); return y == 0 ? x : gcd(y, x%y); } 
int main()
{
	N = read(), M = read();
	for(int i = 1, u, v, w; i <= M; ++i)
		u = read(), v = read(), w = read(), data[i] = (Load){u, v, w};
	sort(data+1, data+M+1, cmp);
	S = read(), T = read();
	if(S == T) { printf("1\n"); return 0; }
	int son = inf, mother = 1;
	for(int start = 1, end = N; start <= M; )
	{
		for(int j = 1; j <= N; ++j) fa[j] = j;
		for(int j = start; j <= M; ++j)
		if(Union(data[j].u, data[j].v))
			if(Find(S) == Find(T)) { end = j; break;}
			
		for(int j = 1; j <= N; ++j) fa[j] = j;
		for(int j = end; j >= start; --j)
		if(Union(data[j].u, data[j].v))
			if(Find(S) == Find(T)) { start = j; break;}
		
		if(Find(S) == Find(T))
		{
			if((double)data[end].w*1.0/(double)data[start].w < (double)son*1.0/(double)mother)
				son = data[end].w, mother = data[start].w;
			++start; end = N;
		}
		else break;
	}
	if(son == inf) printf("IMPOSSIBLE\n");
	else 
	{
		int g = gcd(son, mother);
		if(g == mother) printf("%d\n", son/g);
		else printf("%d/%d\n", son/g, mother/g);
	}
	return 0;
}

