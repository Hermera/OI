#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef unsigned long long ll;
inline ll read() {
    char ch = getchar(); ll x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int N = 1e6+10;
 
int cas, tot, top, n, q;
int x[N], app[N], who[N];
ll ans, ret, y[N], A, B, P;
 
int main() {
    cas = read();
    while(cas--) {
        n = read(), q = read();
         
        x[1] = read();
        A = read(), B = read(), P = read();
        for(int i = 2; i <= q; ++i) 
            x[i] = (A * x[i-1] + B) % P;
         
        top = 1, ans = tot = 0;
        memset(app, -1, sizeof(app));
        memset(who, -1, sizeof(who));
     
        for(int i = 1; i <= q; ++i) {
            if(app[x[i]] < 0) {
                if(tot == n) {
                    ans -= who[top], --tot;
                    app[who[top]] = -1, ++top;
                    while(who[top] < 0 && top < i) ++top;
                }
                who[i] = x[i];
                app[x[i]] = i;
                ans += x[i], ++tot;
            } else {
                who[app[x[i]]] = -1;
                who[i] = x[i], app[x[i]] = i;
            }
            y[i] = ans;
        }
         
        ret = 0;
        for(ll i = 1; i <= q; ++i)
            ret += i * y[i];
        cout << ret << endl;
    }
    return 0;
}