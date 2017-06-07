#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
inline ll read()
{
    char ch = getchar(); ll sum = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
    return sum;
}
const ll maxn = 1e5+5;
ll N, M, like[maxn], fa[maxn];
ll tree[maxn];
 
void add(ll x, ll v) { while(x <= N) tree[x] += v, x += x&-x; }
ll query(ll x)
{
    ll ans = 0;
    while(x) ans += tree[x], x -= x&-x;
    return ans;
}
 
ll Find(ll x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
 
int main()
{
    //freopen("data.in", "r", stdin);
    N = read();
    for(ll i = 1; i <= N; ++i) 
        like[i] = read(), fa[i] = like[i] <= 1 ? i+1 : i, add(i, like[i]); 
    fa[N+1] = N+1;
    M = read();
    for(ll i = 1; i <= M; ++i)
    {
        ll op = read(), l = read(), r = read();
        if(l > r) swap(l, r);
        if(op == 1) printf("%lld\n", query(r)-query(l-1));
        else
        for(ll j = Find(l); j <= r; j = Find(j+1))
        {
            ll temp = (ll)sqrt(like[j]);
            add(j, temp-like[j]);
            like[j] = temp;
            if(like[j] <= 1) fa[j] = Find(j+1);
        }
    }
    return 0;
}
