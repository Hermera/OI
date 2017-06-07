#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxl = 22;
int N, M, T, u[maxn], v[maxn], c[maxn*maxl], t[maxn], l[maxn][maxl];

bool work() {
	for(int i = 1; i <= N; ++i) t[i] = l[i][rand()%l[i][0]+1];
	for(int i = 1; i <= T; ++i) c[i] = (rand()&1)+1;
	int ret = 0;
	for(int i = 1; i <= M; ++i)
		if(c[t[u[i]]] != c[t[v[i]]]) ++ret;	
	return ret*2 >= M;
}

int main() {
	srand(20000909);
	N = read(), M = read();
	for(int i = 1; i <= M; ++i) u[i] = read(), v[i] = read();
	for(int i = 1; i <= N; ++i) {
		l[i][0] = read();
		for(int j = 1; j <= l[i][0]; ++j) 
			T = max(l[i][j] = read(), T);
	}
	
	while(!work());
	for(int i = 1; i <= N; ++i) printf("%d ", t[i]);
	printf("\n");
	for(int i = 1; i <= T; ++i) printf("%d ", c[i]);
	printf("\n");
	return 0;
}
	
