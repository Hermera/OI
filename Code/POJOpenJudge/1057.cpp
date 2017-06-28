#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 6e5+5;
const int K = 15;


int h[N], cnt, idx;
struct Data {
	int next, to;
} g[N * K];

void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}

int tim, tot, top;
int dfn[N], low[N], sta[N], scc[N];
void tarjan(int x) {
	dfn[x] = low[x] = ++tim;
	sta[++top] = x;
	for(int i = h[x]; i; i = g[i].next) {
		int v = g[i].to;
		if(!dfn[v]) tarjan(v);
		if(!scc[v]) low[x] = min(low[x], low[v]);
	}
	if(dfn[x] == low[x])
		for(++tot; top;) {
			scc[sta[top]] = tot;
			if(sta[top--] == x) break;
		}
}


#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
int lid[N], pid[N];
struct Segment {
	int tid[N << 2];
	void build(int o, int l, int r) {
		tid[o] = ++idx;
		if(l == r) {
			lid[l] = tid[o];
			return;
		}
		build(lc), build(rc);
		add(tid[o], tid[o<<1]);
		add(tid[o], tid[o<<1|1]);
	}
	
	void make(int o, int l, int r, int L, int R, int k) {
		if(R < l || r < L) return;
		if(L <= l && r <= R) return add(k, tid[o]);
		make(lc, L, R, k);
		make(rc, L, R, k);
	}
} T;


int *L, *R, n, p[N], sure[N];
struct compare {
	bool operator ()(int x, int y) {
		return R[x] > R[y] || R[x] == R[y] && x > y;
	}
};
priority_queue <int, vector<int>, compare> q;

bool cmp(int x, int y) {
	return L[x] < L[y];
}

bool work(int *a, int *b, int *G) {
	L = a, R = b;
	for(int i = 1; i <= n; ++i) p[i] = i;
	sort(p + 1, p + 1 + n, cmp);
	
	int t = 1;
	while(!q.empty()) q.pop();
	for(int i = 1; i <= n; ++i) {
		while(t <= n && L[p[t]] == i) q.push(p[t++]);
		if(q.empty()) return 0;
		if(R[q.top()] < i) return 0;
		G[q.top()] = i, q.pop();
	}
	
	idx = cnt = 0;
	memset(h, 0, sizeof h);
	memset(dfn, 0, sizeof dfn);
	memset(scc, 0, sizeof scc);
	
	T.build(1, 1, n);
	for(int i = 1; i <= n; ++i) pid[i] = ++idx;
	for(int i = 1; i <= n; ++i) {
		T.make(1, 1, n, L[i], G[i]-1, pid[i]);
		T.make(1, 1, n, G[i]+1, R[i], pid[i]);
		add(lid[G[i]], pid[i]);
	}
	
	for(int i = 1; i <= idx; ++i)
		if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; ++i)
		if(scc[pid[i]] != scc[lid[G[i]]]) ++sure[i];
	return 1;
}

int a1[N], a2[N], b1[N], b2[N];
int to1[N], to2[N];
int main() {
	while(scanf("%d", &n) != EOF) {
		for(int i = 1; i <= n; ++i) sure[i] = 0;
		for(int i = 1; i <= n; ++i) {
			a1[i] = read(), b1[i] = read();
			a2[i] = read(), b2[i] = read();
		}
		
		if(work(a1, a2, to1) && work(b1, b2, to2)) {
			int ans = 0;
			for(int i = 1; i <= n; ++i)
				if(sure[i] == 2) ++ans;
			printf("%d\n", ans);
			for(int i = 1; i <= n; ++i)
				if(sure[i] == 2) printf("%d %d %d\n", i, to1[i], to2[i]);
		} else printf("-1\n");
	}
	return 0;
}
