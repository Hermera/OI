#include <cstdio>
using namespace std;
typedef unsigned long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 2e5+5;
const int B = 233;

int n, m, idx;
int a[N], b[N], c[N], ans;
ll pow[N], tmp, sum;


struct node {
	ll sum; 
	int siz, l, r;
	node *ls, *rs;
	void update() {
		sum = ls->sum * pow[rs->siz] + rs->sum;
		siz = ls->siz + rs->siz;
	}
} t[N << 2], *root;

node *newnode(int l, int r) {
	node *p = t + (++idx);
	return p->l = l, p->r = r, p;
}

#define mid (o->l + o->r>>1)
struct Segment {
	void build(node *&o, int l, int r) {
		o = newnode(l, r);
		if(l == r) return;
		build(o->ls, l, (l+r)>>1);
		build(o->rs, (l+r>>1)+1, r);
	}

	void modify(node *o, int p, int v, int w) {
		if(o->l == o->r) {
			o->sum += v;
			o->siz += w;
			return;
		}
		if(p <= mid) modify(o->ls, p, v, w);
		else modify(o->rs, p, v, w);
		o->update();
	}
} T;


int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= m; ++i) b[i] = read(), c[b[i]] = i;
	
	pow[0] = 1;
	for(int i = 1; i <= m; ++i) pow[i] = pow[i-1] * B;
	for(int i = 1; i <= n; ++i) tmp = tmp * B + a[i];
	for(int i = 1; i <= n; ++i) sum += pow[i-1];
	
	T.build(root, 1, m);
	for(int i = 1; i <= m; ++i) {
		T.modify(root, c[i], i, 1);
		if(i >= n) {
			if(t[1].sum - sum*(i-n) == tmp) ++ans;
			T.modify(root, c[i-n+1], -(i-n+1), -1);
		}
	}
	printf("%d\n", ans);
	return 0;
}
