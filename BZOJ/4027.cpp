#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 2e6+5;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
struct Data { int next, to; } data[maxn<<1];
int N, M, cnt, C[maxn], F[maxn], G[maxn], head[maxn];

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }
bool cmp(int x, int y) { return G[x] < G[y]; }

void dfs(int x, int fa)
{
	vector <int> son;
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa)
		dfs(data[i].to, x), son.push_back(data[i].to), F[x] += F[data[i].to];
	G[x] += son.size();
	sort(son.begin(), son.end(), cmp);
	for(vector <int> ::iterator it = son.begin(); it != son.end(); ++it)
		if(G[x]+G[*it]-1 <= M) G[x] += G[*it]-1, ++F[x];
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) G[i] = read();
	for(int i = 1; i <= N; ++i)
		for(int j = 1, k = read(), u; j <= k; ++j) 
			u = read()+1, add(i, u), add(u, i);
	dfs(1, 0);
	printf("%d\n", F[1]);
	return 0;
}
