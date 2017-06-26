#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 150005;

#define mid (l + r >> 1)
#define lc o << 1, l, mid
#define rc o << 1 | 1, mid + 1, r
struct segment {
	int t[N << 2], p[N << 2];
	void pushup(int o) {
		t[o] = min(t[o << 1], t[o << 1 | 1]) + p[o];
	}

	void build(int o, int l, int r) {
		if (l == r) return (void) (t[o] = -l);
		build(lc), build(rc), pushup(o);
	}

	void modify(int o, int l, int r, int L, int R, int v) {
		if (R < l || r < L) return;
		if (L <= l && r <= R) {
			t[o] += v, p[o] += v;
			return;
		}
		modify(lc, L, R, v);
		modify(rc, L, R, v);
		pushup(o);
	}

	int query() {
		return t[1];
	}
} T;


int n, m, h;
int a[N], b[N];

int main() {
	freopen("6062.in", "r", stdin);

	n = read(), m = read(), h = read();
	for (int i = 1; i <= m; ++i) b[i] = read();
	sort(b + 1, b + 1 + m);
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + 1 + m, h - read()) - b;

	T.build(1, 1, m);
	for (int i = 1; i <= m; ++i) 
		T.modify(1, 1, m, a[i], m, 1);

	int ans = 0;
	for (int i = m; i <= n; ++i) {
		if (i != m) {
			T.modify(1, 1, m, a[i], m, 1);
			T.modify(1, 1, m, a[i-m], m, -1);
		}

		if (T.query() >= 0) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}