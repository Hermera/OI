#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pii;
#define fir first
#define sec second
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 1e5+5;
const ll INF = 1e16;

int h[N], n, cnt;
struct Data {
	int next, to, w;
} g[N << 1];

void add(int x, int y, int w) {
	g[++cnt] = (Data) { h[x], y, w }; h[x] = cnt;
	g[++cnt] = (Data) { h[y], x, w }; h[y] = cnt;
}
	

ll s[N], t[N], dis[N];
int m, c, S, T, tim;
int b[N], q[N], vis[N], pid[N];
pii bfs(int x) {
	int fi = 1, ed = 0;
	q[++ed] = x, dis[x] = 0, pid[x] = ++tim;
	
	pii ret(0, 0);
	while(fi <= ed) {
		int u = q[fi++];
		for(int i = h[u]; i; i = g[i].next) {
			int v = g[i].to;
			if(pid[v] != tim && !vis[v]) {
				dis[v] = dis[u] + g[i].w;
				pid[v] = tim, q[++ed] = v;
				ret = max(ret, pii(dis[v], v));
			}
		}
	}
	return ret;
}

void getpath(int x, int fa) {
	for(int i = h[x], v; i; i = g[i].next)
		if(!vis[v = g[i].to] && v != fa) {
			getpath(v, x);
			if(v == b[m]) {
				b[++m] = x;
				vis[x] = 1;
				s[m] = g[i].w;
				return;
			}
		}
}



inline void cmin(ll &x, ll y) { x = x > y ? y : x; }
inline void cmax(ll &x, ll y) { x = x < y ? y : x; }

int p1[N], p2[N];
bool judge(ll x) {
	ll mn = INF, mx = -INF;
	ll plusR = INF, subsR = INF;
	ll plusL = -INF, subsL = -INF;
	
	for(int i = 1, j = 1; i <= m; ++i) {
		#define u p1[i]
		#define v p2[j]
		for(; j <= m && s[u]+t[u] > x+s[v]-t[v]; ++j) {
			cmin(mn, s[v]-t[v]);
			cmax(mx, s[v]+t[v]);
		}
		
		cmax(plusL, c-x + mx + (s[u]+t[u]));
		cmin(plusR, x-c + mn + (s[u]-t[u]));
		cmax(subsL, c-x - mn + (s[u]+t[u]));
		cmin(subsR, x-c - mx + (s[u]-t[u]));
		#undef u
		#undef v
	}
	
	int l1 = m, r1 = m;
	int l2 = 1, r2 = 1;
	for(int i = 1; i <= m; ++i) {
		while(s[i]+s[l1-1] >= plusL && l1) --l1;
		while(s[i]+s[r1] > plusR && r1) --r1;
		while(s[i]-s[l2] > subsR && l2 <= m) ++l2;
		while(s[i]-s[r2+1] >= subsL && r2 <= m) ++r2;
		
		if(max(l1, l2) <= min(r1, r2))
			return 1;
	}
	return 0;
}



ll getmin() {
	ll fi = 0, se = 0;
	for(int i = 1; i <= m; ++i) {
		if(fi < (t[i]-s[i])) se = fi, fi = t[i]-s[i];
		else if(se < (t[i]-s[i])) se = t[i]-s[i];
	}
	return max(fi + se, min(s[m], (ll)c));
}

bool cmp1(int x, int y) { return s[x]+t[x] < s[y]+t[y]; }
bool cmp2(int x, int y) { return s[x]-t[x] < s[y]-t[y]; }

int main() {
	freopen("298.in", "r", stdin);

	while(scanf("%d%d", &n, &c) != EOF) {
		if(!n && !c) break;
		
		cnt = 0;
		for(int i = 1; i <= n; ++i) h[i] = vis[i] = 0;
		for(int i = 2; i <= n; ++i) {
			int x = read(), y = read(), w = read();
			add(x, y, w);
		}
		
		S = bfs(1).sec;
		T = bfs(S).sec;
		
		b[m = 1] = T;
		getpath(S, 0);
		vis[T] = 1;
		for(int i = 1; i <= m; ++i) {
			s[i] = s[i] + s[i-1];
			t[i] = bfs(b[i]).fir;
		}
		
		for(int i = 1; i <= m; ++i) p1[i] = p2[i] = i;
		sort(p1 + 1, p1 + 1 + m, cmp1);
		sort(p2 + 1, p2 + 1 + m, cmp2);
		
		ll l = getmin(), r = INF, ans = INF;
		while(l <= r) {
			ll mid = (l + r) >> 1;
			if(judge(mid)) ans = mid, r = mid-1;
			else l = mid + 1;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
