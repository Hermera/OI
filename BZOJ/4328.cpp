#include <cstdio>
#include <bitset>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2005;
bitset <maxn> f[maxn];
int n, back, ret[maxn], ans[maxn], q[maxn];

bool Gauss() {
	for(int i = 1, j; i <= n; ++i) {
		for(j = i; j <= n; ++j) if(f[j][i]) break;
		if(j > n) continue;
		swap(f[j], f[i]), swap(ret[j], ret[i]);
		for(int k = 1; k <= n; ++k)
			if(f[k][i] && k != i) f[k] ^= f[i], ret[k] ^= ret[i];
	}
	
	for(int i = n; i; --i) {
		int s = 0;
		for(int j = i+1; j <= n; ++j) s ^= f[i][j]*ans[j];
		if(!f[i][i]) {
			if(s != ret[i]) return 0;
		} 
		else ans[i] = ret[i]^s;
	}
	
	return 1;
}

int main() {
	n = read();
	for(int i = 1, m; i <= n; ++i) {
		m = read();
		if(m&1) f[i][i] = 1, ret[i] = 1;
		while(m--) f[i][read()] = 1;		
	}
	
	if(!Gauss()) return printf("Impossible\n"), 0;
	for(int i = 1; i <= n; ++i)
		if(ans[i]) q[++back] = i;
		
	printf("%d\n", back);
	for(int i = 1; i <= back; ++i) printf("%d ", q[i]);
	printf("\n");
	return 0;
}
