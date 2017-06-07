#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int Maxn = 2e5+5;
const int Size = 130;
char s[Maxn];
int Rank[Maxn], sa[Maxn], c[Maxn], f[Maxn], height[Maxn], belong[Maxn];

void BuildSa(int N, int M)
{
	int i, *x = Rank, *y = f;
	for(i = 0; i < M; ++i) c[i] = 0;
	for(i = 0; i < N; ++i) c[x[i] = s[i]]++;
	for(i = 1; i < M; ++i) c[i] += c[i-1];
	for(i = N-1; i >= 0; --i) 
		sa[--c[x[i]]] = i;	
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

void GetHeight(int N)
{
	for(int i = 0; i < N; ++i) Rank[sa[i]] = i;
	for(int i = 0, k = 0; i < N; ++i)
	{
		if(k) --k;
		int j = sa[Rank[i]-1];
		while(s[i+k] == s[j+k]) ++k;
		height[Rank[i]] = k;
	}
}

int solve(int N)
{
	int Max = 0;
	for(int i = 1; i < N; ++i)
		if(belong[sa[i]] != belong[sa[i-1]] && belong[sa[i-1]] && belong[sa[i]]) 
			Max = max(Max, height[i]);
	return Max;
}

int main()
{
//	freopen("data.in", "r", stdin);
	scanf("%s", s);
	int len = strlen(s), pre; s[len] = '$';
	for(int i = 0; i < len; ++i) belong[i] = 1;
	scanf("%s", s+len+1); pre = len; len = strlen(s);
	s[len++] = '*';
	for(int i = pre+1; i < len-1; ++i) belong[i] = 2;
	BuildSa(len, Size);
	GetHeight(len);
	printf("%d\n", solve(len));
	return 0;
}
