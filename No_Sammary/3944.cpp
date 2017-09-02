#include <cstdio>
using namespace std;
typedef long long ll;

const int N = 3e6+5;
const int LIM = 3e6;

int n, cnt, cas, pri[N], mob[N], mts[N];
ll phi[N], etf[N];

void getprime() {
	n = LIM;
	phi[1] = mob[1] = 1;
	for(int i = 2; i <= LIM; ++i) {
		if(!phi[i]) phi[i] = i-1, mob[i] = -1, pri[++cnt] = i;
		for(int j = 1; j <= cnt && i * pri[j] <= LIM; ++j) {
			int now = i * pri[j];
			if(i % pri[j]) {
				phi[now] = phi[i] * (pri[j]-1);
				mob[now] = -mob[i];
			} else {
				phi[now] = phi[i] * pri[j];
				mob[now] = 0;
				break;
			}
		}
	}
	
	for(int i = 2; i <= LIM; ++i) {
		phi[i] += phi[i-1];
		mob[i] += mob[i-1];
	}	
}


#define getetf(x) (x <= LIM ? phi[x] : etf[n/(x)])
#define getmts(x) (x <= LIM ? mob[x] : mts[n/(x)])

int vis[N], tim;
void solve(int x) {
	if(x <= LIM) return;
	if(vis[n/x] == tim) return;
	
	int t = n/x;
	vis[t] = tim;
	etf[t] = (1LL*x + 1) * x >> 1;
	mts[t] = 1;
	for(unsigned int l = 2, r; l <= x; l = r+1) {
		r = x / (x / l), solve(x/l);
		etf[t] -= getetf(x/l) * (r-l+1);
		mts[t] -= getmts(x/l) * (r-l+1);
	}
} 
/*  all the x is n/t
	so you needn't use map: you can store it in pos (n/t)
*/


int main() {
	getprime();
	
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d", &n), ++tim;
		if(n <= LIM) printf("%lld %d\n", phi[n], mob[n]);
		else {
			solve(n);
			printf("%lld %d\n", etf[1], mts[1]);
		}
	}
	return 0;
}
