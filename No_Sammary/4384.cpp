#include <cstdio>
#include <algorithm>
using namespace std;
void cmin(int &x, int y) { x = x > y ? y : x; }
void cmax(int &x, int y) { x = x < y ? y : x; }

struct node {
	int fir, sec, val;
	void upd(int v, int p, int on) {
		if(!on) {
			if(p < fir) {	
				if(v == val) fir = p;
				else sec = fir, fir = p, val = v;
			} else if(v != val) cmin(sec, p);
		} else {
			if(p > fir) {	
				if(v == val) fir = p;
				else sec = fir, fir = p, val = v;
			} else if(v != val) cmax(sec, p);
		}
	}
};


const int maxn = 1e6+5;
const int maxm = maxn << 1;
const int INF = 1e9;

int n, m, ans;
struct BIT2 {
	node t[maxm];
	void clear(int v) {
		for(int i = 0; i <= m; ++i) t[i].fir = t[i].sec = v;
	}
	
	void modify(int x, int v, int p, int on) {
		for(; x <= m; x += x&-x) t[x].upd(v, p, on);
	}
	
	int query(int x, int v, int p, int on) {
		int ret = 0;
		for(; x; x -= x&-x) 
			if(v == t[x].val) cmax(ret, on*(t[x].sec-p));
			else cmax(ret, on*(t[x].fir-p));
		return ret;
	}
} plus, mius;


struct ele {
	int x, y, z, p;
	ele() {}
	ele(int a, int b, int c, int d):
		x(a), y(b), z(c), p(d) {}
	bool operator <(const ele &b) const {
		return x < b.x;
	}
} pos[maxn];

void solve(int l, int r) {
	for(int i = l; i <= r; ++i) 
		cmax(ans, plus.query(pos[i].y-1, pos[i].z, pos[i].p, -1)),
		cmax(ans, mius.query(pos[i].y-1, pos[i].z, pos[i].p,  1));
	for(int i = l; i <= r; ++i)
		plus.modify(pos[i].y, pos[i].z, pos[i].p, 0),
		mius.modify(pos[i].y, pos[i].z, pos[i].p, 1);		
}

void getans() {
	plus.clear( INF);
	mius.clear(-INF);
	int l = 0, r = 0;
	for(; r <= n; ++r) 
		if(pos[l].x != pos[r].x) 
			solve(l, r-1), l = r;
	solve(l, r-1);
}

char str[maxn];
int s1[maxn], s2[maxn], s3[maxn], last;

int main() {
	scanf("%d%s", &n, str + 1);
	for(int i = 1; i <= n; ++i) {
		s1[i] = s1[i-1] + (str[i] == 'B');
		s2[i] = s2[i-1] + (str[i] == 'C');
		s3[i] = s3[i-1] + (str[i] == 'S');
		if(str[i] == str[i-1]) cmax(ans, ++last);
		else cmax(ans, last = 1);
	}
	
	m = (n+1) << 1;
	for(int i = 0; i <= n; ++i) 
		pos[i] = ele(s1[i]-s2[i], s1[i]-s3[i], s2[i]-s3[i], i);
	for(int i = 0; i <= n; ++i) 
		pos[i].x += n+1, pos[i].y += n+1, pos[i].z += n+1;
	
	sort(pos, pos+1+n);
	getans();
	for(int i = 0; i <= n; ++i) 
		pos[i].y = m - pos[i].y;
	getans();
	
	printf("%d\n", ans);
	return 0;
}
