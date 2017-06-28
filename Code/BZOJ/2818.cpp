#include <cstdio>
using namespace std;
const int maxn = 1e7+5;
typedef long long ll;
int N, cnt, p[maxn], phi[maxn];
ll num[maxn];
bool vis[maxn];
 
void GetPhi() {
    for(int i = 2; i <= N; ++i) {
        if(!vis[i]) p[++cnt] = i, phi[i] = i-1;
        for(int j = 1; j <= cnt && i*p[j] <= N; ++j) {
            vis[i*p[j]] = true;
            if(i%p[j] == 0) {
            	phi[i*p[j]] = phi[i]*p[j];
            	break;
            }
			phi[i*p[j]] = phi[i]*(p[j]-1);
        }
    }
}
 
ll solve() {
	ll ans = 0;
	num[1] = 1;
	for(int i = 2; i <= N; ++i)
		num[i] = num[i-1] + 2*phi[i];
	for(int i = 1; i <= cnt; ++i)
		if(N/p[i] > 0) ans += num[N/p[i]];
	return ans;
}
 
int main() {
    scanf("%d", &N);
    GetPhi();
    printf("%lld\n", solve());
    return 0;
}
