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

const int maxn = 2e5+5, inf = 1e9;
int N, M = 200000, a[maxn], id[maxn], L1[maxn], L2[maxn], R1[maxn], R2[maxn];
ll h[maxn], ans;

struct Segment {
	#define mid ((l+r)>>1)
	#define lc o<<1, l, mid
	#define rc o<<1|1, mid+1, r

	struct Tree {
		int mn, sn, cnt, tag;
		ll sum;
	} t[maxn<<2];
	
	void build(int o, int l, int r) {
		if(l == r) t[o].mn = t[o].sum = l, t[o].cnt = 1, t[o].sn = inf;
		else build(lc), build(rc), pushup(o);
	}
	
	void pushup(int o) {
		int ls = o<<1, rs = o<<1|1;
		t[o].mn = min(t[ls].mn, t[rs].mn);
		
		t[o].cnt = 0;	
		if(t[ls].mn == t[o].mn) t[o].cnt += t[ls].cnt;
		if(t[rs].mn == t[o].mn) t[o].cnt += t[rs].cnt;
		
		if(t[ls].mn != t[rs].mn) 
			if(t[ls].mn < t[rs].mn) t[o].sn = min(t[ls].sn, t[rs].mn);
			else t[o].sn = min(t[ls].mn, t[rs].sn);
		else t[o].sn = min(t[ls].sn, t[rs].sn);
		t[o].sum = t[ls].sum+t[rs].sum;
	}
	
	void pushdown(int o, int l, int r) {
		if(!t[o].tag) return;
		set(lc, t[o].tag), set(rc, t[o].tag);
		t[o].tag = 0;
	}
	
	void set(int o, int l, int r, int x) {
		t[o].tag = max(t[o].tag, x);
		if(t[o].tag >= t[o].sn) {
			modify(lc, l, mid, t[o].tag);
			modify(rc, mid+1, r, t[o].tag);
			pushup(o);
			t[o].tag = 0;
		}
		else if(t[o].tag >= t[o].mn) {
			t[o].sum += 1LL*t[o].cnt*(t[o].tag-t[o].mn);
			t[o].mn = t[o].tag;
		}
	}
	
	void modify(int o, int l, int r, int L, int R, int x) {
		if(r < L || R < l) return;
		if(L <= l && r <= R) return set(o, l, r, x);
		
		pushdown(o, l, r);
		modify(lc, L, R, x);
		modify(rc, L, R, x);
		pushup(o);
	}
	
	ll ans() { return t[1].sum; }
} T;
			

int main() {
	N = read();
	for(int i = 1; i <= N; ++i)
		a[i] = read(), id[a[i]] = i;
	
	for(int i = 1; i <= M; ++i)
	for(int j = i; j <= M; j += i) if(id[j]) {
		if(!L1[i] || L1[i] > id[j]) L2[i] = L1[i], L1[i] = id[j];
		else if(!L2[i] || L2[i] > id[j]) L2[i] = id[j];
		
		if(!R1[i] || R1[i] < id[j]) R2[i] = R1[i], R1[i] = id[j];
		else if(!R2[i] || R2[i] < id[j]) R2[i] = id[j];
	}
	
	T.build(1, 1, N);
	for(int i = M; i; --i) {
		if(L1[i] != R1[i]) {
			T.modify(1, 1, N, 1, L1[i], R2[i]);
			T.modify(1, 1, N, L1[i]+1, L2[i], R1[i]);
			T.modify(1, 1, N, L2[i]+1, N, N+1);
		}
		h[i] = 1LL*N*(N+1) - T.ans();
	}
	for(int i = 1; i < M-1; ++i) ans += 1LL*i*(h[i+1]-h[i]);
	printf("%lld\n", ans);
	return 0;
}
