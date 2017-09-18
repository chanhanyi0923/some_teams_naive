#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll P = 1000000007;

ll L3[100];
ll g[100];
ll Pow(ll x, ll t)
{
	if (t == 0)
		return 1;
	if (t % 2 == 0)
	{
		ll ret = Pow(x, t / 2);
		ret *= ret;
		ret %= P;
		return ret;
	}
	ll ret = Pow(x, t - 1);
	ret *= x;
	ret %= P;
	return ret;
}

void getL3()
{
	L3[0] = 0;
	for (int i = 1; i <= 64; i++)
	{
		L3[i] = 2 * L3[i - 1] + Pow(4, i - 1);
		L3[i] %= P;
	//	cout << L3[i] << endl;
	}
	g[0] = 1;
	for (int i = 1; i <= 64; i++)
	{
		g[i] = g[i - 1] * 2 + 3 * Pow(4, i - 1);
		g[i] %= P;
	//	cout << g[i] << endl;
	}	
}

ll sum(ll t)
{
	if (t == 0)
	{
		return 0;
	}
	int d = 62;
	while (((1ll << d) & t) == 0)
	{
		d--;
	}
	
	//cout << d << endl;
	ll ret = L3[d];
	
	for (d--; d >= 0; d--)
	{
		if (t & (1ll << d))
		{
			ret += g[d];
		}
	}
	ret %= P;
	return ret;
}

ll f(ll n)
{
	return (sum(n - 1) + n - 1) % P;
}
int main()
{
	getL3();
	ll n;
	while (cin >> n)
	{
		cout << f(n) << endl;
	}
}

