#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ll n, x;
	double v;
	cin >> n >> x >> v;
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		ll l, r;
		double v;
		cin >> l >> r >> v;
		sum += (l - r) * v;
	}
	sum /= v;
	double ans = asin(sum / x);
	if (sum / x > sqrt(3) / 2)
	{
		printf("Too hard\n");
	}
	else printf("%.3lf\n", x / (v * cos(ans)));
}