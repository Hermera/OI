#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 105;
int t, n, c = 100;
int sg[maxn][maxn], vis[maxn];

int main() {
	for(int i = 1; i <= c; ++i)
	for(int j = 1; j <= c; ++j) if(i != j) {
		int id = (i-1)*c+j;
		for(int k = 1; k < i; ++k) if(i-k != j) vis[sg[i-k][j]] = id;
		for(int k = 1; k < j; ++k) if(j-k != i) vis[sg[i][j-k]] = id;
		for(int k = min(i, j)-1; k; --k) vis[sg[i-k][j-k]] = id;
		for(int k = 0;; ++k) 
			if(vis[k] != id) {	
				sg[i][j] = k;
				break;
			}
	}

	scanf("%d", &t);
	while(t--) {
		int mat = 0, ans = 0;
		scanf("%d", &n);
		for(int x, y; n--; ) {
			scanf("%d%d", &x, &y);
			mat ^= sg[x][y];
			if(!x || !y || x == y) ans = 1;
		}
		
		if(ans || mat) printf("^o^\n");
		else printf("T_T\n");
	}
	return 0;
}
