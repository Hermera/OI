#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000005;
char s[maxn];
int f[maxn], N, kase;

void MakeFail(char *s, int len)
{
	memset(f, 0, sizeof(f));
	for(int i = 1; i < len; i++)
	{
		int j = f[i];
		while(j && s[i] != s[j]) j = f[j];
		f[i+1] = s[i]==s[j] ? j+1 : 0;
	}
}

int main()
{
	while(scanf("%d", &N) == 1 && N)
	{
		memset(s, 0, sizeof(s));
		scanf("%s", s);
		printf("Test case #%d\n", ++kase);
		int len = strlen(s);
		MakeFail(s, len);
		for(int i = 2; i <= len; i++)
		if(i%(i-f[i]) == 0 && i/(i-f[i])>1)
			printf("%d %d\n", i, i/(i-f[i]));
		printf("\n");
	}
}
