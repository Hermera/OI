#include <cstdio>
using namespace std;

const int maxn = 505;
int n, t, a[maxn], sg[maxn], vis[maxn];

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i <= n*n; ++i) vis[i] = sg[i] = 0;
		for(int i = 1; i <= n; ++i) scanf("%d", a+i), a[i] &= 1;
		for(int i = n-1; i; --i) {
			for(int j = i+1; j <= n; ++j)
			for(int k = j; k <= n; ++k)
				vis[sg[j]^sg[k]] = i;
			for(int j = 0;; ++j) 
				if(vis[j] != i) {
					sg[i] = j;
					break;
				}
		}
						
		int sta = 0, ans = 0;
		for(int i = 1; i <= n; ++i) if(a[i]) sta ^= sg[i];
		if(!sta) printf("-1 -1 -1\n0\n");
		else {
			for(int i = 1; i < n; ++i)
			for(int j = i+1; j <= n; ++j)
			for(int k = j; k <= n; ++k) {
				int ret = sta;
				ret ^= sg[i];
				ret ^= sg[j];
				ret ^= sg[k];
				if(!ret) {
					if(!ans) printf("%d %d %d\n", i-1, j-1, k-1);
					++ans;
				}
			}
			printf("%d\n", ans);
		}
		
	}
	return 0;
}
