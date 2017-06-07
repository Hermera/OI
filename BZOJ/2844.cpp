#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
const int mod = 10086;
int n, m, t, a[maxn], b[maxn];

void gauss() {
	for(int i = 1<<30; i; i >>= 1) {
		int j = t+1;
		while(!(i&(a[j])) && j <= n) ++j;
		if(j > n) continue;
		++t;
		
		swap(a[t], a[j]), b[t] = i;
		for(int k = 1; k <= n; ++k)
			if(k != t && (a[k]&i)) a[k] ^= a[t];
	}
}

int pow(int x, int k) {
	int ret = 1;
	for(; k; k >>= 1, (x *= x)%= mod)
		if(k&1) (ret *= x)%= mod;
	return ret;
}

int main() {	
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	m = read();
	gauss();
	
	int ans = 1;
	for(int i = 1; i <= t; ++i)
		if(m&b[i])	m ^= a[i], (ans += pow(2, n-i))%= mod;
	printf("%d\n", ans);
	return 0;
}
