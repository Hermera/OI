#include <cstdio>
#include <queue>
#include <cmath>
#include <functional>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int N, B, Q;
int a[maxn], num[maxn], all[maxn], blg[maxn], t[maxn], tmp[maxn];
ll ans[maxn];
vector <int> G;

struct Query {
	int l, r, id; ll val;
	void init(int i) {
		id = i;
		l = read(), r = read(), val = 0;
	}
	bool operator <(const Query &b) const {
		return blg[l] != blg[b.l] ? blg[l] < blg[b.l] : r < b.r; 
	}
} ask[maxn];

void update(int x, int v) {
	int &o = num[a[x]];
	--t[o], o += v, ++t[o];
}

priority_queue <ll, vector<ll>, greater<ll> > q;
ll solve() {
	ll ret = 0;
	for(int i = 1; i <= B; ++i) tmp[i] = t[i];
	for(int i = 0; i < G.size(); ++i)
		if(num[G[i]] > B) q.push(num[G[i]]);
	
	int pre = 0;
	for(int i = 1; i <= B; ++i) if(tmp[i]) {
		if(pre) {
			int now = pre+i;
			--tmp[i], ret += now, pre = 0;
			if(now > B) q.push(now);
			else ++tmp[now];
		}
		ret += ((tmp[i]>>1)<<1)*i;
		if((i<<1) <= B) tmp[i<<1] += (tmp[i]>>1);
		else for(int j = 1; j <= (tmp[i]>>1); ++j) q.push(i<<1);
		
		if(tmp[i]&1) pre = i;
	}
	
	if(pre) q.push(pre);
	while(!q.empty()) {
		ll x = q.top(); q.pop();
		if(q.empty()) break;
		x += q.top(); q.pop();
		ret += x;
		q.push(x);
	}
	return ret;
}

int main() {
	N = read(), B = sqrt(N);
	for(int i = 1; i <= N; ++i) 
		a[i] = read(), ++all[a[i]], blg[i] = (i-1)/B+1;
	for(int i = 1; i < maxn; ++i)
		if(all[i] > B) G.push_back(i);
	
	Q = read();
	for(int i = 1; i <= Q; ++i) ask[i].init(i);
	sort(ask+1, ask+1+Q);
	
	int l = 1, r = 0;
	for(int i = 1; i <= Q; ++i) {
		Query &e = ask[i];
		while(l < e.l) update(l++, -1);
		while(r < e.r) update(++r, 1);
		while(l > e.l) update(--l, 1);
		while(r > e.r) update(r--, -1);
		e.val = solve();
	}
	
	for(int i = 1; i <= Q; ++i) ans[ask[i].id] = ask[i].val;
	for(int i = 1; i <= Q; ++i) printf("%I64d\n", ans[i]);
	return 0;
}
