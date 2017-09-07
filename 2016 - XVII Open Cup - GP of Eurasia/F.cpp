#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll a[15][7] = {0};

int get_digits(ll x)
{
	//printf("x = %lld\n", x);
	int ret = 0;
	while (x > 0)
	{
		x /= 10;
		ret++;
	}
	return ret;
}

vector<ll> num;
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	num.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> num[i];
	//	printf("num[i] = %lld\n", num[i]);
		int d = get_digits(num[i]);
		a[d][num[i] % 7]++;
		//printf("a[%d][%lld] = %lld\n", d, num[i] % 7, a[d][num[i] % 7]);
	}
	
	ll ans = 0;
	for (int i = 0; i < n; i++)
	{
		ll t = num[i];
	//	printf("num[i] = %lld\n", num[i]);
		int kk = get_digits(t);
		for (int k = 1; k <= 10; k++)
		{
			t *= 10;
			t %= 7;
		//	printf("k = %d, t = %lld\n", k, t);
			int mod = t % 7;
			if (mod != 0)
			{
				mod = 7 - mod;
			}
		//	printf("mod = %d\n", mod);
			//printf("ans += %lld\n", a[k][mod]);
			ans += a[k][mod];
			if (k == kk && (t + num[i]) % 7 == 0)
			{
				ans--;
		//		printf("ans--\n");
			}
		}
	}
	
	cout << ans << endl;
}
