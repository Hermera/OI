#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define ll long long
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,K,top;
int fa[20005];
int u[100005],v[100005],c[100005];
int au[20005],av[20005],ac[20005];
bool mark[100005];
int num[2];
int find(int x) { return x==fa[x]?x:fa[x]=find(fa[x]); }

void solve(bool typ,int mx)
{
	for(int i=1;i<=m;i++)
		if(c[i]==typ&&num[typ]<mx)
		{
			int p=find(u[i]),q=find(v[i]);
			if(p!=q)
			{
				fa[p]=q;
				au[++top]=u[i],av[top]=v[i],ac[top]=c[i];
				mark[i]=1;num[typ]++;
			}
		}
}
int main()
{
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++)
		u[i]=read(),v[i]=read(),c[i]=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	num[0]=num[1]=0;
	solve(1,inf);solve(0,inf);
	if(num[1]+num[0]!=n-1||num[0]>K) { puts("no solution"); return 0; }
	top=0;num[0]=num[1]=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
		if(c[i]==0&&mark[i])
		{
			int p=find(u[i]),q=find(v[i]);
			if(p!=q)
				num[0]++, fa[p]=q, au[++top]=u[i], av[top]=v[i], ac[top]=c[i];
		}
    solve(0,K);solve(1,inf);
	if(num[0]<K) { puts("no solution"); return 0; }
	for(int i=1;i<=top;i++)
		printf("%d %d %d\n",au[i],av[i],ac[i]);
	return 0;
}
