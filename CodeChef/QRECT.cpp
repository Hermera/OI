#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5;

struct rect {
	int x1, y1, x2, y2;
	rect() {}
	rect(int a, int b, int c, int d): 
		x1(a), y1(b), x2(c), y2(d) {}
} rec[maxn];
int m, ans[maxn];

struct machine {
	int n, c, h[maxn], no[maxn], opt[maxn], ret[maxn];
	rect obj[maxn];
	
	struct ele {
		int id, pos, l, r, type;
		ele() {}
		ele(int a, int b, int c, int d, int e):
			id(a), pos(b), l(c), r(d), type(e) {}
		bool operator <(const ele &b) {
			return pos != b.pos ? pos < b.pos : type > b.type;
		}
	} f[maxn];
	
	struct BIT {
		int v[maxn], p[maxn], co, tim;
		void add(int x, int w) {
			for(; x <= co; x += x&-x) {
				if(p[x] != tim) p[x] = tim, v[x] = 0;
				v[x] += w;
			}
		}
		
		int query(int x) {
			int tmp = 0;
			for(; x; x -= x&-x) 
				if(p[x] == tim) tmp += v[x];
			return tmp;
		}
	} t1, t2;
	
	
	void insert(rect x, int d, int id = 0) {
		obj[++n] = x, opt[n] = d, no[n] = id;
	}
	
	void push(ele x) { t1.add(x.l, 1), t2.add(x.r, 1);}
	int query(ele x) { return t1.query(x.r) - t2.query(x.l-1); }
	
	void solve(int l, int r) {
		if(l == r) return;
	
		int mid = (l+r)>>1, tot = 0;
		
		++t1.tim, ++t2.tim, tot = 0;
		for(int i = l; i <= mid; ++i) 
			if(opt[i]) f[++tot] = ele(i, 0, obj[i].y1, obj[i].y2, 1);
		for(int i = mid+1; i <= r; ++i) 
			if(!opt[i]) f[++tot] = ele(i, 0, obj[i].y1, obj[i].y2, 0);
		for(int i = 1; i <= tot; ++i) if(f[i].type) push(f[i]);
		for(int i = 1; i <= tot; ++i) if(!f[i].type) ret[f[i].id] += query(f[i]);
		
		++t1.tim, ++t2.tim, tot = 0;
		for(int i = l; i <= mid; ++i) 
			if(opt[i]) f[++tot] = ele(i, obj[i].x2, obj[i].y1, obj[i].y2, 0);
		for(int i = mid+1; i <= r; ++i) 
			if(!opt[i]) f[++tot] = ele(i, obj[i].x1, obj[i].y1, obj[i].y2, 1);
		sort(f+1, f+1+tot);
		for(int i = 1; i <= tot; ++i) {
			if(!f[i].type) push(f[i]);
			else ret[f[i].id] -= query(f[i]);
		}
		
		++t1.tim, ++t2.tim, tot = 0;
		for(int i = l; i <= mid; ++i) 
			if(opt[i]) f[++tot] = ele(i, obj[i].x1, obj[i].y1, obj[i].y2, 1);
		for(int i = mid+1; i <= r; ++i) 
			if(!opt[i]) f[++tot] = ele(i, obj[i].x2, obj[i].y1, obj[i].y2, 0);
		sort(f+1, f+1+tot);
		for(int i = tot; i; --i) {
			if(f[i].type) push(f[i]);
			if(!f[i].type) ret[f[i].id] -= query(f[i]);
		}
		
		solve(l, mid);
		solve(mid+1, r);
	}
	
	void main(int on) {
		if(!n) return;
		for(int i = 1; i <= n; ++i) {
			h[++c] = obj[i].x1, h[++c] = obj[i].x2;
			h[++c] = obj[i].y1, h[++c] = obj[i].y2;
		} 
		
		sort(h+1, h+1+c);
		c = unique(h+1, h+1+c) - h - 1;
		for(int i = 1; i <= n; ++i) {
			rect &e = obj[i];
			e.x1 = lower_bound(h+1, h+1+c, e.x1) - h;
			e.y1 = lower_bound(h+1, h+1+c, e.y1) - h;
			e.x2 = lower_bound(h+1, h+1+c, e.x2) - h;
			e.y2 = lower_bound(h+1, h+1+c, e.y2) - h;
		}
		
		t1.co = t2.co = c;
		solve(1, n);
		for(int i = 1; i <= m; ++i)
			ans[no[i]] += on * ret[i];
	}
} I, D;


int t, is[maxn];
char op[5];

int main() {
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%s", op);
		if(*op == 'D') D.insert(rec[read()], 1);
		else {
			int x1 = read(), y1 = read();
			int x2 = read(), y2 = read();
			if(*op == 'I') {
				rec[++t] = rect(x1, y1, x2, y2);
				I.insert(rec[t], 1);
			} else {
				I.insert(rect(x1, y1, x2, y2), 0, i);
				D.insert(rect(x1, y1, x2, y2), 0, i);
				is[i] = 1;
			}
		}
	}
	
	I.main(1);
	D.main(-1);
	for(int i = 1; i <= m; ++i)
		if(is[i]) printf("%d\n", ans[i]);
	return 0;
}
