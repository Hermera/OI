#include <cstdio>
#include <cstring>
using namespace std;
 
int M, K, A, B, C, cas, o;
double ans, now, dp[2][52][8][8][8];
#define f dp[o]
#define g dp[!o]
 
int main() {
    scanf("%d", &cas);
    while(cas--) {
        scanf("%d%d%d%d", &K, &A, &B, &C);
         
        M = 51, ans = 0;
        memset(g, 0, sizeof(g));
        g[M][A][B][C] = 1;
        for(int i = 1; i <= K; ++i) {
            memset(f, 0, sizeof(f));
            for(int m = 1; m <= M; ++m)
                for(int a = 0; a <= 7; ++a)
                for(int b = 0; b <= 7; ++b)
                for(int c = 0; c <= 7; ++c) 
                    if(now = g[m][a][b][c]) {
                        int tot = a + b + c + 1;
                        if(a) f[m][a-1][b][c] += now * a / tot;
                        if(b) {
                            f[m][a+1][b-1][c + (tot < 8)] += now * b / tot;
                        }
                        if(c) {
                            f[m][a][b+1][c-1 + (tot < 8)] += now * c / tot;
                        }
                        if(m) {
                            f[m-1][a][b][c] += now / tot;
                        }
                    }
            o ^= 1;
        }
         
        for(int m = 1; m <= M; ++m)
            for(int a = 0; a <= 7; ++a)
            for(int b = 0; b <= 7; ++b)
            for(int c = 0; c <= 7; ++c)
                ans += (M - m) * g[m][a][b][c];
        printf("%.2lf\n", ans);
    }
    return 0;
}