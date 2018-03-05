#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b;

int main()
{
	cin >> a >> b;
	ll s = 0;
	for (ll i = 1; i <= 1000005 ; i++)
	{
		for (ll j = ((a - 1) / i + 1) * i; j <= b; j += i)
		{
			if (i < j / i)
			{
				s += i;
				s += j / i;
			}
			else if (i == j / i)
			{
				s += i;
			}
		}
	}
	cout << s << endl;
}