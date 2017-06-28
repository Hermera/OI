#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int N, root[maxn], key[maxn], l[maxn], r[maxn], dis[maxn], pev[maxn], nxt[maxn];

int merge(int x, int y) {
	if(!x || !y) return x+y;
	if(key[y] < key[x]) swap(x, y);
	r[x] = merge(r[x], y);
	if(dis[r[x]] > dis[l[x]]) swap(l[x], r[x]);
	dis[x] = dis[r[x]]+1;
	return x;
}
	
int Gauss() {
	int ret = 1;
	
	for(int i = 1; i <= N; ++i) {
		int x = root[i];
		if(!x || key[x] < i) return 0;
		if(x > i) ret = -ret;
		root[key[x]+1] = merge(root[key[x]+1], merge(l[x], r[x]));
	}
	return ret;
}

int main() {
	for(int T = read(); T; --T) {
		N = read();
		for(int i = 1; i <= N; ++i) root[i] = 0;
		for(int i = 1, x, y; i <= N; ++i) {
			x = read(), y = read();
			key[i] = y;
			root[x] = merge(root[x], i);
		}
		int ans = Gauss();
		if(!ans) printf("Draw\n");
		else printf("%s\n", ans > 0 ? "Alex" : "Fedor");
	}
	return 0;
}
