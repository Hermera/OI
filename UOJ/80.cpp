#include <cstdio>
#include <cstring>
#include <algorithm>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
typedef long long ll;

const int maxn = 405;
const int INF = 1e9;

inline int cmin(int &x, int y) { return x > y ? x = y, 1 : 0; } 
inline int cmax(int &x, int y) { return x < y ? x = y, 1 : 0; }

namespace KM {
	int w[maxn][maxn], n;
	void add(int x, int y, int c) { cmax(w[x][y], c); }
	void clear(int nn) { mset(w, 0), n = nn; }
	
	int slack[maxn], q[maxn], pre[maxn];
	int mx[maxn], my[maxn], wx[maxn], wy[maxn];
	bool vx[maxn], vy[maxn];
	
	void match(int y) {
		for(int x, z; ~y; y = z) {
			x = pre[y], z = mx[x];
			mx[x] = y, my[y] = x;
		}
	}
	
	void find(int now) {
		mset(vx, 0), mset(vy, 0), mset(slack, 63);
		
		int h = 1, t = 0;
		q[++t] = now, vx[now] = 1;
		for(;;) {
			while(h <= t) {
				int x = q[h++];
				for(int y = 1; y <= n; ++y) if(!vy[y]) {
					int d = wx[x] + wy[y] - w[x][y];
					if(!d) {
						pre[y] = x;
						if(my[y] < 0) return match(y);
						q[++t] = my[y];
						vx[my[y]] = vy[y] = 1;
					} else if(cmin(slack[y], d)) pre[y] = x;
				}
			}
		
			int d = INF;
			for(int i = 1; i <= n; ++i) 
				if(!vy[i]) cmin(d, slack[i]);
			for(int i = 1; i <= n; ++i) {
				if(vx[i]) wx[i] -= d;
				if(vy[i]) wy[i] += d;
				else slack[i] -= d;
			}
			
			for(int i = 1; i <= n; ++i)
				if(!vy[i] && !slack[i]) {
					if(my[i] < 0) return match(i);
					q[++t] = my[i];
					vx[my[i]] = vy[i] = 1;
				}
		}
	}

	ll solve() {	
		mset(mx, -1), mset(my, -1);
		mset(wx, -63), mset(wy, 0);
		
		for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			cmax(wx[i], w[i][j]);
		for(int i = 1; i <= n; ++i) find(i);
		
		ll ret = 0;
		for(int i = 1; i <= n; ++i)
			ret += wx[i] + wy[i];
		return ret;
	}
}


int n1, n2, m;
int main() {
	using namespace KM;

	scanf("%d%d%d", &n1, &n2, &m);
	clear(max(n1, n2));
	for(int x, y, c; m--;) scanf("%d%d%d", &x, &y, &c), add(x, y, c);
	printf("%lld\n", solve());
	
	for(int i = 1; i <= n1; ++i)
		if(w[i][mx[i]]) printf("%d ", mx[i]);
		else printf("0 ");
	printf("\n");
	return 0;
}
