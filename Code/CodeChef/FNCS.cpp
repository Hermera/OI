#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
typedef unsigned long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
int n, m, q, a[maxn], l[maxn], r[maxn], sum[maxn], blo[maxn];
ll ans[maxn], fs[maxn], vs[maxn];

struct ele {
	int t, pos, val;
	ele() {}
	ele(int o, int p, int v): t(o), pos(p), val(v) {}
};
vector <ele> wait[maxn], lazy;

ll query(int x) { return sum[x] + blo[x/m]; }
void add(int x, int w) {
	for(int i = x/m+1; i <= n/m;  ++i) blo[i] += w;
	for(int i = x; i < (x/m+1)*m; ++i) sum[i] += w;
}

int main() {
	n = read(), m = sqrt(n);
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) l[i] = read()-1, r[i] = read();
	for(int i = 1; i <= n; ++i) vs[i] = vs[i-1] + a[i];
	for(int i = 1; i <= n; ++i) fs[i] = fs[i-1] + (vs[r[i]] - vs[l[i]]);
	
	q = read();
	for(int op, x, y, t = 1; t <= q; ++t) {
		op = read(), x = read(), y = read();
		if(!(t % m)) {
			lazy.clear();
			for(int i = 1; i <= n; ++i) vs[i] = vs[i-1] + a[i];
			for(int i = 1; i <= n; ++i) fs[i] = fs[i-1] + (vs[r[i]] - vs[l[i]]);
		}
		
		if(op == 2) {
			ans[t] = fs[y] - fs[--x];
			for(int i = 0; i < lazy.size(); ++i)
				wait[x].push_back(ele(t, lazy[i].pos, -lazy[i].val)),
				wait[y].push_back(ele(t, lazy[i].pos, lazy[i].val));
		} else lazy.push_back(ele(0, x, y - a[x])), a[x] = y;
	}
	
	for(int i = 1; i <= n; ++i) {
		add(l[i]+1, 1);
		add(r[i]+1, -1);
		for(int j = 0; j < wait[i].size(); ++j)
			ans[wait[i][j].t] += query(wait[i][j].pos) * wait[i][j].val;
	}
	for(int i = 1; i <= q; ++i)
		if(ans[i]) printf("%llu\n", ans[i]);
	return 0;
}
