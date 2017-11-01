#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 10100;

int wx[maxn],wy[maxn],wt[maxn];
int nx,ny;

int main()
{
	freopen("joy.in","r",stdin);
	freopen("joy.out","w",stdout);
	int sx,sy,fx,fy;
	scanf("%d%d%d%d",&sx,&sy,&fx,&fy);
	int n,k,vm;
	scanf("%d%d%d",&n,&k,&vm);
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&wt[i],&wx[i],&wy[i]);
	}
	nx=sx,ny=sy;
	int j=0;
	for(int i=0;i<k;i++){
		if(j+1<n && wt[j+1]<=i)j++;
		nx+=wx[j];
		ny+=wy[j];
		//printf("%d %d\n",nx,ny);
	}
	if(1ll*(nx-fx)*(nx-fx)+1ll*(ny-fy)*(ny-fy) > 1ll*vm*vm*k*k){
		printf("No\n");
		return 0;
	}
	puts("Yes");
	double xx,yy;
	xx=fx-nx;
	xx/=k;
	yy=fy-ny;
	yy/=k;
	double nowx=sx,nowy=sy;
	j=0;
	for(int i=0;i<k;i++){
		if(j+1<n && wt[j+1]<=i)j++;
		nowx+=wx[j];
		nowx+=xx;
		nowy+=wy[j];
		nowy+=yy;
		printf("%.15f %.15f\n",nowx,nowy);
	}
	
	return 0;
}
