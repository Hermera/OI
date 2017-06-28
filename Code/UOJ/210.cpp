#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5;
int n, m, o, cnt, top, tot, tim, back;
int h[maxn], dfn[maxn], low[maxn], scc[maxn], st[maxn], np[maxn], put[maxn];
struct Data { int next, to; } G[maxn*8];

void add(int x, int y) {
	G[++cnt] = (Data){ h[x], y }; h[x] = cnt;
	G[++cnt] = (Data){ h[y^1], x^1 }; h[y^1] = cnt;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++tim;
	st[++top] = x;
	for(int i = h[x]; i; i = G[i].next) {
		int v = G[i].to;
		if(!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
		else if(!scc[v]) low[x] = min(low[x], low[v]);
	}
	if(low[x] == dfn[x]) {
		++tot;
		while(top) {
			int v = st[top--];
			scc[v] = tot;
			if(v == x) break;
		}
	}
}

int no(int x, int d) { return x<<1|d; }
int say(int x, int d) { return (n+x)<<1|d; }
int main() {
	//true & good man: 1
	//false & liar: 0
	
	n = read(), m = read();
	o = say(m+1, 1)+1;
	for(int i = 1; i <= n; ++i) np[i] = 1;
	for(int i = 2, x, y, t; i <= m+1; ++i) {
		scanf("%d%d%d", &x, &y, &t), t = !t;
		add(no(y, !t), say(np[x], 1));
		add(say(i, 1), no(y, t));
		add(say(i, 1), say(np[x], 1));
		np[x] = i;
	}
	for(int i = 1; i <= n; ++i) add(say(np[i], 0), no(i, 1));
	
	for(int i = o; i; --i) if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= o; i += 2) 
		if(scc[i] == scc[i^1]) return puts("Impossible"), 0;
	
	for(int i = 1; i <= n; ++i)
		if(scc[no(i, 1)] < scc[no(i, 0)]) put[++back] = i;
	printf("%d\n", back);
	for(int i = 1; i <= back; ++i) 
		printf("%d%c", put[i], i == back ? '\n' : ' ');
	return 0;
}
