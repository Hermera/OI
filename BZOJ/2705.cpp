#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
ll n,ans;
int m;
ll phi(ll x)
{
    ll t=x;
    for(ll i=2;i<=m;i++)
        if(x%i==0)
        {
            t=t/i*(i-1);
            while(x%i==0)x/=i;
        }
    if(x>1)t=t/x*(x-1);
    return t;
}
int main()
{
	scanf("%lld",&n);
	m=sqrt(n);
	for(int i=1;i<=m;i++)
    	if(n%i==0)
	        ans+=(ll)i*phi(n/i)+(ll)(n/i)*phi(i);  
	printf("%lld",ans);
	return 0;
}
