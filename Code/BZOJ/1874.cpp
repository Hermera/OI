#include <cstdio>
using namespace std;

const int maxn = 1005;
int n, m, c = 1000;
int a[maxn], b[maxn], sg[maxn], vis[maxn];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a+i);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) scanf("%d", b+i);
	
	sg[0] = 0;
	for(int i = 1; i <= c; ++i) 
	for(int j = 1; j <= m; ++j) if(i >= b[j]) {
		vis[sg[i-b[j]]] = i;
		for(int k = 0;; ++k) 
			if(vis[k] != i) {
				sg[i] = k;
				break;
			}
	}
	
	int mat = 0;
	for(int i = 1; i <= n; ++i) mat ^= sg[a[i]];
	if(!mat) printf("NO\n");
	else {
		printf("YES\n");
		for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) if(a[i] >= b[j]) {
			int ret = mat ^ sg[a[i]] ^ sg[a[i]-b[j]];
			if(!ret) {
				printf("%d %d\n", i, b[j]);
				return 0;
			}
		}
	}
	return 0;
}
