#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 3005;
int N, sum, fa[maxn], avai[maxn], size[maxn];

struct Edge {
	int x, y, w;
	void init() { scanf("%d%d%d", &x, &y, &w); }
	bool operator <(const Edge &b) const { return w < b.w; }
} e[maxn];

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
bool Union(int x, int y) {
	x = Find(x), y = Find(y);
	if(x == y) return false;
	size[x] += size[y];
	avai[x] += avai[y];
	fa[y] = x;
	return true;
}

int main() {
	scanf("%d", &N);
	if(N == 1) printf("0\n");
	for(int i = 1; i < N; ++i) e[i].init();
	for(int i = 1; i <= N; ++i) 
		scanf("%d", avai+i), sum += avai[i], fa[i] = i, size[i] = 1;
	sort(e+1, e+N);
	
	for(int i = 1; i < N; ++i)
	if(Union(e[i].x, e[i].y)) {
		int u = Find(e[i].x);
		if(size[u] > sum-avai[u]) {
			printf("%d\n", e[i].w);
			return 0;
		}
	}
}
