#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e6+5;
typedef int arr[maxn];

int n, m, t, tim;
arr a, b, p, f, g;

struct BIT {
	arr w, v;
	void add(int x) {
		for( ; x <= n; x += x&-x) {
			if(v[x] != tim) v[x] = tim, w[x] = 0;
			++w[x];
		}
	}
	
	int query(int x) {
		int ret = 0;
		for( ; x; x -= x&-x)
			if(v[x] == tim) ret += w[x];
		return ret;
	}
} T;

struct ele {
	int type, pos, l, r, id;
	bool operator <(const ele &b) const {
		if(pos != b.pos) return pos < b.pos;
		return abs(type) < abs(b.type);
	}
} wk[maxn];

struct opt { int l, r, a, b, id; };
vector <opt> q[maxn], num[maxn];
vector <opt>:: iterator it;

#define REP(x) for(it = x.begin(); it != x.end(); ++it)
#define mid ((l+r)>>1)
void solve(int l, int r) {
	if(l != r) solve(l, mid);
	
	t = 0, ++tim;
	for(int i = mid; i >= l; --i) REP(num[i])
		wk[++t] = (ele){ 0, it->l, a[it->l] };
	for(int i = mid+(l != r); i <= r; ++i) REP(q[i]) 
		wk[++t] = (ele){ -1, it->l-1, it->a, it->b, it->id },
		wk[++t] = (ele){  1, it->r  , it->a, it->b, it->id };
	sort(wk+1, wk+1+t);
	for(int i = 1; i <= t; ++i) {
		ele &e = wk[i];
		if(!e.type) T.add(e.l);
		else g[e.id] += e.type*(T.query(e.r) - T.query(e.l-1));
	}
	
	if(l != r) solve(mid+1, r);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), p[i] = 1;
	for(int i = 1; i <= n; ++i) b[i] = p[a[i]], p[a[i]] = i+1;
	for(int i = 1; i <= n; ++i) num[b[i]].push_back((opt){ i });
	for(int l, r, x, y, i = 1; i <= m; ++i) {
		l = read(), r = read();
		x = read(), y = read();
		q[l].push_back((opt){ l, r, x, y, i });
	}
	
	t = 0;
	for(int i = 1; i <= n; ++i) wk[++t] = (ele){ 0, i, a[i] };
	for(int i = 1; i <= n; ++i) REP(q[i]) 
		wk[++t] = (ele){ -1, it->l-1, it->a, it->b, it->id },
		wk[++t] = (ele){  1, it->r  , it->a, it->b, it->id };
	sort(wk+1, wk+1+t);
	for(int i = 1; i <= t; ++i) {
		ele &e = wk[i];
		if(!e.type) T.add(e.l);
		else f[e.id] += e.type*(T.query(e.r) - T.query(e.l-1));
	}
	
	solve(1, n);
	for(int i = 1; i <= m; ++i)
		printf("%d %d\n", f[i], g[i]);
	return 0;
}
