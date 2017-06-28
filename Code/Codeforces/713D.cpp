#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1005, maxl = 11;
int N, M, Q, a[maxn][maxn], b[maxn][maxn];

struct ST {
	int t[maxl][maxl][maxn][maxn], log[maxn];
	void init() {
		log[0] = -1;
		for(int i = 1; i <= max(N, M); ++i) log[i] = log[i>>1]+1;
		
		for(int i = 0; i <= log[N]; ++i)
		for(int j = 0; j <= log[M]; ++j) 
			for(int x = 1; x <= N-(1<<i)+1; ++x)
			for(int y = 1; y <= M-(1<<j)+1; ++y) {
				int &now = t[i][j][x][y];
				if(!i && !j) now = b[x][y];
				else if(!i) now = max(t[i][j-1][x][y], t[i][j-1][x][y+(1<<(j-1))]);
				else now = max(t[i-1][j][x][y], t[i-1][j][x+(1<<(i-1))][y]);
			}
	}
	
	int query(int x1, int y1, int x2, int y2) {
		int lx = log[x2-x1+1];
		int ly = log[y2-y1+1];
		#define v t[lx][ly]
		
		x2 -= (1<<lx)-1;
		y2 -= (1<<ly)-1;
		return max(max(v[x1][y1], v[x1][y2]), max(v[x2][y1], v[x2][y2]));
	}
} RMQ;

int main() {
	freopen("713D.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
		a[i][j] = read();
		
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
		if(a[i][j]) b[i][j] = min(min(b[i-1][j], b[i][j-1]), b[i-1][j-1])+1;
		
	RMQ.init();
	Q = read();
	for(int i = 1, x1, y1, x2, y2; i <= Q; ++i) {
		x1 = read(), y1 = read();
		x2 = read(), y2 = read();
		
		int l = 0, r = min(x2-x1+1, y2-y1+1), ans;
		while(l <= r) {
			int mid = (l+r)>>1;
			if(RMQ.query(x1+mid-1, y1+mid-1, x2, y2) >= mid) 
				ans = mid, l = mid+1;
			else r = mid-1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
