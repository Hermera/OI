#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long ll;
int gcd(int x, int y) { return !y ? x : gcd(y, x%y); }

const int maxn = 2005;
const int mod = 1e9+7;

struct node {
	int a, b;
	bool po;
	
	node() {}
	node(bool p, int x, int y): po(p), a(x), b(y) {}
	
	bool operator <(const node &x) const {
		if(po != x.po) return po < x.po;
		if(po) return 1LL*a*x.b > 1LL*x.a*b;
		else return 1LL*a*x.b < 1LL*x.a*b;
	}
	
	void print() {
		if(!po) printf("-");
		if(b%a) printf("%d/%d\n", b, a);
		else printf("%d\n", b/a);
	}
} ans[maxn];

int n, p, tot, a[maxn], k1, k2, c1[maxn], c2[maxn];
ll px[maxn], py[maxn];

void getgene(int *c, int &k, int x) {
	x = abs(x);
	for(int i = 1; i*i <= x; ++i) 
		if(x%i == 0) {
			c[++k] = i;
			if(i != x/i) c[++k] = x/i;
		}
}


bool check(bool po, ll x, ll y) {
	px[0] = py[0] = 1;
	for(int i = 1; i <= n; ++i)
		px[i] = px[i-1] * x % mod,
		py[i] = py[i-1] * y % mod;
	
	ll ret = 0, sum = 0;
	for(int i = 0; i <= n; ++i) {
		ret = a[i] * py[i] % mod * px[n-i] % mod;
		if(!po && (i&1)) (sum -= ret)%= mod;
		else (sum += ret)%= mod;
	}
	return !sum;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i) scanf("%d", a+i);
	while(!a[p]) ++p; 
	if(p) {
		n -= p, ans[++tot] = node(1, 1, 0);
		for(int i = 0; i <= n; ++i) a[i] = a[i+p];
	}
	
	getgene(c1, k1, a[0]);
	getgene(c2, k2, a[n]);
	for(int i = 1; i <= k2; ++i)
	for(int j = 1; j <= k1; ++j) {
		int x = c2[i], y = c1[j];
		if(gcd(x, y) == 1) {
			if(check(1, x, y)) ans[++tot] = node(1, x, y);
			if(check(0, x, y)) ans[++tot] = node(0, x, y);
		}
	}
	
	sort(ans+1, ans+tot+1);
	printf("%d\n", tot);
	for(int i = 1; i <= tot; ++i) ans[i].print();
	return 0;
}
