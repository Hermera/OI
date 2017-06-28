#include <cstdio>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int u[maxn], v[maxn], c[maxn], f[maxn];
int n, k;

int main() {
	n = read();
	for(int i = 2; i <= n; ++i) u[i] = read(), v[i] = read();
	for(int i = 1; i <= n; ++i) c[i] = read();
	for(int i = 2; i <= n; ++i) 
		if(c[u[i]] != c[v[i]]) 
			++k, ++f[u[i]], ++f[v[i]];
	for(int i = 1; i <= n; ++i) 
		if(k == f[i]) {	
			printf("YES\n%d\n", i);
			return 0;
		}
	printf("NO\n");
	return 0;
}
