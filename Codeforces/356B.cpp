#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5, size = 26;
ll N, M, Ls, Lt, G;
ll ans, d1[size], d2[size];
char s[maxn], t[maxn];

ll gcd(ll x, ll y) { return !y ? x : gcd(y, x%y); }
ll lcm(ll x, ll y) { return x*y/G; }

int main() {
	scanf("%I64d%I64d%s%s", &N, &M, s, t);
	Ls = strlen(s), Lt = strlen(t);
	G = gcd(Ls, Lt);
	
	for(int i = 0; i < G; ++i) {
		memset(d1, 0, sizeof(d1));
		memset(d2, 0, sizeof(d2));
		for(int j = i; j < Ls; j += G) ++d1[s[j]-'a'];
		for(int j = i; j < Lt; j += G) ++d2[t[j]-'a'];
		for(int j = 0; j < 26; ++j) ans += d1[j]*d2[j];
	}
	
	printf("%I64d\n", Ls*N - Ls*N/lcm(Ls, Lt)*ans);
	return 0;
}
	
