#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 5e4+5, Mod = 1e9+7;
int N, M, a[maxn];

int main() {
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	sort(a+1, a+1+N);
	
	int ans = 0;
	for(int k = 29; ~k; --k) {
		map <int, int> cnt;
		for(int i = 1; i <= N; ++i) ++cnt[a[i]>>k];
		
		ans <<= 1;
		int tot = 0;
		for(map <int, int> ::iterator it = cnt.begin(); it != cnt.end(); ++it) {
			int u = it->first, v = u^(ans+1);
			if(u < v) tot += (long long)it->second*cnt[v];
		}
		
		if(tot >= M) ++ans;
		else M -= tot;
	}
	
	long long ret = 0;
	for(int i = 1; i <= N; ++i)
	for(int j = i+1; j <= N; ++j)
		if((a[i]^a[j]) > ans) ret += a[i]^a[j];
	
	(ret += (long long)M*ans) %= Mod;
	printf("%I64d\n", ret);
	return 0;
}
