#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <queue>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
typedef long long ll;

const int maxn = 25, maxp = maxn*maxn*maxn*2, inf = 1e9;
int N, M, S, T;
struct Edge { int to, cap, rev; };
vector <Edge> G[maxp];
int level[maxp], iter[maxp];

void add(int from, int to, int cap) {
	G[from].push_back((Edge){to, cap, G[to].size()});
	G[to].push_back((Edge){from, 0, G[from].size()-1});
}

bool bfs(int s, int t) {
	mset(iter, 0), mset(level, -1);
	queue <int> q;
	level[s] = 0; q.push(s);
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); i++) {
			Edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0)
				level[e.to] = level[v] + 1, q.push(e.to);
		}
	}
	return level[t] != -1;
}

int dfs(int v, int t, int f) {
	if(v == t || f == 0) return f;
	for(int &i = iter[v]; i < G[v].size(); i++) {
		Edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v]) {
			int d = dfs(e.to, t, min(e.cap, f));
			if(d > 0)
			{ e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}

int MaxFlow(int s, int t) {
	int flow = 0;
	while(bfs(s, t))
		for(int f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

const int fx[4] = { 1, -1, 0, 0 };
const int fy[4] = { 0, 0, 1, -1 };
struct Point { int x, y; }; 
bool check[maxn][maxn];
int people, dis[maxn][maxn][maxn][maxn];
vector <Point> door;
char s[maxn][maxn];

bool Get(Point u, int a[maxn][maxn]) {
	queue <Point> q;
	bool flag = false;
	a[u.x][u.y] = 0;
	q.push(u);
	mset(check, 0);
	check[u.x][u.y] = true;
	while(!q.empty()) {
		Point v = q.front(); q.pop();
		for(int d = 0; d < 4; ++d) {
			int nx = v.x+fx[d], ny = v.y+fy[d];
			if(!nx || !ny || nx > N || ny > M || s[nx][ny] == 'X' || check[nx][ny]) continue;
			a[nx][ny] = a[v.x][v.y]+1;
			check[nx][ny] = true;
			
			if(s[nx][ny] == 'D') flag = true;
			else q.push((Point){ nx, ny });
		}
	}
	return flag;
}	

bool Getdis() {
	mset(dis, 63);
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j) {
		if(s[i][j] == '.' && !Get((Point){ i, j }, dis[i][j])) return false;
		if(s[i][j] == 'D') door.push_back((Point){ i, j });
	}
	return true;
}

void MakeGraph(int x) {
	for(int i = S; i <= T; ++i) G[i].clear();
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j) if(s[i][j] == '.') {
		add(S, (i-1)*M+j, 1);
		for(int k = 0; k < door.size(); ++k) {
			Point &d = door[k];
			if(dis[i][j][d.x][d.y] <= x)
				for(int t = dis[i][j][d.x][d.y]; t <= x; ++t) 
					add((i-1)*M+j, (k+1)*N*M+t, 1);
		}
	}
	for(int k = 0; k < door.size(); ++k) {
		Point &d = door[k];
		for(int t = 1; t <= x; ++t) 
			add((k+1)*N*M+t, T, 1);
	}
}	

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		scanf("%s", s[i]+1);
		for(int j = 1; j <= M; ++j) 
			if(s[i][j] == '.') ++people;
	}
	
	if(!Getdis()) printf("impossible\n");
	else {
		S = 0, T = (door.size()+1)*N*M+2;
		int l = 0, r = N*M, ans;
		while(l <= r) {
			int mid = (l+r)>>1;
			MakeGraph(mid);
			if(MaxFlow(S, T) == people) ans = mid, r = mid-1;
			else l = mid+1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
