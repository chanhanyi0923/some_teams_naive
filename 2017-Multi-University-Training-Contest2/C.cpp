#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int P = 1000000007;

vector<ll> a;
vector<ll> b;
vector<ll> mal;

int n;
int main()
{
	while (scanf("%d", &n) == 1)
	{
		a.clear();
		b.clear();
		a.resize(n, 0);
		b.resize(n, 0);
		
		for (int i = 0; i < n; i++)
		{
			scanf("%lld", &a[i]);
		}
		for (int i = 0; i < n; i++)
		{
			scanf("%lld", &b[i]);
		}
		
		sort(b.begin(), b.end());
		mal.clear();
		mal.resize(n);
		
		mal[n - 1] = a[n - 1] - n;	
		for (int i = n - 2; i >= 0; i--)
		{
			mal[i] = max(mal[i + 1], a[i] - (i + 1));
		}
		
		ll ans = mal[b[0] - 1];
		ll mar = ans - (n + 1);
		for (int i = 1; i < n; i++)
		{
			ll idx = n + i + 1;
			ll now = max(mal[b[i] - 1], mar);
			ans += now;
			ans %= P;
			mar = max(mar, now - idx);
		}
		
		cout << ans % P << endl; 
	}
}
