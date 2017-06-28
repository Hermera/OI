#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
ll read() {
	char ch = getchar(); ll x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


struct Node {
	ll val; int tot;
	bool operator +=(const Node &b) {
		tot = max(tot, b.tot);
		val += b.val;
	}
	
	bool operator <(const Node &b) const {
		return val != b.val ? val > b.val : tot > b.tot;
	}
};
ll sum;
int n, k, cnt;
priority_queue <Node> q;

int work() {
	while(!q.empty()) {
		Node v = q.top(); q.pop();
		for(int i = 1; i < k; ++i) {
			if(q.empty()) return v.tot;
			v += q.top(), q.pop();
		}
		++v.tot, sum += v.val, q.push(v);
	}
}

int main() {
	n = read(), k = read();
	for(int i = 1; i <= n; ++i) q.push((Node){ read(), 0 });
	if(n == 1) return printf("%lld 1\n", q.top().val);
	while(k != 2 && n%(k-1) != 1) q.push((Node){ 0, 0 }), ++n;
	
	cnt = work();
	printf("%lld\n%d\n", sum, cnt);
	return 0;
}
