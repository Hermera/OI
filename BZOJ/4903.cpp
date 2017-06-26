#include <cstdio>
using namespace std;
 
const int SIZE = 5e6;
char in[SIZE], *inp = in;
void input() {
    fread(in, 1, SIZE, stdin);
}
 
inline int read() {
    int x = 0;
    while(*inp < '0' || *inp > '9') ++inp;
    while(*inp >= '0' && *inp <= '9') x = x*10+*(inp++)-'0';
    return x;
}
 
 
const int N = 3e5+5;
const int mod = 1e9+7;
 
int n, a[N], p[N], dp[N];
 
inline void update(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}
 
int main() {
    input();
 
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) p[a[i]] = i;
     
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        int s = a[i];
         
        update(dp[s], 1);
        for(int t = s; t; (--t) &= s)
            if(p[t] > i) update(dp[t], dp[s]);
        update(ans, dp[s]);
    }
     
    update(ans, -n);
    update(ans, mod);
     
    printf("%d\n", ans);
    return 0;
}