#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1e5+5;
int c, m, tim, p[maxn], sg[maxn], vis[maxn];

int get(int n) {
	if(n < m) return 0;
	if(~sg[n]) return sg[n];
	for(int i = 2; i <= n; i = n/(n/i)+1)
		for(int j = i; j <= i+1 && j <= n; ++j)
			get(n/j), get(n/j+1);
			
	++tim;
	for(int i = 2; i <= n; i = n/(n/i)+1)
		for(int j = i; j <= i+1 && j <= n; ++j) {
			int ret = 0;
			if((n%j) & 1) ret ^= sg[n/j + 1];
			if((j - n%j) & 1) ret ^= sg[n/j];
			vis[ret] = tim;
		}
	sg[n] = 0;
	while(vis[sg[n]] == tim) ++sg[n];
	return sg[n];
}

int main() {
	scanf("%d%d", &c, &m);
	memset(sg, -1, sizeof(sg));
	for(int x; c--;) {
		scanf("%d", &x);
		
		int ans = 0;
		for(int i = 1; i <= x; ++i) scanf("%d", p+i);
		for(int i = 1; i <= x; ++i) ans ^= get(p[i]);
		printf("%d", ans ? 1 : 0);
		printf("%c", c ? ' ' : '\n');
	}
	return 0;
}
