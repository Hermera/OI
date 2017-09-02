#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {	
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 50005;
const double INF = 1e20;


struct line {
	double k, b;
	bool empty() { return !k && !b; }
	double val(int x) { return k * x + b; }
} now;

double getITST(line &x, line &y) {
	if(x.k == y.k) return INF;
	return (x.b - y.b) / (y.k - x.k);
}


#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Segment {
	line t[N << 2];
	void modify(int o, int l, int r, line x) {
		if(t[o].empty()) t[o] = x;
		if(t[o].val(l) < x.val(l)) swap(t[o], x);
		
		double pos = getITST(t[o], x);
		if(l == r || pos < l || pos > r) return;
		if(mid < pos) modify(rc, x); 
		else modify(lc, t[o]), t[o] = x;
	}
	
	line query(int o, int l, int r, int p) {
		if(l == r) return t[o];
		line ret = (p <= mid ? query(lc, p) : query(rc, p));
		return ret.val(p) < t[o].val(p) ? t[o] : ret;
	}
} T;


int n;
char op[10];
ll query(int x) {
	line ret = T.query(1, 1, n, x);
	return (ll)(ret.val(x)/100);
}

int main() {
	n = 50000;
	for(int i = read(); i; --i) {
		scanf("%s", op);
		if(*op == 'Q') printf("%lld\n", query(read()));
		else {
			scanf("%lf%lf", &now.b, &now.k);
			now.b -= now.k, T.modify(1, 1, n, now);
		}
	}
	return 0;
}
