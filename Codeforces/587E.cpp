#include <cstdio>
#include <cstring>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5, maxl = 31;
int N, Q, a[maxn], b[maxn];
struct Node {
	int s[maxl];
	void add(int x) {
		for(int i = maxl-1; ~i; --i)
		if(x&(1<<i))
			if(s[i]) x ^= s[i];
			else { s[i] = x; break; }
	}
	int count() {
		int ret = 0;
		for(int i = maxl-1; ~i; --i) if(s[i]) ++ret;
		return ret;
	}
	void insert(Node b) { for(int i = maxl-1; ~i; --i) if(b.s[i]) add(b.s[i]); }
	void clear() { memset(s, 0, sizeof(s)); }
} O;

#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Range_Segment {
	int tree[maxn<<2], lazy[maxn<<2];
	void pushdown(int o) {
		if(!lazy[o]) return;
		lazy[o<<1] ^= lazy[o];
		lazy[o<<1|1] ^= lazy[o];
		lazy[o] = 0;
	}
	
	void build(int o, int l, int r) {
		if(l == r)  tree[o] = a[l];
		else build(lc), build(rc);
	}
	
	void modify(int o, int l, int r, int L, int R, int k) {
		if(L <= l && r <= R) { lazy[o] ^= k; return; }
		if(R < l || r < L) return;
		pushdown(o);
		modify(lc, L, R, k), modify(rc, L, R, k);
	}
	
	int query(int o, int l, int r, int p) {
		if(l == r) return tree[o]^lazy[o];
		pushdown(o);
		if(p <= mid) return query(lc, p);
		else return query(rc, p);
	}
} A;

struct Point_Segment {
	Node tree[maxn<<2];
	void pushup(int o) {
		tree[o].clear();
		tree[o].insert(tree[o<<1]);
		tree[o].insert(tree[o<<1|1]);
	}
	
	void build(int o, int l, int r) {
		if(l == r) tree[o].clear(), tree[o].add(b[l]);
		else build(lc), build(rc), pushup(o);
	}
	
	void modify(int o, int l, int r, int p, int k) {
		if(l == r) { tree[o].clear(), b[l] ^= k, tree[o].add(b[l]); return; }
		if(p <= mid) modify(lc, p, k);
		else modify(rc, p, k);
		pushup(o);
	}
	
	Node query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return tree[o];
		if(R < l || r < L) return O;
		Node ret; ret.clear();
		ret.insert(query(lc, L, R));
		ret.insert(query(rc, L, R));
		return ret;
	}
} B;

int main() {
	N = read(), Q = read();
	for(int i = 1; i <= N; ++i) a[i] = read(), b[i] = a[i-1]^a[i];
	A.build(1, 1, N), B.build(1, 1, N);
	
	while(Q--) {
		int op = read(), l = read(), r = read();
		if(op == 1) {
			int k = read();
			A.modify(1, 1, N, l, r, k);
			B.modify(1, 1, N, l, k);
			if(r != N) B.modify(1, 1, N, r+1, k);
		}
		else {
			Node ret = B.query(1, 1, N, l+1, r);
			ret.add(A.query(1, 1, N, l));
			printf("%d\n", 1<<ret.count());
		}
	}
	return 0;
}
