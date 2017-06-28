#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 25;
const int S1 = 5e6+5;
const int S2 = 2e6+5;
int n, m, k1, k2, a[N];

struct ele {
    int val, sta;

    ele() {}
    ele(int v, int s): val(v), sta(s) {}
    bool operator <(const ele &b) const {
        return val < b.val;
    }
} q2[S2];

int nx[S1], hd[S1], to[S1], q1[S1], cnt;
void add(int sta, int val) {
    nx[++cnt] = hd[sta], to[cnt] = val, hd[sta] = cnt;
}


void dfs1(int las, int sum, int sta) {
    if(las == m) return add(sta, sum);
    dfs1(las+1, sum, sta);
    dfs1(las+1, sum + a[las], sta | (1<<las));
    dfs1(las+1, sum - a[las], sta | (1<<las));
}

void dfs2(int las, int sum, int sta) {
    if(las == n) {
        q2[++k2] = ele(sum, sta);
        return;
    }
    dfs2(las+1, sum, sta);
    dfs2(las+1, sum + a[las], sta | (1<<las));
    dfs2(las+1, sum - a[las], sta | (1<<las));
}

bool vis[S2];
int main() {
    scanf("%d", &n);
    m = (n+1)>>1;
    for(int i = 0; i < n; ++i) scanf("%d", a + i);

    dfs1(0, 0, 0);
    dfs2(m, 0, 0);
    sort(q2+1, q2+k2+1);
    for(int s = 0; s < (1<<m); ++s) {
        k1 = 0;
        for(int i = hd[s]; i; i = nx[i]) q1[++k1] = to[i];
        sort(q1+1, q1+k1+1);
        for(int i = 1, j = 1; i <= k2; ++i) {
            while(j <= k1 && q1[j] < q2[i].val) ++j;
            if(j > k1) break;
            if(q2[i].val == q1[j]) vis[s | q2[i].sta] = 1;
        }
    }

    int ans = 0;
    for(int i = 1; i < (1<<n); ++i)
        if(vis[i]) ++ans;
    printf("%d\n", ans);
    return 0;
}
