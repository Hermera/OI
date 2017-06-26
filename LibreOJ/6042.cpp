#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 105;
int a[N], p[N], n;

void work(int x, int c) {
	a[x] = c, c = -c;
	for(int i = p[x]; i != x; i = p[i])
		a[i] = c, c = -c;
}


void dfs(int x, int sum) {
	if(sum < 0) return;
	if(x > n) {
		if(!sum) {
			for(int i = 1; i <= n; ++i)
				printf("%c", a[i] > 0 ? '(' : ')');
			exit(0);
		}
		return;
	}
	
	if(a[x]) dfs(x + 1, sum + a[x]);
	else {
		work(x,  1), dfs(x + 1, sum + 1), work(x, 0);
		work(x, -1), dfs(x + 1, sum - 1), work(x, 0);
	}
}


int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", p + i);
	for(int i = 1; i <= n; ++i)
		if(i < p[i] && i == p[p[i]]) 
			a[i] = 1, a[p[i]] = -1;
	
	dfs(1, 0);
	return 0;
}