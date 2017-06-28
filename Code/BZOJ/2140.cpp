#include <map>
#include <cstdio>
using namespace std;
typedef unsigned long long ll;
 
const int maxn = 4005;
const int bin = 233;
 
map <ll, int> num;
ll gethash(char *s) {
    ll ret = 0;
    for(int i = 0; s[i]; ++i)
        ret = ret * bin + s[i];
    return ret;
}
 
 
int cnt, tim, top, tot;
int h[maxn], dfn[maxn], low[maxn], sta[maxn], scc[maxn], siz[maxn];
struct Data { int next, to; } g[maxn * 10];
void add(int x, int y) {
    g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}
 
void cmin(int &x, int y) { x = x > y ? y : x; }
void tarjan(int x) {
    dfn[x] = low[x] = ++tim;
    sta[++top] = x;
    for(int i = h[x]; i; i = g[i].next) {
        int v = g[i].to;
        if(!dfn[v]) tarjan(v), cmin(low[x], low[v]);
        else if(!scc[v]) cmin(low[x], low[v]);
    }
    if(low[x] == dfn[x]) {
        ++tot;
        while(top) {
            int v = sta[top--];
            scc[v] = tot, ++siz[tot];
            if(v == x) break;
        }
    }
}
 
 
int n, m;
char s[maxn], t[maxn];
 
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)  {
        scanf("%s%s", s, t);
        num[gethash(s)] = num[gethash(t)] = i;
    }
     
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%s%s", s, t);
        add(num[gethash(s)], num[gethash(t)]);
    }
     
    for(int i = 1; i <= n; ++i) 
        if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; ++i)
        printf("%s\n", siz[scc[i]] > 1 ? "Unsafe" : "Safe");
    return 0;
}
﻿