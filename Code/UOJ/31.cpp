#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2e5+5;
int n, t, m;
char str[N];

typedef pair<int, int> pi;
#define fir first
#define sec second
pi put[N];

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for(int i = 1; i <= (n/2); ++i)
        if(str[i] == ')') {
            while(str[t] == ')' || t <= i) ++t;
            put[++m] = pi(i, t);
            swap(str[i], str[t]);
        }

    printf("%d\n", m);
    for(int i = 1; i <= m; ++i)
        printf("%d %d\n", put[i].fir, put[i].sec);
    return 0;
}
