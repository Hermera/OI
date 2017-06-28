#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e6+5;
int N, M, cnt, u[maxn], v[maxn];
ll a[maxn], b[maxn], ans;

int main() {
	freopen("4264.in", "r", stdin);

	srand(20000909);
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) a[i] = 1LL*rand()*rand()+rand();
	for(int i = 1; i <= M; ++i) {
		u[i] = read(), v[i] = read();
		b[u[i]] ^= a[v[i]];
		b[v[i]] ^= a[u[i]];
	}
	
	for(int i = 1; i <= M; ++i) 
		if((b[u[i]]^a[v[i]]) == (b[v[i]]^a[u[i]])) ++ans;
		
	sort(b+1, b+1+N);
	for(int i = 1; i <= N; ++i) {
		++cnt;
		if(i == N || b[i] != b[i+1]) 
			ans += 1LL*cnt*(cnt-1)>>1, cnt = 0;
	}
	printf("%lld\n", ans);
	return 0;
}
