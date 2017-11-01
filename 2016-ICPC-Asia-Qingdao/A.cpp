#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		ll ans = 0;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			ans += x * y;
		}
		cout << ans << endl;
	}
}