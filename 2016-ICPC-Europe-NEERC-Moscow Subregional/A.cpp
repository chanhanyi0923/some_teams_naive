#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> a;
int main() 
{
	int n;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int maxord=0;
	for(int i=1;i<n;i++)if(a[i]>a[maxord])maxord=i;
	int aa=maxord-1;
	if(aa<0)aa=n-1;
	int bb=maxord+1;
	if(bb>=n)bb=0;
	printf("%d %d %d\n",aa+1,maxord+1,bb+1);
	return 0;
}
