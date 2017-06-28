//http://s8pc-3.contest.atcoder.jp/tasks/s8pc_3_f
#include <set>
#include <vector>
#include <cstdio>
#include <assert.h>
using namespace std;
typedef long long ll;
inline ll read() {
    char ch = getchar(); ll x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}


const ll INF = 2e13 + 5;
const int N = 1e5+5;

struct seg {
    int l, r;
    ll v;

    seg() {}
    seg(int a, int b, ll c): l(a), r(b), v(c) {}
    bool operator <(const seg &b) const {
        return l < b.l;
    }
};

set <seg> s;
set <seg>:: iterator it;
seg del[N], ins[N];

int t1, t2;
void work() {
    ll y = read(), x = read();
    it = s.upper_bound(seg(y, 0, 0)), --it;
    if(y+1 <= it->r) ins[++t1] = (seg(y+1, it->r, it->v));
    del[++t2] = (*it);

    int nl = it->l, nr = y; ll nv = it->v;
    for(--it; 1LL*(nr-nl+1)*(it->v-nv) < x && it != s.begin();) {
        x -= 1LL*(nr-nl+1)*(it->v-nv);
        del[++t2] = (*it);
        nl = it->l, nv = it->v, --it;
    }

    nv += x / (nr-nl+1);
    x  %= (nr-nl+1), nl = it->r+x+1;
    if(nl <= nr) ins[++t1] = (seg(nl, nr, nv));
    if(it->r < nl-1) ins[++t1] = (seg(it->r+1, nl-1, nv+1));

    for(int i = 1; i <= t2; ++i) s.erase(del[i]);
    for(int i = 1; i <= t1; ++i) s.insert(ins[i]);
    t1 = t2 = 0;
}


int n, q;
int main() {
    freopen("S8PC3F.in", "r", stdin);
    freopen("S8PC3F.out", "w", stdout);

    n = read(), q = read();

    s.insert(seg(0, 0, INF));
    s.insert(seg(1, n, 0));

    while(q--) work();
    for(it = s.begin(), ++it; it != s.end(); ++it)
        for(int j = it->l; j <= it->r; ++j)
            printf("%lld\n", it->v);
    return 0;
}
