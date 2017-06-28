#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e4+5;
const ll inf = 1e15;
int N, M, L, S, T, pos, tot, cnt, head[maxn];
ll dis[maxn], cost, l, r;
bool vis[maxn];
struct Edge { 
	int u, v, id; ll w;
	void init() { u = read(), v = read(), w = read(); }
} e[maxn];
struct Data { int next, to; ll w; } data[maxn];

void add(int x, int y, ll w) {
	data[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
	data[++cnt] = (Data){ head[y], x, w }; head[y] = cnt;
}

struct Node {
	int id; ll dis;
	bool operator <(const Node &b) const {
		return dis > b.dis;
	}
};
priority_queue <Node> q;

ll Dijkstra(int g, ll v) {
	cnt = 0;
	for(int i = 0; i < N; ++i) head[i] = vis[i] = 0, dis[i] = inf;
	for(int i = 1; i <= M; ++i) 
		if(!e[i].w) {
			if(e[i].id <  g) add(e[i].u, e[i].v, 1);
			if(e[i].id == g) add(e[i].u, e[i].v, v);
			if(e[i].id >  g) add(e[i].u, e[i].v, inf);
		}
		else add(e[i].u, e[i].v, e[i].w);
	
	dis[S] = 0;
	q.push((Node){ S, 0 });
	while(!q.empty()) {
		Node t = q.top(); q.pop();
		if(vis[t.id]) continue;
		vis[t.id] = true;
		for(int i = head[t.id]; i; i = data[i].next) {
			Data &e = data[i];
			if(!vis[e.to] && dis[e.to] > t.dis+e.w) 
				dis[e.to] = t.dis+e.w, q.push((Node){ e.to, dis[e.to] });
		}
	}
	return dis[T];
}

int main() {
	freopen("715B.in", "r", stdin);

	scanf("%d%d%d%d%d", &N, &M, &L, &S, &T); 
	for(int i = 1; i <= M; ++i) {
		e[i].init();
		if(!e[i].w) e[i].id = ++tot;
	}
	
	if(Dijkstra(0, 0) < L || Dijkstra(tot+1, 0) > L) 
		return printf("No\n"), 0;
	
	l = 0, r = tot;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(Dijkstra(mid, 1) <= L) pos = mid, r = mid-1;
		else l = mid+1;
	}
	
	l = 1, r = inf;
	while(l <= r) {
		ll mid = (1LL*l+r)>>1;
		if(Dijkstra(pos, mid) <= L) cost = mid, l = mid+1;
		else r = mid-1;
	}
		
	printf("Yes\n");
	for(int i = 1; i <= M; ++i) 
		if(!e[i].w) {
			printf("%d %d ", e[i].u, e[i].v);
			if(e[i].id <  pos) printf("1\n");
			if(e[i].id == pos) printf("%lld\n", cost);
			if(e[i].id >  pos) printf("%lld\n", inf);
		}
		else printf("%d %d %lld\n", e[i].u, e[i].v, e[i].w);
	return 0;
}	
	
