#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int main()
{
	int n1, n2;
	cin >> n1 >> n2;
	
	int k1 = n2 - n1;
	int k2 = n2 - n1 + 360;
	int k3 = n2 - n1 - 360;
	
	if (abs(k1) > abs(k2))
	{
		swap(k1, k2);
	}
	
	if (abs(k1) > abs(k3))
	{
		swap(k1, k3);
	}
	
	if (k1 == -180)
	{
		k1 = 180;
	}
	
	cout << k1 << endl;
}
