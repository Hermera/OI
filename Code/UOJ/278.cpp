<<<<<<< a2824b917e289d5fe1d2fa5151a17a549f4561fb
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;
int n, a[maxn], f[maxn], p[maxn];

bool cmp(int x, int y) {
    if(f[x] != f[y]) return f[x] < f[y];
    return x > y;
}

int main() {
    freopen("278.in", "r", stdin);

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", f+i);
    for(int i = 1; i <= n; ++i) p[i] = i;
    sort(p+1, p+1+n, cmp);
    for(int i = 1; i <= n; ++i) a[p[i]] = i;
    for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
=======
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;
int n, a[maxn], f[maxn], p[maxn];

bool cmp(int x, int y) {
    if(f[x] != f[y]) return f[x] < f[y];
    return x > y;
}

int main() {
    freopen("278.in", "r", stdin);

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", f+i);
    for(int i = 1; i <= n; ++i) p[i] = i;
    sort(p+1, p+1+n, cmp);
    for(int i = 1; i <= n; ++i) a[p[i]] = i;
    for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
>>>>>>> merge
