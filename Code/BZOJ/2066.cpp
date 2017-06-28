    //code by thy
    #include<cstdio>  
    #include<cstring>  
    #include<iostream>  
    #include<algorithm>  
    const int maxn=1000010;  
    using namespace std;  
    int n,m,a[maxn],cnt,b[maxn],ans,tot;char ch;  
      
    void read(int &x){  
        for (ch=getchar();!isdigit(ch);ch=getchar());  
        for (x=0;isdigit(ch);ch=getchar()) x=x*10+ch-'0';  
    }  
      
    int main(){  
        scanf("%d%d",&m,&n);  
        for (int i=1;i<=n;i++) read(a[i]);  
        if (a[n]==m-1){  
            ans=1;  
            for (int i=n;i&&a[i]-a[i-1]==1;i--,ans++);  
            return printf("%d\n",ans),0;  
        }  
        a[n+1]=m-1;  
        for (int i=n;i;i--)  
            if (a[i+1]-a[i]==1) b[cnt]++;  
            else if (a[i+1]-a[i]==2){  
                if (cnt&1) ans=ans^b[cnt];  
                b[++cnt]=1;  
            }  
            else{  
                if (cnt&1) ans=ans^b[cnt];  
                cnt+=3-((a[i+1]-a[i])&1),b[cnt]=1;  
            }  
        if (cnt&1) ans=ans^b[cnt];  
        if (ans)  
            for (int i=1;i<=cnt;i++)  
                if ((i&1)&&(ans^b[i])<b[i]||i%2==0&&(ans^b[i-1])>b[i-1]&&(ans^b[i-1])<=b[i-1]+b[i])  
                    tot++;  
        printf("%d\n",tot);  
        return 0;  
    }  
