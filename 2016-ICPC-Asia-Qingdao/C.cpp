#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		double l, d;
		cin >> l >> d;
		if (l - d <= 1e-9)
			printf("%.6lf\n", (double)0);
		else
			printf("%.6lf\n", log(l / d) + 1);
	}
}