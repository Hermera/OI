#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 105;
int n, back, root, lc[maxn], rc[maxn], fa[maxn], put[maxn];

void solve(int x) {
	while(~rc[x]) x = lc[x];
	int t = lc[x];
	if(~t && lc[t] < 0 && rc[t] < 0) x = t;
	put[++back] = x;
	
	if(x == root) root = lc[x];
	int f = fa[x];
	if(~f) lc[f] = lc[x], fa[lc[f]] = f;
	while(~f) swap(lc[f], rc[f]), f = fa[f];
}

int main() {
	fa[0] = -1;
	memset(lc, -1, sizeof(lc));
	memset(rc, -1, sizeof(rc));
	
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		if(x < 100) lc[x] = i, fa[i] = x;
		else rc[x-100] = i, fa[i] = x-100;
	}
	
	for(int i = 1; i <= n+1; ++i) solve(root);
	for(int i = back; i; --i) printf("%d ", put[i]);
	printf("\n");
	return 0;
}
