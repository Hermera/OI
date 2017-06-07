#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 5005;
int A, B, C, D, N, M, Q, x[maxn*maxn], t[maxn][maxn];
bool check[maxn*maxn];
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
	x[0] = read(), A = read(), B = read(), C = read(), D = read(), N = read(), M = read(), Q = read();
	for(int i = 1; i <= N*M; ++i) x[i] = (int)((long long)x[i-1]*x[i-1]%D*A%D+(long long)x[i-1]*B%D+C+D)%D;
	
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
		t[i][j] = (i-1)*M+j;
	
	for(int i = 1, j; i <= N*M; ++i)
		j = x[i]%i+1, swap(t[(i-1)/M+1][(i-1)%M+1], t[(j-1)/M+1][(j-1)%M+1]);
	for(int i = 1, u, v; i <= Q; ++i)
		u = read(), v = read(), swap(t[(u-1)/M+1][(u-1)%M+1], t[(v-1)/M+1][(v-1)%M+1]);
	
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
		x[t[i][j]] = (i-1)*M+j;
		
	for(int i = 1, tot = 0; i <= N*M; ++i)
	if(!check[i])
	{
		++tot;
		int r = (x[i]-1)/M+1, c = (x[i]-1)%M+1;
		printf("%d", i);
		for(int j = 1; j < r; ++j)
		for(int k = c+1; k <= M; ++k)
			if(!check[t[j][k]]) check[t[j][k]] = true;
			else break;
			
		for(int j = r+1; j <= N; ++j)
		for(int k = c-1; k; --k)
			if(!check[t[j][k]]) check[t[j][k]] = true;
			else break;
		
		if(tot == N+M-1) break;
		else printf(" ");
	}
	printf("\n");
	return 0;
}
