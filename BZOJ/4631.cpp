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
int N, M, Q, ans, last, a[maxn], nxt[maxn], pre[maxn], c[maxn];
struct Seg { 
	int l, r;
	bool operator <(const Seg &b) const {
		return r < b.r;
	}
} b[maxn];

struct Segment {
	#define mid (l+r>>1)
	#define lc o<<1, l, mid
	#define rc o<<1|1, mid+1, r
	int t[maxn<<2];
	int merge(int x, int y) { return b[x].l > b[y].l ? x : y; }
	void build(int o, int l, int r) {
		if(l == r) t[o] = l;
		else build(lc), build(rc), t[o] = merge(t[o<<1], t[o<<1|1]);
	}
	
	void modify(int o, int l, int r, int p) {
		if(l == r) {
			t[o] = 0; return;
		}
		if(p <= mid) modify(lc, p);
		else modify(rc, p);
		t[o] = merge(t[o<<1], t[o<<1|1]);
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[o];
		if(R < l || r < L) return 0;
		return merge(query(lc, L, R), query(rc, L, R));
	}
} T;

void remove(int x) {
	if(--a[x]) return;
	nxt[pre[x]] = nxt[x];
	pre[nxt[x]] = pre[x];
	
	int t, len = c[nxt[x]-1];
	if(!len) return;
	while(b[t = T.query(1, 1, M, 1, len)].l > pre[x]) 
		++ans, T.modify(1, 1, M, t);
}

int main() {
	freopen("4631.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1; i <= N; ++i) pre[i] = i-1, nxt[i] = i+1;
	
	for(int i = 1; i <= M; ++i) b[i].l = read(), b[i].r = read();
	sort(b+1, b+1+M);
	for(int i = 1; i <= M; ++i)
		if(b[i].r != b[i-1].r) 
			for(int j = b[i-1].r; j < b[i].r; ++j) c[j] = i-1;
	for(int i = b[M].r; i <= N; ++i) c[i] = M;
	
	Q = read();
	T.build(1, 1, M);
	while(Q--) remove((read()+last-1)%N+1), printf("%d\n", last = ans);
	return 0;
}
	
