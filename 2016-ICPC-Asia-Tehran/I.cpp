#include<bits/stdc++.h>
using namespace std;
const int maxn = 3000;
const int INF = 2147483647;
int main(){
    int n;
    while(scanf("%d",&n),n){
        int a[maxn];
        int N=(1<<n)+1;
        for(int i=0;i<N;i++)scanf("%d",&a[i]);
        sort(a,a+N);
        if(n==1){
            printf("%d\n",a[2]-a[0]);
            continue;
        }
        //for(int i=0;i<N;i++)printf("%d ",a[i]);puts("");
        int nn=(N>>2);
        int mi=INF;
        int num=0;
        for(int i=0;i<nn;i++){
            mi=min(a[i+nn*3+1]-a[i],mi);//printf("now mi = %d\n",mi);
        }
        for(int i=1;i<nn;i++){
            mi=min(a[i+nn*3]-a[i],mi);//printf("now mi = %d\n",mi);
        }
        int ma=-INF;
        for(int i=nn;i<=3*nn;i++){
            ma=max(ma,min(a[nn*4]-a[i],a[i]-a[0]));//printf("now ma = %d  a[start]=%d  a[final]=%d  a[i]=%d\n",ma,a[0],a[nn*4],a[i]);
        }
        printf("%d\n",min(mi,ma));
    }
    return 0;
}
