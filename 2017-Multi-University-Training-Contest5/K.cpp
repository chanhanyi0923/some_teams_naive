#include<bits/stdc++.h>
using namespace std;
const int maxn = 100100;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n,k;
		scanf("%d%d",&n,&k);
		int a[maxn];
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		sort(a,a+n);
		int now=n-1;
		int num=1;
		while(now>0 && a[now]-a[now-1]<=k){
			now--;
			num++;
		}
		printf("%d\n",num);
	}
	return 0;
}
