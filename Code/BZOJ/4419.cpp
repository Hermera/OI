#include <cstdio>
#include <map>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
int n, m, a[maxn], b[maxn];
map <int, int> vis[maxn];
map <int, int>:: iterator it;
char op[3];

int main() {
	n = read(), m = read();
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%s", op);
		if(*op == '!') ++a[read()];
		else {
			x = read(), y = read();
			if(*op == '+') vis[x][y] = a[y], vis[y][x] = a[x];
			else {
				b[x] += a[y]-vis[x][y];
				b[y] += a[x]-vis[y][x];
				vis[x].erase(y);
				vis[y].erase(x);
			}
		}
	}
	
	for(int i = 1; i <= n; ++i) 
	for(it = vis[i].begin(); it != vis[i].end(); ++it)
		b[i] += a[it->first] - it->second;
	for(int i = 1; i <= n; ++i) 
		if(i == n) printf("%d\n", b[i]);
		else printf("%d ", b[i]);
	return 0;
}
