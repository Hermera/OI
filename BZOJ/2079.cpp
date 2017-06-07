#include <cstdio>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

const int maxn = 200005;
bool check[maxn];
int N, M;

bool Judge()
{
	for(int i = 1; i <= N; ++i)
	if(!check[i]) return false;
	return true;
}

int main()
{
	N = read(), M = read();
	for(int i = 1; i <= M; ++i)
		check[read()] = true, check[read()] = true;
	
	printf("%s\n", Judge() ? "TAK" : "NIE");
	return 0;
}
