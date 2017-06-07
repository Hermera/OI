#include <cstdio>
#include <cstring>
#include <iostream>
#define M 10100
#define INF 1e9
#define EPS 1e-12
using namespace std;
int n;
double E,s[M],k[M],v[M],x[M];
double Calculate(double lambda)
{
    double temp=0;
    for(int i=1;i<=n;i++)
    {
        double l=max(0.0,v[i]),r=INF;
        while(r-l>EPS)
        {
            double mid=(l+r)/2;
            if(2*lambda*k[i]*mid*mid*(mid-v[i])>1)
                r=mid;
            else l=mid;
        }
        x[i]=(l+r)/2;
        temp+=k[i]*(x[i]-v[i])*(x[i]-v[i])*s[i];
    }
    return temp;
}
void Bisection()
{
    double l=0,r=INF;
    while(r-l>EPS)
    {
        double mid=(l+r)/2;
        if( Calculate(mid)>=E )
            l=mid;
        else r=mid;
    }
}
int main()
{
    int i;
    cin>>n>>E;
    for(i=1;i<=n;i++)
        scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
    Bisection();
    double ans=0;
    for(i=1;i<=n;i++)
        ans+=s[i]/x[i];
    printf("%.10lf\n",ans);
    return 0;
}
