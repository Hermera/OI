 
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int maxn = 1005;
int n, m, k, cas;
vector <int> e[maxn];
vector <int>:: iterator a, b, c;
bool p[maxn][maxn], w[maxn][maxn];
 
#define u (*a)
#define v (*b)
#define t (*c)
namespace solve2 {
    void main() {
        for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            w[i][j] = p[i][j];
    }
}
 
namespace solve3 {
    void main() {
        for(int i = 1; i <= n; ++i)
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = a+1; b != e[i].end(); ++b)
                w[u][v] = w[v][u] = 1;
    }
}
 
namespace solve4 {
    void main() {
        for(int i = 1  ; i <= n; ++i)
        for(int j = i+1; j <= n; ++j) 
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = e[j].begin(); b != e[j].end(); ++b)
                if(u != v && u != j && v != i && p[u][v])
                    w[i][j] = w[j][i] = 1;
    }
}
 
namespace solve5 {
    int cnt[maxn][maxn];
    void main() {
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1; i <= n; ++i)
        for(a = e[i].begin(); a != e[i].end(); ++a)
        for(b = a+1; b != e[i].end(); ++b)
            ++cnt[u][v], ++cnt[v][u];
        for(int i = 1  ; i <= n; ++i)
        for(int j = i+1; j <= n; ++j)
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = e[j].begin(); b != e[j].end(); ++b) {
                if(u == v || u == j || v == i) continue;
                if(cnt[i][j] - p[i][v] - p[j][u] <= 0) continue;
                w[u][v] = w[v][u] = 1;
            }
    }
}
 
 
int now;
struct chark_1D {
    int tim[maxn], cnt[maxn];
    int &operator [](int x) {
        if(tim[x] != now) cnt[x] = 0, tim[x] = now;
        return cnt[x];
    }
};
 
struct chark_2D {
    int tim[maxn][maxn], cnt[maxn][maxn];
    int &operator ()(int x, int y) {
        if(tim[x][y] != now) cnt[x][y] = 0, tim[x][y] = now;
        return cnt[x][y];
    }
};
 
namespace solve6 {
    chark_1D cnt;
    int tot, vis[maxn][maxn];
 
    void main() {
        for(int i = 1  ; i <= n; ++i)
        for(int j = i+1; j <= n; ++j) {
            ++now, tot = 0;
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = e[j].begin(); b != e[j].end(); ++b) 
                if(u != v && u != j && v != i && p[u][v]) 
                    ++cnt[u], ++cnt[v], ++tot, vis[u][v] = now;
             
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = e[j].begin(); b != e[j].end(); ++b) {
                if(u == v || u == j || v == i) continue;
                if(tot - (cnt[u]+cnt[v]-(vis[u][v] == now)) > 0)
                    w[u][v] = w[v][u] = 1;  
            }
        }
    }
}
 
namespace solve7 {
    vector <int> bo[maxn][maxn];
    chark_1D cnt, mbo;
    chark_2D lik, sbo;
    int tot;
 
    void main() {
        for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            bo[i][j].clear();
             
        for(int i = 1; i <= n; ++i)
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = a+1; b != e[i].end(); ++b)
                bo[u][v].push_back(i),
                bo[v][u].push_back(i);
             
        for(int i = 1  ; i <= n; ++i)
        for(int j = i+1; j <= n; ++j) {
            ++now, tot = 0;
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = e[j].begin(); b != e[j].end(); ++b) 
                if(u != v && u != j && v != i) 
                    for(c = bo[u][v].begin(); c != bo[u][v].end(); ++c) 
                        if(t != i && t != j) 
                            ++cnt[u], ++cnt[v], ++tot, ++mbo[t],
                            ++lik(t, u), ++lik(t, v), ++sbo(u, v);
         
            for(a = e[i].begin(); a != e[i].end(); ++a)
            for(b = e[j].begin(); b != e[j].end(); ++b) {
                if(u == v || u == j || v == i) continue;
                 
                int ret = tot;
                ret -= cnt[u] + cnt[v];
                ret -= mbo[u] + mbo[v];
                ret += lik(u, v) + lik(v, u) + sbo(u, v);
                if(ret > 0) w[u][v] = w[v][u] = 1;
            }   
        }
    }
}
 
 
int main() {
    cas = read();
    while(cas--) {
        n = read(), m = read(), k = read();
        for(int i = 1; i <= n; ++i) e[i].clear();
        memset(p, 0, sizeof(p));
        memset(w, 0, sizeof(w));
         
        for(int x, y; m--;) {
            x = read(), y = read();
            if(x == y)  continue;
            if(p[x][y]) continue;
            p[x][y] = p[y][x] = 1;
            e[x].push_back(y);
            e[y].push_back(x);
        }
         
        if(k == 2) solve2::main();
        if(k == 3) solve3::main();
        if(k == 4) solve4::main();
        if(k == 5) solve5::main();
        if(k == 6) solve6::main();
        if(k == 7) solve7::main();
         
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j)
                printf("%c", w[i][j] ? 'Y' : 'N');
            printf("\n");
        }
    }
    return 0;
}
﻿