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
int K, N, M, T, a[maxn], f[maxn];

int main() {
	K = read(), N = read(), M = read(), T = read();
	T = min(N, min(M, T));
	while(K--) {	
		for(int i = 1; i <= N; ++i) a[i] = read();
		for(int i = 1; i <= M; ++i) f[i] = 0;
		
		for(int i = 1; i <= T; ++i)
		for(int j = 1; j <= N; ++j)
			for(int v = a[j]; v <= M && f[v] == f[a[j]-1]; ++v)	
				++f[v];
			
		int ans = 0;
		for(int i = 1; i <= M; ++i) ans = max(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}
