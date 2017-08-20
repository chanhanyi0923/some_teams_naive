#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    n=12;//scanf("%d",&n);
    int a[1000];
    printf("48 144\n");
    for(int i=1;i<=n;i++)a[i]=n;
    int now=1;
    int mx=n;
    int l=0;
    for(int i=3*n;i>0;i--){
        if(mx<=0){
            puts("NO");
            return 0;
        }
        int mx2=mx;
        while(mx2>0){
            printf("%d %d\n",i+n,now);l++;
            a[now]--;
            if(a[now]<0){
                puts("NO");
                return 0;
            }
            now++;
            mx2--;
            if(now>n)now=1;
        }
        mx=-1000;
        for(int i=1;i<=n;i++)if(a[i]>mx)mx=a[i];
    }
    printf("12\n");
    for(int i=1;i<=12;i++)printf("%d\n",i);
    //printf("%d\n",l);
    return 0;
}
