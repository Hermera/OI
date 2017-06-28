#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 5005, maxm = 50005;
int A, B, C, ans, tim, cnt, tot, head[maxn], part[maxn], vis[maxn];
bool cov[maxn];
struct Data { int next, to; } data[maxm];
struct Pos
{
	int x, y, z;
	void Build(int X, int Y, int Z)
	{
		x = X, y = Y, z = Z;
		if(B <= C && B <= A) swap(x, y);
		if(B <= C && B <= A) swap(x, z);
	}
} pos[maxn];

void add(int x, int y) { data[++tot] = (Data){head[x], y}; head[x] = tot; }

void init()
{
	cnt = 0;
	A = read(), B = read(), C = read();
	for(int i = 1; i <= A; ++i)
	for(int j = 1; j <= B; ++j)
	for(int k = 1; k <= C; ++k)
		if(read()) pos[++cnt].Build(i, j, k);
	
	if(B <= C && B <= A) swap(A, B);
	if(C <= A && C <= B) swap(A, C);
	ans = cnt;
}

bool Find(int x)
{
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(vis[e.to] != tim)
		{
			vis[e.to] = tim;
			if(!part[e.to] || Find(part[e.to]))
			{ part[e.to] = x; return true; }
		}
	}
	return false;
}

void dfs(int dep, int res)
{
	if(res >= ans) return;
	if(dep > A)
	{
		memset(head, 0, sizeof(int)*B+5); memset(part, 0, sizeof(int)*C+5); tot = 0;
		for(int i = 1; i <= cnt; ++i)
		if(!cov[pos[i].x]) add(pos[i].y, pos[i].z);
		for(int i = 1; i <= B; ++i)
		{
			++tim;
			if((res += Find(i)) >= ans) return;
		}
		ans = res;
	//	printf("ans = %d\n", ans);
		return;
	}
	cov[dep] = true; dfs(dep+1, res+1);
	
	cov[dep] = false; dfs(dep+1, res);
}

int main()
{
	freopen("data.in", "r", stdin);
	for(int T = read(); T; --T)
	{
		init();
		dfs(1, 0);
		printf("%d\n", ans);
	}
	return 0;
}
