#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 1e7+5;
const int mod = 1e9+7;

bool vis[maxn];
int cnt, p[maxn], num[maxn], gen[maxn], las[maxn];
ll sum[maxn];

void work() {
	gen[1] = sum[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!vis[i]) {
			p[++cnt] = i;
			num[i] = 1;
			gen[i] = 2;
			las[i] = 1;
			sum[i] = (1 + 1LL*i*i) % mod;
		}
		
		for(int x, j = 1; j <= cnt; ++j) {
			if((x = i*p[j]) >= maxn) break;
			vis[x] = 1;
			if(i % p[j]) {
				num[x] = 1;
				las[x] = i;
				gen[x] = gen[i] * 2;
				sum[x] = (sum[i]*p[j]%mod*p[j] + sum[i]) % mod;
			} else {
				num[x] = num[i]+1;
				las[x] = las[i];
				gen[x] = gen[i] * (num[x]+1) / num[x];
				sum[x] = (sum[i]*p[j]%mod*p[j] + sum[las[x]]) % mod;
				break;
			}
		}
	}
}

int q, Q, A, B, C, ans1, ans2;
int main() {
	work();
	
	scanf("%d", &q);
	scanf("%d%d%d%d", &Q, &A, &B, &C);
	while(q--) {
		(ans1 += gen[Q] + (Q&1)) %= mod;
		(ans2 += sum[Q] + 4*(Q&1)) %= mod;
		Q = (1LL*Q*A + B) % C + 1;
	}
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}
