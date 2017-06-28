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
int n, m, t, tim, ans, k = 1e5;
int a[maxn], mn[maxn], mx[maxn], dp[maxn];
struct BIT {
	int t[maxn], v[maxn];
	void add(int x, int c) {
		for(; x <= k; x += x&-x) {
			if(v[x] != tim) t[x] = 0, v[x] = tim;
			t[x] = max(t[x], c);
		}
	}
	
	int query(int x) {
		int ret = 0;
		for(; x; x -= x&-x) 
			if(v[x] == tim) ret = max(ret, t[x]);
		return ret;
	}
} T;

struct ele {
	int op, id, val;
	bool operator <(const ele &b) const {
		return val != b.val ? val < b.val : id < b.id;
	}
} op[maxn];

void solve(int l, int r) {
	if(l == r) return;
	int mid = (l+r)>>1;
	solve(l, mid);
	
	++tim, t = 0;
	for(int i = l; i <= mid; ++i)  op[++t] = (ele){ 0, i, mx[i] };
	for(int i = mid+1; i <= r; ++i) op[++t] = (ele){ 1, i, a[i] };
	sort(op+1, op+1+t);
	
	for(int i = 1; i <= t; ++i) {
		ele &e = op[i];
		if(!e.op) T.add(a[e.id], dp[e.id]);
		else dp[e.id] = max(dp[e.id], T.query(mn[e.id])+1);
	}

	solve(mid+1, r);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) dp[i] = 1;
	for(int i = 1; i <= n; ++i) a[i] = mn[i] = mx[i] = read();
	for(int i = 1, x, y; i <= m; ++i)
		x = read(), y = read(),
		mn[x] = min(mn[x], y),
		mx[x] = max(mx[x], y);
	
	solve(1, n);
	for(int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}
