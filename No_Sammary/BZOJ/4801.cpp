#include <cstdio>
#include <algorithm>
using namespace std;
 
int idx(char ch) {
    if(ch == 'T') return 10;
    if(ch == 'J') return 11;
    if(ch == 'Q') return 12;
    if(ch == 'K') return 13;
    if(ch == 'A') return 1;
    return ch - '0';
}
 
bool cmp(int x, int y) {
    if(x == y) return 1;
    if(x == 1) x += 13;
    if(y == 1) y += 13;
    return x >= y;
}
 
int cas, s[5], t[5];
char str[10];
 
int solve(int a, int b, int c, int d) {
    int Q = 0, T = 0;
    if(cmp(s[a], t[c])) Q += s[a];
    else T += t[c];
     
    if(Q) {
        if(cmp(s[b], t[d])) Q += s[b];
        else T += t[d];
    } else {
        if(cmp(t[d], s[b])) T += t[d];
        else Q += s[b];
    }
     
    return Q - T;
}
 
int main() {
    scanf("%d", &cas);
    while(cas--) {
        scanf("%s", str), s[0] = idx(*str);
        scanf("%s", str), s[1] = idx(*str);
        scanf("%s", str), t[0] = idx(*str);
        scanf("%s", str), t[1] = idx(*str);                     
         
        int ans = -100;
        ans = max(ans, min(solve(0, 1, 0, 1), solve(0, 1, 1, 0)));
        ans = max(ans, min(solve(1, 0, 0, 1), solve(1, 0, 1, 0)));
        printf("%d\n", ans);
    }
    return 0;
}
