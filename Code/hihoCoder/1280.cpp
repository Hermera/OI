#include <ctime>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 45;
const int S = 11e5;

struct ele {
    int val;
    ll sum;

	ele() {}
	ele(int x, ll y): val(x), sum(y) {}
} t1[S], t2[S];

inline ele operator +(ele a, ele b) {
    return ele(a.val+b.val, a.sum+b.sum);
}


int counter;
struct LIST {
    int t, m;
    ele s[S];
    ele &operator [](int x) { return s[x]; }
    void push_back(ele x) { s[++t] = x; }

    void clear() { t = m = 0; }
    void getsort() {
        ele *x = t1, *y = t2;
        x[m = 1] = ele(0, 0);
       // printf("%d\n", t);
        for(int i = 1; i <= t; ++i) {
            for(int j = 1; j <= m; ++j) x[j+m] = x[j]+s[i];

            int p1 = 1, p2 = m+1, p3 = 0, k = m<<1;
            while(p1 <= m && p2 <= k)
                if(x[p1].sum < x[p2].sum) y[++p3] = x[p1++];
                else y[++p3] = x[p2++];
            while(p1 <= m) y[++p3] = x[p1++];
            while(p2 <= k) y[++p3] = x[p2++];

			counter += p3;
            swap(x, y), m <<= 1;
        }
        t = m, counter += t;
        for(int i = 1; i <= t; ++i) s[i] = x[i];
    }
} w1, w2;
ele w[N];


int n;
ll a[N], ss[N << 1];
ll *sum = ss + N;

ll work(int l, int r) {
    int t = 0;
    ll mid = (a[l] + a[r]) >> 1;
    for(int i = 1; i < l; ++i) w[++t] = ele(-1, a[i] - mid);
    for(int i = n; i > r; --i) w[++t] = ele( 1, a[i] - mid);

    w1.clear(), w2.clear();
    for(int i = 1; i <= t/2; ++i) w1.push_back(w[i]);
    for(int i = t; i >  t/2; --i) w2.push_back(w[i]);
    w1.getsort();
    w2.getsort();

    ll ret = 0;
    memset(ss, 0, sizeof(ss));
    for(int i = w1.t, j = 1; i; --i) {
        while(j <= w2.t && w1[i].sum+w2[j].sum <= 0) ++sum[w2[j++].val];
        ret += sum[-w1[i].val];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld", a + i), a[i] <<= 1;
    sort(a+1, a+1+n);

    ll ans = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            ans += work(i, j);

//	cerr << counter << endl;
//	cerr << (double)clock() / CLOCKS_PER_SEC << endl;
    printf("%lld\n", ans);
    return 0;
}
