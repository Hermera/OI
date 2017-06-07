#include <cstdio>
using namespace std;
const int maxn = 1005;
bool voice[maxn][maxn];
int N, BL, ML, c[maxn];

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d%d%d", &N, &BL, &ML);
	for(int i = 1; i <= N; ++i) scanf("%d", c+i);
	voice[0][BL] = true;
	for(int i = 1; i <= N; ++i)
	for(int j = 0; j <= ML; ++j)
	{
		if(j-c[i] >= 0) voice[i][j] |= voice[i-1][j-c[i]];
		if(j+c[i] <= ML) voice[i][j] |= voice[i-1][j+c[i]];
	}
	int ans = -1;
	for(int i = 0; i <= ML; ++i)
		if(voice[N][i]) ans = i;
	printf("%d\n", ans);
	return 0;
}
