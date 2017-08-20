#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    int cnt1[1000],cnt2[1000];
    while(scanf("%d%d",&n,&m),n!=-1){
        memset(cnt1,0,sizeof(cnt1));
        memset(cnt2,0,sizeof(cnt2));
        for(int i=0;i<n;i++){
            int a;
            scanf("%d",&a);
            cnt1[a]++;
        }
        for(int i=0;i<m;i++){
            int a;
            scanf("%d",&a);
            cnt2[a]++;
        }
        bool flag=1;
        for(int i=0;i<500;i++){
            if(i%2){
                if(cnt1[i])cnt1[i*2+2]++;
                if(cnt2[i])cnt2[i*2+2]++;
                if(cnt1[i]!=cnt2[i]){
                    flag=0;
                    break;
                }
            }else{
                if((!cnt1[i] && cnt2[i]) || (cnt1[i] && !cnt2[i])){
                    flag=0;
                    break;
                }
            }
        }
        if(flag)puts("Y");
        else puts("N");
    }
    return 0;
}
