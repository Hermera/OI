#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 11, Mod = 1e9+7;
int N;
struct Permu {
	int a[maxn];
	inline int hash() {
		ll ret = 0;
		for(int i = 0; i <= N; ++i) ret = ret*28+a[i];
		return ret;
	}
} start, end;
map <ll, ll> M;

ll dfs(int step, Permu now) {
	if(now.a[0] == 1) return M[now.hash()];
	int fir = N-now.a[0]+1;
	if(now.a[fir] > 3*(N-step+1)) return 0;
	if(step > N) {
		--now.a[0];
		sort(now.a+N-now.a[0]+1, now.a+N+1);
		int sub = now.hash();
		if(M.count(sub)) return M[sub];
		return M[sub] = dfs(N-now.a[0]+2, now);
	}
	
	ll ret = 0;
	if(now.a[fir] >= 3) {
		now.a[fir] -= 3;
		(ret += dfs(step+1, now))%= Mod;
		now.a[fir] += 3;
	}
	
	if(now.a[fir] >= 1 && now.a[step] >= 1) {
		--now.a[fir], --now.a[step];
		(ret += dfs(step+1, now))%= Mod;
		++now.a[fir], ++now.a[step];
	}
	
	if(now.a[step] >= 3) {
		now.a[step] -= 3;
		(ret += dfs(step+1, now))%= Mod;
		now.a[step] += 3;
	}
	return ret;
}

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) scanf("%d", &start.a[i]);
	start.a[0] = N;
	end.a[0] = 1;
	M[end.hash()] = 1;
	printf("%lld\n", dfs(2, start));
	return 0;
}
