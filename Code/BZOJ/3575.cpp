#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int maxn = 2e5+5;
typedef int arr[maxn];
 
int n, m, k, tim, cnt;
arr pos, nod, pre, suf, app, upd, val, dis, sp, f;
bool vis[maxn], del[maxn];
struct Data { int next, to, w; } g[maxn<<1];
void add(int x, int y, int w) {
    g[++cnt] = (Data) { f[x], y, w }; f[x] = cnt;
}
 
 
struct ele {
    int pos, val;
    bool operator <(const ele &b) const {
        return val > b.val;
    }
};
priority_queue <ele> bst;
queue <int> q;
 
void SPFA(int o, int v, int b) {
    int p = 0;
    ++tim, dis[o] = v, q.push(o);
    while(!q.empty()) {
        int x = q.front(); 
        q.pop(), vis[x] = 0;
        for(int i = f[x]; i; i = g[i].next)
            if(!del[i]) {
                Data &e = g[i];
                if(pos[e.to] > b) {
                    if(app[e.to] != tim) {
                        app[e.to] = tim;
                        upd[++p] = e.to;
                        val[e.to] = dis[x]+e.w+suf[pos[e.to]];
                    } else val[e.to] = min(val[e.to], dis[x]+e.w+suf[pos[e.to]]);
                } else if(dis[x]+e.w < dis[e.to]) {
                    dis[e.to] = dis[x] + e.w;
                    if(!vis[e.to]) vis[e.to] = 1, q.push(e.to);
                }
            }
    }
     
    for(int i = 1; i <= p; ++i)
        bst.push((ele){ pos[upd[i]], val[upd[i]] });
}
 
int main() {
    n = read(), m = read(), k = read();
    for(int x, y; m--;) x = read(), y = read(), add(x, y, read());
    for(int i = 1; i <= k; ++i) sp[i] = read();
     
    pos[1] = nod[1] = 1;
    for(int i = 1; i <= k; ++i) 
        nod[i+1] = g[sp[i]].to,
        pos[g[sp[i]].to] = i+1;
    for(int i = 1; i <= k; ++i) pre[i+1] = pre[i] + g[sp[i]].w;
    for(int i = k; i >= 1; --i) suf[i] = suf[i+1] + g[sp[i]].w;
     
    memset(dis, 127, sizeof(dis));
    for(int i = 1; i <= k; ++i) {
        del[sp[i]] = 1;
        SPFA(nod[i], pre[i], i);
        del[sp[i]] = 0;
        while(!bst.empty() && bst.top().pos <= i) bst.pop();
        printf("%d\n", bst.empty() ? -1 : bst.top().val);
    }
    return 0;