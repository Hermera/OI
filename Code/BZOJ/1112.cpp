#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
const ll INF = 1e16;

#define fir first
#define sec second
namespace treap {
	struct node {
		node *ls, *rs;
		node() { ls = rs = this; }
		int val, key, siz; ll sum; 
		void update() {
			sum = ls->sum + rs->sum + val;
			siz = ls->siz + rs->siz + 1;
		}
	} *emt = new node(), *root = emt, gen[maxn];
	typedef pair<node*, node*> pi;
	int cnt;
	
	node *newnode(int v) { 
		node *o = gen + (++cnt);
		*o = *emt, o->val = v, o->key = rand();
		return o->update(), o;
	}

	node *merge(node *x, node *y) {
		if(x == emt) return y;
		if(y == emt) return x;
		
		node *o;
		if(x->key < y->key) x->rs = merge(x->rs, y), o = x;
		else y->ls = merge(x, y->ls), o = y;
		return o->update(), o;
	}
	
	pi split(node *o, int k) {
		if(o == emt) return pi(o, o);
		if(o->ls->siz >= k) {
			pi x = split(o->ls, k);
			o->ls = x.sec;
			o->update();
			return x.sec = o, x;
		} else {
			pi x = split(o->rs, k - o->ls->siz - 1);
			o->rs = x.fir;
			o->update();
			return x.fir = o, x;
		}
	}

	int getkth(int v, node *o = root) {
		if(o == emt) return 0;
		if(v < o->val) return getkth(v, o->ls);
		else return getkth(v, o->rs) + o->ls->siz + 1;
	}

	void insert(int v) { 
		int k = getkth(v);
		pi x = split(root, k);
		root = merge(merge(x.fir, newnode(v)), x.sec); 
	}
	
	void remove(int v) {
		int k = getkth(v);
		pi x = split(root, k-1);
		pi y = split(x.sec, 1);
		root = merge(x.fir, y.sec);
	}
}

using namespace treap;
ll solve(int p, int k) {
	ll ret = 0;
	pi x = split(root, k-1);
	pi y = split(x.sec, 1);
	ret += 1LL * x.fir->siz * y.fir->val - x.fir->sum;
	ret += y.sec->sum - 1LL * y.sec->siz * y.fir->val;
	root = merge(x.fir, merge(y.fir, y.sec));
	return ret;
}

int n, k, h[maxn];
ll ans = INF;

int main() {
	n = read(), k = read();
	for(int i = 1; i <= n; ++i) h[i] = read();
	for(int i = 1; i != k; ++i) insert(h[i]);
	for(int i = 1; i <= n-k+1; ++i) {
		insert(h[i+k-1]);
		ans = min(ans, solve(i, k>>1));
		ans = min(ans, solve(i, (k>>1)+1));
		remove(h[i]);
	}
	
	printf("%lld\n", ans);
	return 0;
}
