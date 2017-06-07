#include <cstdio>
#include <bitset>
using namespace std;
typedef long long ll;
inline ll read() {
	char ch = getchar(); ll x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxl = 64;
ll a[maxn], sum;
int d[maxl], ans[maxn], now, N;
bitset <maxn> r[maxl];

int main() {
	N = read();
	for(int i = 0; i < N; ++i) a[i] = read(), sum ^= a[i];
	for(int i = maxl-1; ~i; --i) 
		if(!(sum&(1LL<<i))) {
			for(int j = 0; j < N; ++j) r[now][j] = (a[j]&(1LL<<i));
			++now;
		}
		
	for(int i = maxl-1; ~i; --i) 
		if((sum&(1LL<<i))) {
			for(int j = 0; j < N; ++j) r[now][j] = (a[j]&(1LL<<i));
			++now;
		}
		
	for(int i = 0; i < now; ++i) {
		r[i][N] = 1;
		for(int j = 0; j < i; ++j)
			if(d[j] != N && r[i][d[j]]) r[i] ^= r[j];
		while(!r[i][d[i]] && d[i] < N) ++d[i];
		if(d[i] != N)
			for(int j = 0; j < i; ++j)
				if(r[j][d[i]]) r[j] ^= r[i];
	}
	
	for(int i = 0; i < now; ++i) 
		if(d[i] != N) 
			ans[d[i]] = (bool)r[i][N];
	
	for(int i = 0; i < N; ++i) 
	if(i != N-1) printf("%d ", ans[i]+1);
	else printf("%d\n", ans[i]+1);
	return 0;
}
