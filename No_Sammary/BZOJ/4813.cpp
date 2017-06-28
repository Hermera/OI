#include <cstdio>
#include <algorithm>
using namespace std;
 
const int N = 105;
int n, m, cnt, h[N];
struct Data {
    int next, to;
} g[N << 1];
 
void add(int x, int y) {
    g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
    g[++cnt] = (Data) { h[y], x }; h[y] = cnt;
}
 
 
int fa[N], dep[N], len;
void dfs(int x) {
    for(int v, i = h[x]; i; i = g[i].next)
        if((v = g[i].to) != fa[x])
            fa[v] = x, dep[v] = dep[x]+1, dfs(v);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int x, y, i = 2; i <= n; ++i) {
        scanf("%d%d", &x, &y), add(x, y);
    }
     
    dfs(0);
    for(int i = 1; i <= n; ++i)
        len = max(len, dep[i]);
         
    int ans = 0;
    if(m <= len+1) ans = m+1;
    else ans = (m+len)/2+1;
    ans = min(ans, n);
    printf("%d\n", ans);
    return 0;
}
﻿
