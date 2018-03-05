#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k, p, x;
double cost(ll m)
{
	return (double)m * x + double(k) / m * p;
}
int main()
{
	cin >> k >> p >> x;
	double mi = 1e20;
	for (int i = 1; i <= 10000000; i++)
	{
		mi = min(mi, cost(i));
	}
	printf("%.3lf\n", mi);
}