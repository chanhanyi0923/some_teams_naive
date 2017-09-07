#include<bits/stdc++.h>
using namespace std;
const int maxn = 100100;
const int MOD = 1000000000;
typedef long long ll;
ll a[maxn];
ll sum;

ll gcd(ll A,ll B){
    if(B==0)return A;
    return gcd(B,A%B);
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n-1;i++)scanf("%lld",&a[i]);
    srand(time(NULL));
    int top=n;
    ll now=-1;
    int ask=rand()%MOD;
    printf("? %d\n",ask);
    fflush(stdout);
    a[top++]=ask;
    int tmp;
    scanf("%d",&tmp);
    a[top++]=tmp;
    sum=0;
    for(int i=1;i<top-1;i++){
        sum+=a[i];
    }
    if(sum!=tmp)now=sum-tmp;
    sum+=a[top-1];
    sum-=a[1];

    //for(int i=1;i<top;i++)printf("%d ",a[i]);//puts("");
    //printf("\nnow = %d\n",now);
    //fflush(stdout);

    for(int _=3;_<1000;_++){
        ask=rand()%MOD;
        if(now!=-1)ask=ask%now;
        printf("? %d\n",ask);
        fflush(stdout);
        a[top]=ask;
        //s[top]=s[top-1]+a[top];
        sum+=a[top];
        sum-=a[top-n];
        top++;
        //printf("sum = %lld\n",sum);fflush(stdout);
        scanf("%d",&tmp);
        if(sum!=tmp){
            if(now==-1){
                now=sum-tmp;
            }else{
                now=gcd(now,sum-tmp);
            }
        }
        a[top]=tmp;
        sum+=a[top];
        sum-=a[top-n];
        top++;

        //for(int i=1;i<top;i++)printf("%d ",a[i]);//puts("");
        //printf("\nnow = %d\n",now);
        //fflush(stdout);
    }
    printf("! %lld\n",now);
    fflush(stdout);
    return 0;
}
