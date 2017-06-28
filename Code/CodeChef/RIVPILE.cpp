#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 255, maxm = maxn*maxn*maxn;
const int inf = 1e9;
struct Point { double x, y; } p[maxn];
struct Cir {
	double r, v;
	void init() { r = read(), v = read(); }
	bool operator <(const Cir &b) const { return r != b.r ? r < b.r : v < b.v; }
} c[maxn];
int N, M, W, S, T, head[maxm], cnt;
struct Data { int next, to; ll w; } data[maxm];

void init() {
	N = read(), M = read(), W = read();
	for(int i = 1; i <= N; ++i) p[i].x = read(), p[i].y = read();
	for(int i = 1; i <= M; ++i) c[i].init();
	sort(c+1, c+1+M);
	
	int tot = 0;
	for(int i = 1; i <= M; ++i) {
		while(tot && c[tot].v >= c[i].v) --tot;
		c[++tot] = c[i];
	}
	M = tot;
}

double away(Point a, Point b) { return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); }
int Node(int x, int y) { return (x-1)*M+y; }
void add(int x, int y, ll w) { 
	data[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
}

bool isedge(int a, int b, int x, int y) {
	for(int i = head[Node(a, b)]; i; i = data[i].next)
		if(data[i].to == Node(x, y)) return true;
	return false;
}

void BuildGraph() {
	S = 0, T = Node(N, M)+1;
	for(int i = S; i <= T; ++i) head[i] = 0;
	cnt = 0;
	
	for(register int i = 1; i <= N; ++i) 
	for(register int j = 1; j <= M; ++j) 
		if(c[j].r >= p[i].y) {
			add(S, Node(i, j), c[j].v);
			break;
		}
	
	for(register int i = 1; i <= N; ++i) 
	for(register int j = 1; j <= M; ++j) 
		if(c[j].r >= W-p[i].y) add(Node(i, j), T, 0);

	for(register int i = 1; i <= N; ++i)
	for(register int j = 1; j <= N; ++j) if(i != j) {
		int t = M;
		for(register int k = 1; k <= M; ++k) if(c[k].r+c[t].r >= away(p[i], p[j])){
			while(c[k].r+c[t-1].r >= away(p[i], p[j]) && t > 1) --t;
			add(Node(i, k), Node(j, t), c[t].v);
		}
	}
	
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j < M; ++j)
		add(Node(i, j), Node(i, j+1), c[j+1].v-c[j].v);
}

int dis[maxm];
bool check[maxm];
struct State {
	int id, d;
	bool operator <(const State &b) const { return d > b.d; }
};
priority_queue <State> q;
ll Dijkstra(int s, int t) {
	for(int i = S; i <= T; ++i) dis[i] = inf, check[i] = 0;
	dis[s] = 0;
	while(!q.empty()) q.pop();
	
	q.push((State){ s, 0 });
	while(!q.empty()) {
		State o = q.top(); q.pop();
		if(check[o.id]) continue;
		check[o.id] = true;
		if(o.id == t) break;
		for(int i = head[o.id]; i; i = data[i].next) {
			Data &e = data[i];
			if(!check[e.to] && dis[e.to] > dis[o.id]+e.w) {
				dis[e.to] = dis[o.id]+e.w;
				q.push((State){ e.to, dis[e.to] });
			}
		}
	}
	return dis[t];		
}

int main() {
	freopen("RIVPILE.in", "r", stdin);
	freopen("my.out", "w", stdout);

	for(int kase = read(); kase; --kase) {
		init();
		BuildGraph();
		ll ans = Dijkstra(S, T);
		if(ans >= inf) printf("impossible\n");
		else printf("%lld\n", ans);
	}
	return 0;
}
