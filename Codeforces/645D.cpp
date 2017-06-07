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
int N, M, cnt, dp[maxn], mx[maxn], head[maxn];
struct Data { int next, to, id; } data[maxn];
void add(int x, int y, int id) {
	data[++cnt] = (Data){ head[x], y, id }; head[x] = cnt;
}

bool update(int x, int &y) { 
	y = max(x, y);
	return x == y;
}

int count(int x) {
	if(dp[x]) return dp[x];
	dp[x] = 1;
	for(int i = head[x]; i; i = data[i].next) {
		Data &e = data[i];
		if(update(count(e.to)+1, dp[x]))
			mx[x] = max(mx[e.to], e.id);
	}
	return dp[x];
}

int main() {
	freopen("645D.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1, u, v; i <= M; ++i) 
		u = read(), v = read(), add(u, v, i);
	
	for(int i = 1; i <= N; ++i)
		if(count(i) == N) 
			return printf("%d\n", mx[i]), 0;
	printf("-1\n");
	return 0;
}
