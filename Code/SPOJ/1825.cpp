#include <cstdio>
#include <algorithm>
#include <vector>
#define Int register int
using namespace std;
int read() {
	char ch = getchar(); Int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 2e5+5;
int N, K, M, D, sum, ans, cnt, root;
int head[maxn], size[maxn], f[maxn], deep[maxn], dis[maxn], tmp[maxn], mx[maxn];
bool cow[maxn], vis[maxn];
struct Data { int next, to, w; } data[maxn<<1];
void add(Int x, Int y, Int w) {
	data[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
}

void Getroot(Int x, Int fa) {
	size[x] = 1, f[x] = 0;
	for(Int i = head[x]; i; i = data[i].next) 
		if(!vis[data[i].to] && data[i].to != fa) {
			Data &e = data[i];
			Getroot(e.to, x);
			f[x] = max(f[x], size[e.to]);
			size[x] += size[e.to];
		}
	f[x] = max(f[x], sum-size[x]);
	if(f[x] < f[root]) root = x;
}

void Getdis(Int x, Int fa) {
    D = max(D, deep[x]);
	for(Int i = head[x]; i; i = data[i].next) 
		if(!vis[data[i].to] && data[i].to != fa) {
			Data &e = data[i];
			deep[e.to] = deep[x]+cow[e.to];
			dis[e.to] = dis[x]+e.w;
			Getdis(e.to, x);
		}
}

void Getmax(Int x, Int fa) {
	tmp[deep[x]] = max(tmp[deep[x]], dis[x]);
	for(Int i = head[x]; i; i = data[i].next) 
		if(!vis[data[i].to] && data[i].to != fa) Getmax(data[i].to, x);
}

struct Node {
	int to, mx;
	bool operator <(const Node &b) const {
		return mx < b.mx;
	}
};
vector <Node> G;
void solve(Int x) {
	vis[x] = true;
	G.clear();
	if(cow[x]) --K;
	
	for(Int i = head[x]; i; i = data[i].next) 
	if(!vis[data[i].to]) {
		Data &e = data[i]; 
		deep[e.to] = cow[e.to], dis[e.to] = e.w, D = 0;
		Getdis(e.to, x);
		G.push_back((Node){ e.to, D });
	}
	
	sort(G.begin(), G.end());
	for(Int i = 0; i < G.size(); ++i) {
		Getmax(G[i].to, x);
		Int now = 0;
		
		if(i) for(Int j = G[i].mx; ~j; --j) {
			while(now+j < K && now < G[i-1].mx)
				++now, mx[now] = max(mx[now], mx[now-1]);
			if(now+j <= K) ans = max(ans, mx[now]+tmp[j]);
		}
		
		for(Int j = 0; j <= G[i].mx; ++j)
			mx[j] = max(mx[j], tmp[j]), tmp[j] = 0;
	}
	for(Int j = G[G.size()-1].mx; ~j; --j) {
		if(j <= K) ans = max(ans, mx[j]);
		mx[j] = 0;
	}
	
	if(cow[x]) ++K;
	for(Int i = head[x]; i; i = data[i].next) 
		if(!vis[data[i].to]) {
			Data &e = data[i];
			root = 0, sum = size[e.to];
			Getroot(e.to, x);
			solve(root);
		}
}	

int main() {
	freopen("freetourII.in", "r", stdin);
	freopen("freetourII.out", "w", stdout);

	N = read(), K = read(), M = read();
	for(Int i = 1; i <= M; ++i) cow[read()] = true;
	for(Int i = 1, u, v, w; i < N; ++i)
		u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	
	sum = f[0] = N;
	Getroot(1, 0);
	solve(root);
	printf("%d\n", ans);
	return 0;
}
