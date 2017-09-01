#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll pair_num(ll x)
{
	return x * (x - 1) / 2;
}
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		ll n, m;
		ll ans = 0;
		cin >> n >> m;
	
		if (n - 1 > m)
		{
			ll c = m + 1;
			ll dc = n - c;
			ll dcp = pair_num(dc) + c * dc;
			ans += n * dcp;
		
			ans += m;
			ans += 2 * pair_num(m);
		}
		else
		{
			ans = n - 1;
			ans += 2 * pair_num(n - 1);
			ans -= m - (n - 1);
			ans = max(pair_num(n), ans);
		}
		cout << ans * 2 << endl;
	}
	return 0;
}
