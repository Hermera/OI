#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxl = 31;
int N, ans, a[maxn], f[maxn], g[maxl];

int main() {
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1; i <= N; ++i) {
		f[i] = 1;
		for(int j = 0; j < maxl; ++j)
			if(a[i]&(1<<j)) f[i] = max(f[i], g[j]+1);
		for(int j = 0; j < maxl; ++j)
			if(a[i]&(1<<j)) g[j] = f[i];
	}
	
	for(int i = 1; i <= N; ++i) ans = max(ans, f[i]);
	printf("%d\n", ans);
	return 0;
}
