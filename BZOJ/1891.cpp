#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int maxn = 4e5+5;
const int maxm = 2e6+5;
const int INF = 1e9;
 
typedef int arr[maxn];
 
int n, m, s, t, cnt;
arr hd, le;
 
struct Data { 
    int next, to;
} g[maxm];
void add(int x, int y) {
    g[++cnt] = (Data) { hd[x], y }; hd[x] = cnt;
}
 
arr q, mat;
bool bfs() {
    int l = 1, r = 0, ok = 0;
    for(int i = 1; i <= n*2; ++i) le[i] = 0;
    for(int i = 1; i <= n; ++i) if(!mat[i]) q[++r] = i;
    while(l <= r) {
        int x = q[l++];
        if(x > n) {
            q[++r] = mat[x];
            le[mat[x]] = le[x]+1;
        } else
            for(int v, i = hd[x]; i; i = g[i].next) 
                if(!le[v = g[i].to]) {
                    le[v] = le[x]+1;
                    if(mat[v]) q[++r] = v;
                    else ok = 1;
                }   
    }
    return ok;
}
 
bool dfs(int x) {
    for(int v, i = hd[x]; i; i = g[i].next) 
        if(le[v = g[i].to] > le[x]) {
            le[v] = -1;
            if(!mat[v] || dfs(mat[v])) {
                mat[v] = x;
                mat[x] = v;
                return 1;
            }
        }
    return 0;
}
 
void match() {
    while(bfs())
        for(int i = 1; i <= n; ++i)
            if(!mat[i]) dfs(i);
}
 
 
int tim, top, tot;
arr dfn, low, sta, scc, siz;
void tarjan(int x) {
    dfn[x] = low[x] = ++tim;
    sta[++top] = x;
    for(int i = hd[x]; i; i = g[i].next) {
        int v = g[i].to;
        if(!dfn[v]) tarjan(v);
        if(!scc[v]) low[x] = min(low[x], low[v]);
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
 
 
struct Edge {
    int u, v;
    void init() { 
        u = read();
        v = read()+n;
        add(u, v); 
    }
     
    int ask() {
        if(scc[u] == scc[v]) return 0;
        return mat[u] == v ? 1 : 2;
    }
} e[maxm];
 
int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) e[i].init();
     
    match();
    for(int i = 1; i <= 2*n; ++i) hd[i] = cnt = 0;
    for(int i = 1; i <= m; ++i)
        if(mat[e[i].u] == e[i].v) add(e[i].v, e[i].u);
        else add(e[i].u, e[i].v);
     
    for(int i = 1; i <= 2*n; ++i)
        if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= m; ++i) 
        printf("%d", e[i].ask());
    printf("\n");
    return 0;
}
﻿