#include <cstdio>
#include <vector>
#include <cstring>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
 
const int maxn = 2005;
vector <int> G[maxn];
int match[maxn], N, M;
bool used[maxn];
inline int read()
{
    char ch = getchar(); int sum = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
    return sum;
}
 
void AddEdge(int x, int y){ G[x].push_back(y); }
bool dfs(int v)
{
    used[v] = true;
    for(int i = 0; i < G[v].size(); ++i)
    {
        int u = G[v][i], w = match[u];
        if(w < 0 || !used[w] && dfs(w))
        { match[v] = u, match[u] = v; return true; }
    }
    return false;
}
 
int BinMatching()
{
     int ans = 0;
     mem(match, -1);
     for(int i = 1; i <= M; ++i)
     if(match[i] < 0) 
     {
     	mem(used, 0);
     	if(dfs(i)) ++ans;
     	else return ans;
     }
     return ans;
}
 
int main()
{
	freopen("data.in", "r", stdin);
    N = read(), M = read();
    for(int i = 1, u, v; i <= M; ++i)
        u = read()+1, v = read()+1, AddEdge(i, M+u), AddEdge(i, M+v);
    printf("%d\n", BinMatching());
    return 0;
}
