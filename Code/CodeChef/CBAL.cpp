#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

#define mset(x, a) memset(x, a, sizeof(x))
#define mcpy(x, y) memcpy(x, y, sizeof(x))
const int maxn = 1e5+5, maxb = 320;
int N, C, S, tim, blocks;
int h[maxn], belong[maxn], lab[maxn], vis[maxn];
ll f[maxb][maxn][3], ans[maxb][maxb][3], sum[maxn][3], ret[3];
char s[maxn];
struct Block { int l, r; } b[maxb];

void init() {
	scanf("%s", s+1);
	N = strlen(s+1);
	for(int i = 1; i <= N; ++i) h[i] = lab[i] = lab[i-1]^(1<<(s[i]-'a'));
	sort(h, h+1+N);
	C = unique(h, h+1+N)-h;
	for(int i = 0; i <= N; ++i) lab[i] = lower_bound(h, h+C, lab[i])-h;
}

void Update(int x) {
	int label = lab[x];
	if(vis[label] != tim) mset(sum[label], 0), vis[label] = tim;
	ret[0] += sum[label][0];
	ret[1] += abs(sum[label][0]*x - sum[label][1]);
	ret[2] += sum[label][0]*x*x - 2LL*x*sum[label][1] + sum[label][2];
	sum[label][0] += 1;
	sum[label][1] += x;
	sum[label][2] += (ll)x*x;
}
		
	
void Pre_Work() {
	for(int i = 1; i < maxb; ++i) b[i].l = 0;
	S = sqrt(N);
	for(int i = 0, x; i <= N; ++i) {
		x = belong[i] = i/S+1;
		if(!b[x].l) b[x].l = i;
		b[x].r = i;
	}
	
	blocks = belong[N];
	for(int i = 1; i <= blocks; ++i) {
		for(int j = 0; j <= C; ++j)
		for(int k = 0; k < 3; ++k)
			f[i][j][k] = f[i-1][j][k];
			
		for(int j = b[i].l; j <= b[i].r; ++j) {
			int label = lab[j];
			f[i][label][0] += 1;
			f[i][label][1] += j;
			f[i][label][2] += (ll)j*j;
		}
	}
	
	for(int i = 1; i <= blocks; ++i) {
		++tim, mset(ret, 0);
		 for(int j = i; j <= blocks; ++j) {
		 	for(int k = b[j].l; k <= b[j].r; ++k) Update(k);
		 	mcpy(ans[i][j], ret);
		 }
	}	
}

void Do(int st, int ed, int i) {
	int label = lab[i];
	if(vis[label] != tim) {
		vis[label] = tim;
		for(int k = 0; k < 3; ++k) sum[label][k] = f[ed-1][label][k]-f[st][label][k];
	}
	Update(i);
}
	
ll Query(int L, int R, int t) {
	int st = belong[L], ed = belong[R];
	++tim, mcpy(ret, ans[st+1][ed-1]);
	
	if(ed-st <= 1) for(int i = L; i <= R; ++i) Update(i);
	else {
		for(int i = b[st].r; i >= L; --i) Do(st, ed, i);
		for(int i = b[ed].l; i <= R; ++i) Do(st, ed, i);
	}
	return ret[t];
}
	
void Work() {
	ll A = 0, B = 0, Q = read();
	for(int i = 1, l, r; i <= Q; ++i) {
		l = (read()+A)%N+1, r = (read()+B)%N+1;
		if(l > r) swap(l, r);
		A = B;
		printf("%lld\n", B = Query(l-1, r, read()));
	}
}

int main() {
	for(int T = read(); T; --T) 
		init(), Pre_Work(), Work();
	return 0;
}	
