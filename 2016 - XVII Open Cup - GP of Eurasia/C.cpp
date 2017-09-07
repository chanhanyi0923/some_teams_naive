#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const double eps = 1e-8;

int cmp(double x){
	if(fabs(x)<eps)return 0;
	if(x>0)return 1;
	return -1;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	char s[10000];
	scanf("%s",s);
	int inc0,inc1;
	double mul1;
	scanf("%d",&inc0);
	scanf("%s",s);
	scanf("%lf",&mul1);
	scanf("%d",&inc1);
	if(cmp(inc1-inc0*mul1)==1){
		printf("Evolve, Power up\n");
	}else{
		if(cmp(inc1-inc0*mul1)==0){
			printf("Whatever\n");
		}else{
			printf("Power up, Evolve\n");
		}
	}
	return 0;
}
