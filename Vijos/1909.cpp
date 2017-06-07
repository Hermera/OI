#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int maxn = 1e4+5;
vector <int> G[maxn], R[maxn];
int n, m, s, t, dis[maxn];
bool vis[maxn], can[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; ++i)
		scanf("%d%d", &x, &y), G[x].push_back(y), R[y].push_back(x);
	scanf("%d%d", &s, &t);
	
	queue <int> q;
	q.push(t), vis[t] = 1;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = 0; i < R[v].size(); ++i) 
			if(!vis[R[v][i]]) 
				vis[R[v][i]] = 1, q.push(R[v][i]);
	}
	
	for(int i = 1; i <= n; ++i) can[i] = 1;
	for(int i = 1; i <= n; ++i)
	for(int j = 0; j < G[i].size(); ++j)
		if(!vis[G[i][j]]) can[i] = 0;
	
	memset(dis, -1, sizeof(dis));
	if(can[s]) q.push(s), dis[s] = 0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i)
			if(dis[G[v][i]] < 0 && can[G[v][i]])
				dis[G[v][i]] = dis[v]+1, q.push(G[v][i]);
	}
	
	printf("%d\n", dis[t]);
	return 0;
}
	
