#include <cstdio>
#include <algorithm>
using namespace std;
 
 
const int N = 2e7+5;
 
int seed;
int getrand() {
    seed = ((seed * 12321) ^ 9999) % 32768;
    return seed;
}
 
 
int n, k, s, t;
int p[N];
 
void input() {
    scanf("%d%d%d", &k, &seed, &s);
    n = 2 * k + 1;
     
    int sum = 0;
    for(int i = 1; i <= n; ++i) 
        p[i] = (getrand() / 128) & 1, sum += p[i];
     
    int i = 1;
    for(; sum > k; --sum) {
        while(!p[i]) ++i;
        p[i] = 0;
    }
     
    for(; sum < k; ++sum) {
        while( p[i]) ++i;
        p[i] = 1;
    }
     
}
 
 
 
typedef pair<int, int> pii;
#define fir first
#define sec second
pii q[N];
 
int solve(int x) {
    nth_element(q, q + x, q + t);
    return -q[x].sec;
}
 
 
int main() {
    input();
     
    int sum = 0;
    for(int i = 1; i <= n; ++i) {
        sum += p[i] ? -1 : 1;
        if(!p[i]) q[t++] = pii(sum, -i);
    }
     
    int ans1 = solve(0);
    int ans2 = solve(s);
    int ans3 = solve(k-s);
    printf("%d\n%d\n%d\n", ans1, ans2, ans3);
    return 0;
}