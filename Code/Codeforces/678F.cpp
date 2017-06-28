#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 3e5+5;
const ll inf = 2e18;
struct Point {
	ll x, y;
	void init() { x = read(), y = read(); }
	ll calc(ll q) { return q*x+y; }
	bool operator <(const Point &b) const {
		return x != b.x ? x < b.x : y < b.y;
	}
	Point operator -(const Point &b) const {
		return (Point){ x-b.x, y-b.y };
	}
	ll operator *(const Point &b) const {
		return x*b.y - y*b.x;
	}
} p[maxn], st[maxn];

int N, tot, top;
int op[maxn], q[maxn], id[maxn], s[maxn], e[maxn];
ll ans[maxn];

struct Segment {
	#define mid ((l+r)>>1)
	#define lc o<<1, l, mid
	#define rc o<<1|1, mid+1, r
	vector <Point> t[maxn<<2];
	
	void insert(int o, int l, int r, int x) {
		if(r < s[x] || e[x] < l) return;
		if(s[x] <= l && r <= e[x]) {
			t[o].push_back(p[x]);
			return;
		}
		insert(lc, x), insert(rc, x);
	}
	
	ll query(ll x) {
		int l = 1, r = top;
		if(!top) return -inf;
		while(r-l > 6) {
			int m1 = (2*l+r)/3, m2 = (l+2*r)/3;
			if(st[m1].calc(x) < st[m2].calc(x)) l = m1+1;
			else r = m2-1;
		}
		ll ret = -inf;
		for(int i = l; i <= r; ++i)
			ret = max(ret, st[i].calc(x));
		return ret;
	}
	
	void solve(int o, int l, int r) {
		top = 0;
		sort(t[o].begin(), t[o].end());
		for(int i = 0; i < t[o].size(); ++i) {
			Point x = t[o][i];
			while(top > 1 && (x-st[top])*(st[top]-st[top-1]) <= 0) --top;
			st[++top] = x;
		}
		for(int i = l; i <= r; ++i)
			if(op[i] == 3) ans[i] = max(ans[i], query(q[i]));
		
		if(l == r) return;
		solve(lc), solve(rc);
	}
} T;
		
int main() {
	N = read();
	for(int i = 1; i <= N; ++i) {
		op[i] = read(), ans[i] = -inf;
		if(op[i] == 1) {
			p[++tot].init();
			s[tot] = i, e[tot] = N;
			id[i] = tot;
		}
		if(op[i] == 2) e[id[read()]] = i-1;
		if(op[i] == 3) q[i] = read();
	}
	
	for(int i = 1; i <= tot; ++i) T.insert(1, 1, N, i);
	T.solve(1, 1, N);
	
	for(int i = 1; i <= N; ++i) 
	if(op[i] == 3) 
		if(ans[i] == -inf) printf("EMPTY SET\n");
		else printf("%lld\n", ans[i]);
	return 0;
}
			
