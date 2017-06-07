#include <cstdio>
const int maxn = 1e5+5;
int N, sum[maxn], q[maxn], f[maxn], g[maxn];
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read();
    for (int i = 1; i <= N; ++i) sum[i] = sum[i-1]+read(); 
    
    int h = 1, t = 1; q[1] = N+1;
    for(int i = N; i; --i)
    {
        while (t > h && sum[q[h+1] - 1]-sum[i - 1] >= f[q[h +1]]) h++;
        
        while(h < t && sum[q[h+1]-1]-sum[i-1] >= f[q[h+1]]) ++h;
        f[i] = sum[q[h]-1]-sum[i-1], g[i] = g[q[h]]+1;
        while(h < t && f[i]-sum[i-1] < f[q[t]]-sum[q[t]-1]) --t;
        q[++t] = i;
    }

	printf("%d\n", g[1]);
    return 0;
}
