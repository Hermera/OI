#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int n, m;
struct ele {
	int pos, val, type;
	bool operator <(const ele &b) const {
		if(pos != b.pos) return pos < b.pos;
		if(type != b.type) return type > b.type;
		return val > b.val; 
	}
} op[maxn];
multiset <int, greater<int> > s;

int main() {
	n = read();
	for(int i = 1, a, b, k; i <= n; ++i) {
		a = read(), b = read(), k = read();
		op[++m] = (ele){ a, k, 1 };
		op[++m] = (ele){ b, k, 0 };
	}
	
	long long ans = 0;
	sort(op+1, op+1+m);
	for(int i = 1; i <= m; ++i) {
		ele &now = op[i], &pre = op[i-1];
		if(!s.empty()) ans += 1LL*(*s.begin())*(now.pos-pre.pos);
		if(now.type) s.insert(now.val);
		else s.erase(s.find(now.val));
	}
	printf("%lld\n", ans);
	return 0;
}
