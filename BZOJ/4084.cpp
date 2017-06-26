#include <set>
#include <map>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
 
const int bin = 29;
const int maxn = 4e6+5;
string s[maxn], t[maxn];
 
int fail[maxn];
char str[maxn];
void getfail(string &a) {
    int len = a.size();
    for(int i = 1; i <= len; ++i) str[i] = a[i-1];
    reverse(str+1, str+1+len);
    for(int i = 2; i <= len; ++i) {
        int j = fail[i-1];
        while(str[j+1] != str[i] && j) j = fail[j];
        fail[i] = str[j+1] == str[i] ? j+1 : 0;
    }
    reverse(str+1, str+1+len);
}
 
 
ll h[maxn], pow[maxn], ans;
ll getval(int a, int b) { return a <= b ? h[b] - h[a-1] * pow[b-a+1] : 0; }
ll getval(int a, int b, int c, int d) {
    return getval(a, b) * pow[d-c+1] + getval(c, d);
}
 
inline int idx(char ch) { return ch - 'a' + 1; }
int n, m, l1, l2;
 
const int siz = 1<<21;
struct HashMap {
    int h[maxn], cnt;
    struct Data {
        int next, num;
        ll to;
    } g[maxn];
     
    void insert(ll x) {
        for(int i = h[x % siz]; i; i = g[i].next)
            if(g[i].to == x) {
                ++g[i].num;
                return;
            }
        g[++cnt] = (Data){ h[x % siz], 1, x }; h[x % siz] = cnt;
    }
     
    int find(ll x) {
        for(int i = h[x % siz]; i; i = g[i].next)
            if(g[i].to == x) return g[i].num;
        return 0;
    }
     
    void clear() {
        for(int i = cnt; i; --i)
            h[g[i].to % siz] = g[i].num = 0;
        cnt = 0;
    }
} sum, vis;
 
 
int main() {
    scanf("%d%d%d%d", &n, &m, &l1, &l2);
    for(int i = 1; i <= n; ++i) cin >> s[i];
    for(int i = 1; i <= m; ++i) cin >> t[i];
    if(l1 < l2) swap(l1, l2), swap(s, t), swap(n, m);
     
    pow[0] = 1;
    for(int i = 1; i <= l1; ++i) pow[i] = pow[i-1] * bin;
    for(int i = 1; i <= m; ++i) {
        ll val = 0;
        for(int j = 0; j < l2; ++j) (val *= bin) += idx(t[i][j]);
        sum.insert(val);
    }
     
    int rem = (l1 - l2)>>1;
    for(int i = 1; i <= n; ++i) {
        vis.clear(), getfail(s[i]);
        for(int j = 1; j <= l1; ++j) h[j] = h[j-1] * bin + idx(str[j]);
        for(int j = rem+1; j <= l1; ++j)
            if(fail[j] >= rem) {
                ll val = getval(l1-j+rem+1, l1-rem, 1, l1-j);
                if(!vis.find(val)) {
                    vis.insert(val);
                    ans += sum.find(val);
                }
            }
    }
    printf("%lld\n", ans);
    return 0;
}