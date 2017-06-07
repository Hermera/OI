#include <cstdio>
long long P;
long long power(long long x,int k)
{
    long long res=1;
    for (;k;x=x*x%P,k/=2)
        if (k&1) res=res*x%P;
    return res;
}
int main()
{
    long long N,K,M;
    scanf("%lld%lld%lld%lld",&N,&K,&M,&P);
    if (K==1) {printf("%lld\n",N%P);return 0;}
    long long tmp=power(M,K-2),ans=(N%P*tmp%P*M%P-M*(M+1)/2%P*tmp%P*(K-1)%P)%P;
    printf("%lld\n",(ans+P)%P);
    return 0;
}
