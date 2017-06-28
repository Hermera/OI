#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1e5+5;

int n;
char s[N];
namespace SuffixArray {
    int t1[N], t2[N], c[N];
    int sa[N], rk[N], hi[N];

    void build(int n, int m) {
        int *x = t1, *y = t2, i, j, k;
        for(i = 1; i <= m; ++i) c[i] = 0;
        for(i = 1; i <= n; ++i) ++c[x[i] = s[i]];
        for(i = 2; i <= m; ++i) c[i] += c[i-1];
        for(i = n; i; --i) sa[c[x[i]]--] = i;
        for(k = 1; k <= n; k <<= 1) {
            j = 0;
            for(i = 1; i <= n; ++i) if(sa[i]+k > n) y[++j] = sa[i];
            for(i = 1; i <= n; ++i) if(sa[i]-k > 0) y[++j] = sa[i]-k;
            for(i = 1; i <= m; ++i) c[i] = 0;
            for(i = 1; i <= n; ++i) ++c[x[y[i]]];
            for(i = 2; i <= m; ++i) c[i] += c[i-1];
            for(i = n; i; --i) sa[c[x[y[i]]]--] = y[i]; //!

            swap(x, y);
            j = x[sa[1]] = 1;
            for(i = 2; i <= n; ++i)
                if(y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]) x[sa[i]] = j;
                else x[sa[i]] = ++j;
            if(j == n) break;
            m = j;
        }

        k = 0;
        for(i = 1; i <= n; ++i) rk[sa[i]] = i;
        for(i = 1; i <= n; ++i) if(rk[i] > 1) {
            if(k) --k;
            j = sa[rk[i]-1];
            while(s[j+k] == s[i+k]) ++k;
            hi[rk[i]] = k;
        }
    }

    void print() {
        for(int i = 1; i <= n; ++i) printf("%d ", sa[i]); puts("");
        for(int i = 2; i <= n; ++i) printf("%d ", hi[i]); puts("");
    }
}

int main() {
    freopen("35.in", "r", stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    SuffixArray::build(n, 130);
    SuffixArray::print();
    return 0;
}
