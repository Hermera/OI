#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 3e5+5;
int N, ans;
struct Point {
	ll x, y; int m, p, r, id;
	double d;
	void init() {
		x = read(), y = read(), m = read(), p = read(), r = read();
	}
	bool operator <(const Point &b) const {
		return d < b.d;
	}
} a[maxn], O, V;
queue <Point> q;
double f[maxn];

#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Segment {
	Point t[maxn<<2];
	Point merge(Point ls, Point rs) {
		if(ls.m < rs.m) return ls;
		else return rs;
	}
	
	void build(int o, int l, int r) {
		if(l == r) t[o] = a[l];
		else build(lc), build(rc), t[o] = merge(t[o<<1], t[o<<1|1]);
	}
	
	void erase(int o, int l, int r, int p) {
		if(l == r) {
			t[o] = V;
			return;
		}
		if(p <= mid) erase(lc, p);
		else erase(rc, p);
		t[o] = merge(t[o<<1], t[o<<1|1]);
	}
	
	Point query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[o];
		if(R < l || r < L) return V;
		return merge(query(lc, L, R), query(rc, L, R));
	}
} T;

double dis(Point a, Point b) {
	return sqrt(1.0*(a.x-b.x)*(a.x-b.x) + 1.0*(a.y-b.y)*(a.y-b.y));
}

int main() {
	freopen("3276.in", "r", stdin);
	freopen("my.out", "w", stdout);

	V.m = 2e9;
	scanf("%lld%lld%d%d%d", &O.x, &O.y, &O.p, &O.r, &N);
	for(int i = 1; i <= N; ++i) a[i].init();
	for(int i = 1; i <= N; ++i) a[i].d = dis(a[i], O);
	sort(a+1, a+1+N);
	for(int i = 1; i <= N; ++i) f[i] = a[i].d, a[i].id = i;
	
	T.build(1, 1, N);
	q.push(O);
	while(!q.empty()) {
		O = q.front(); q.pop();
		int lim = upper_bound(f+1, f+1+N, O.r)-f-1;
		Point P = T.query(1, 1, N, 1, lim);
		while(P.m <= O.p) {
			q.push(P), ++ans;
			T.erase(1, 1, N, P.id);
			P = T.query(1, 1, N, 1, lim);
		}
	}
	
	printf("%d\n", ans);
	return 0;
}
