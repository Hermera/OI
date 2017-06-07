#include<cstdio>
#include<queue>
#include<algorithm>
const int inf = 1e9;
const int maxn = 3e5 + 5;
using namespace std;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int x,now;
int t1[maxn],t2[maxn],rk[maxn];
int st[maxn], ed[maxn];
struct data{int id,t;};
struct res{int id,t;}ans[maxn];
priority_queue<data,vector<data> >q;
bool operator<(data a,data b)
{
	if(rk[a.id]==rk[b.id])return t1[a.id]>t1[b.id];
	return rk[a.id]<rk[b.id];
}
bool operator<(res a,res b)
{
	return a.t<b.t;
}
int main()
{
	while(scanf("%d",&x)!=EOF)
	{
		t1[x]=read();t2[x]=read();rk[x]=read();
		ans[x].id=x;
	}
	t1[x+1]=inf;
	for(int i=1;i<=x+1;i++)
	{
		int t=t1[i]-now;
		while(!q.empty()&&q.top().t<=t)
		{
			now+=q.top().t;
			ans[q.top().id].t=now;
			t-=q.top().t;
			q.pop();
		}
		if(i==x+1)break;
		if(!q.empty()&&t)
		{
			data x=q.top();q.pop();
			x.t-=t;
			q.push(x);
		}
		now=t1[i];
		q.push((data){i,t2[i]});
	}
	sort(ans,ans+x+1);
	for(int i=1;i<=x;i++)
		printf("%d %d\n",ans[i].id,ans[i].t);
	return 0;
}
