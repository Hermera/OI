#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 200005;
const int size = 256;
char s[maxn], ans[maxn];
int len, Rank[maxn], f[maxn], c[maxn], sa[maxn];

void BuildSa(int N, int M)
{
	int i, *x = Rank, *y = f;
	for(i = 0; i < M; ++i) c[i] = 0;
	for(i = 0; i < N; ++i) c[x[i] = s[i]]++;
	for(i = 1; i < M; ++i) c[i] += c[i-1];
	for(i = N-1; i >= 0; --i) sa[--c[x[i]]] = i;	
	for(int k = 1; k <= N;k <<= 1)
	{
		int p = 0;
		for(i = N-k; i < N; ++i) y[p++] = i;
		for(i = 0; i < N; ++i) if(sa[i] >= k) y[p++] = sa[i]-k;
		for(i = 0; i < M; ++i) c[i] = 0;
		for(i = 0; i < N; ++i) c[x[y[i]]]++;
		for(i = 0; i < M; ++i) c[i] += c[i-1];
		for(i = N-1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1; x[sa[0]] = 0;
		for(i = 1; i < N; ++i)
			x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
		if(p >= N) break;
		M = p;
	}
}

int main()
{
//	freopen("data.in", "r", stdin);
	scanf("%s", s);
	len = strlen(s);
	for(int i = 0; i < len; ++i) s[len+i] = s[i];
	s[len<<1] = '\0';
	BuildSa((len<<1)+1, size);
	for(int i = 0; i <= len<<1; ++i)
	if(sa[i] < len)
		printf("%c", s[sa[i]+len-1]);
	printf("\n");
	return 0;
}
