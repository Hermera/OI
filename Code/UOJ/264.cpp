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
const int maxm = 8e6+5;
const int INF = 2e9;

struct Queue {
	int h, t, a[maxm];
	void init() { h = 1, t = 0; }
	void pop() { ++h; }
	void push(int x) { a[++t] = x; }
	int front() {
		if(h > t) return -INF;
		return a[h];
	}	
} q1, q2, q3;
ll sum;
int b[maxn], n, m, q, u, v, t;

int done(bool o) {
	int x = max(q1.front(), max(q2.front(), q3.front()));
	if(q1.front() == x) q1.pop();
	else if(q2.front() == x) q2.pop();
	else if(q3.front() == x) q3.pop();
	if(!o) printf("%lld ", x+sum);
	return x;
}

int main() {
	n = read(), m = read(), q = read();
	u = read(), v = read(), t = read();
	q1.init(), q2.init(), q3.init();
	for(int i = 1; i <= n; ++i) b[i] = read();
	sort(b+1, b+1+n);
	for(int i = n; i; --i) q1.push(b[i]);
	for(int i = 1, x; i <= m; ++i) {
		x = done((i%t))+sum, sum += q;
		q2.push(1LL*x*u/v - i*q);
		q3.push((x - 1LL*x*u/v) - i*q);
	}
	
	printf("\n");
	for(int i = 1; i <= n+m; ++i) done((i%t));
	printf("\n");
	return 0;
}
