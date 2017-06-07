#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int, int> Pi;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
int n, q, cnt, tim, ans[maxn], L[maxn];
set <Pi> s[maxn];
struct ele {
	int x, y, id;
	ele(int _x = 0, int _y = 0, int _id = 0): x(_x), y(_y), id(_id) {}
	bool operator <(const ele &b) const {
		return x > b.x;
	}
} a[maxn], b[maxn], c[maxn], stu[maxn];

int lower(int x) {
	int l = 1, r = cnt, ans = -1;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(L[mid] <= x) ans = mid, l = mid+1;
		else r = mid-1;
	}
	return ans;
}

int merge(int x, int y) {
	if(!x || !y) return x|y;
	if(stu[x].y == stu[y].y) return stu[x].x < stu[y].x ? x : y; 
	else return stu[x].y < stu[y].y ? x : y;
}

struct BIT {
	int p[maxn], t[maxn];
	void add(int x, int y) {
		for(; x <= n; x += x&-x)
			if(p[x] < tim) p[x] = tim, t[x] = y;
			else t[x] = merge(t[x], y);
	}
	
	int query(int x) {
		int ret = 0;
		for(; x; x -= x&-x) 
			if(p[x] == tim) ret = merge(ret, t[x]);
		return ret;
	}
} T;

void solve(int l, int r) {
	if(l == r) return;
	int mid = (l+r)>>1, t1 = 0, t2 = 0;
	solve(l, mid);
	solve(mid+1, r);
	
	for(int i = l; i <= mid; ++i) if(a[i].id < 0) b[t1++] = a[i];
	for(int i = r; i >  mid; --i) if(a[i].id > 0) c[t2++] = a[i];
	if(!t2) return;
	
	++tim;
	sort(b, b+t1);
	sort(c, c+t2);
	for(int i = 0, j = 0; i < t2; ++i) {
		while(j < t1 && b[j].x >= c[i].x) T.add(b[j].y, -b[j].id), ++j;
		ans[c[i].id] = merge(ans[c[i].id], T.query(c[i].y-1));
	}
}	

char op[3];
int main() {
	n = read();
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%s", op), x = read();
		if(*op == 'D') {
			L[++cnt] = y = read();
			stu[cnt] = a[i] = ele(x, y, -cnt);
		} 
		else a[i] = stu[x], a[i].id = ++q;
	}
	
	sort(L+1, L+1+cnt);
	for(int i = 1; i <= n; ++i) {
		ele &e = a[i];
		e.y = cnt-lower(e.y)+1;
		if(e.id < 0) s[e.y].insert(Pi(e.x, -e.id));
		else {
			set <Pi>:: iterator it = s[e.y].lower_bound(Pi(e.x+1, 0));
			if(it != s[e.y].end()) ans[e.id] = it->second;
		}
	}
	
	solve(1, n);
	for(int i = 1; i <= q; ++i)
		if(!ans[i]) printf("NE\n");
		else printf("%d\n", ans[i]);
	return 0;
}
