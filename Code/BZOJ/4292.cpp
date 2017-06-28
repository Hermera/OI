#include<cstdio>    
using namespace std;  
typedef long long ll;
ll A, B, K;  
  
int cal(long long x) {  
    int ans = 0;  
    while(x) ans += (x%10)*(x%10), x /= 10;  
    return ans;  
}  
  
int main() {  
    scanf("%lld%lld%lld", &K, &A, &B);  
    int ans = 0;
    for(int i = 1; i <= 1500 && i <= B/K; ++i) {  
        ll n = K*i;
        if(A <= n && n <= B && cal(n) == i) 
        	++ans;  
    }  
    printf("%d\n", ans);  
    return 0;  
}
