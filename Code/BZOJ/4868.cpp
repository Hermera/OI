#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int N = 1e5+5;
const ll LIM = 1e10;
const ll INF = 1e18;

struct ele {
    ll tot, sum;
    ele() {}
    ele(ll x, ll y): tot(x), sum(y) {}
    void update(int v) {
        tot += 1;
        sum += v;
    }
} stu[N], gra[N];
ele operator +(ele a, ele b) { return ele(a.tot+b.tot, a.sum+b.sum); }
ele operator -(ele a, ele b) { return ele(a.tot-b.tot, a.sum-b.sum); }

ll A, B, C;
int tim[N], dis[N];
int n, m, mn, mx;

int main() {
    scanf("%lld%lld%lld", &A, &B, &C);

    n = read(), m = read();
    for(int i = 1; i <= n; ++i) tim[i] = read();
    for(int i = 1; i <= m; ++i) dis[i] = read();

    mx = 0;
    mn = N;
    for(int i = 1; i <= m; ++i) mx = max(mx, dis[i]);
    for(int i = 1; i <= n; ++i) {
        mx = max(mx, tim[i]);
        mn = min(mn, tim[i]);
    }

    if(C >= LIM) {
        ll need = 0, help = 0;
        for(int i = 1; i <= m; ++i)
            if(dis[i] < mn) help += mn - dis[i];
            else need += dis[i] - mn;

        ll ans = 0;
        if(A < B) {
            ll change = min(need, help);
            ans += change * A, need -= change;
        }
        ans += need * B;
        printf("%lld\n", ans);

    } else {
        for(int i = 1; i <= n; ++i) stu[tim[i]].update(tim[i]);
        for(int i = 1; i <= m; ++i) gra[dis[i]].update(dis[i]);
        for(int i = 1; i <= mx; ++i) stu[i] = stu[i] + stu[i-1];
        for(int i = 1; i <= mx; ++i) gra[i] = gra[i] + gra[i-1];

        ll ans = INF;
        for(int i = 1; i <= mx; ++i) {
            ll pregra = gra[i].tot * i - gra[i].sum;
            ll prestu = stu[i].tot * i - stu[i].sum;
            ll sufgra = (gra[mx]-gra[i]).sum - (gra[mx]-gra[i]).tot * i;

            ll ret = 0;
            if(A < B) {
                ll change = min(pregra, sufgra);
                ret += change * A, sufgra -= change;
            }
            ret += sufgra * B;
            ret += prestu * C;
            ans = min(ans, ret);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
