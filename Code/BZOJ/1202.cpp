#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1100;
int fa[maxn], dis[maxn], N, M;

int Find(int x)
{
	if(fa[x] == x) return x;
	int fx = Find(fa[x]);
	dis[x] += dis[fa[x]], fa[x] = fx;
	return fx;
}

bool Union(int x, int y, int z)
{
	int fx = Find(x), fy = Find(y);
	if(fx != fy) { dis[fy] = z+dis[x]-dis[y], fa[fy] = fx; return true; }
	else return dis[y]-dis[x] == z;
}

int main()
{
//	freopen("data.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	int T; scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d", &N, &M);
		memset(dis, 0, sizeof(dis));
		bool flag = true;
		for(int i = 0; i <= N; ++i) fa[i] = i;
		for(int i = 1; i <= M; ++i)
		{
			int s, t, z;
			scanf("%d%d%d", &s, &t, &z); --s;
			if(!Union(s, t, z)) flag = false; 
		}
		printf("%s\n", flag ? "true" : "false");
	}
	return 0;
}
