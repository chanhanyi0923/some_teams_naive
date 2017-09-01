#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll P = 1000000007;
vector<int> sign;

void init()
{
	sign.resize(100020);
	for (int now = 2; now < 100020; now++)
	{
		int count = 0;
		for (int k = 2; k <= floor(sqrt(now)); k++)
		{
			if (now % k == 0)
			{
				count += sign[k];
				if (k != now / k)
				{
					count += sign[now / k];
				}
			}
		}
		sign[now] = 1 - count;
	}
}

ll powmp(ll x, ll n)
{
	if (n == 0)
	{
		return 1;
	}

	if (n % 2 == 0)
	{
		ll ret = powmp(x, n / 2);
		ret = ret * ret % P;
		return ret;
	}
	else
	{
		return x * powmp(x, n - 1) % P;
	}
}

vector<int> a;

int main()
{
	init();
#ifdef __LOCAL__
	freopen("input", "r", stdin);
	freopen("output", "w", stdout);
#endif
	int T;
	cin >> T;
	for (int N = 0; N < T; N++)
	{
		int n;
		cin >> n;
		a.clear();
		a.resize(n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}

		sort(a.begin(), a.end());

		ll ans = 0;
		for (int gcd = 2; gcd <= a[0]; gcd++)
		{
			if (sign[gcd] == 0)
				continue;
			ll now_low = a[0] / gcd * gcd;
			ll now_high = now_low + gcd;
			ll now_ans = 1;
			//	printf("gcd = %d\n", gcd);
			vector<int>::iterator ptr1 = a.begin();
			while (true)
			{
				vector<int>::iterator ptr2 = upper_bound(a.begin(), a.end(), now_high - 1);
				ll num = ptr2 - ptr1;
				ll t = now_low / gcd;
				now_ans *= powmp(t, num);
				now_ans %= P;
				//	printf("num = %lld, t = %lld, now_low = %lld, now_high = %lld\n", num, t, now_low, now_high);
				vector<int>::iterator ptr = lower_bound(a.begin(), a.end(), now_high);

				if (ptr == a.end())
				{
					break;
				}

				now_low = *ptr;
				ptr1 = ptr2;
				now_low = now_low / gcd * gcd;
				now_high = now_low + gcd;
			}
			ans += now_ans * sign[gcd];
			ans = (ans + P) % P;
		}
		//printf("%lld\n", ans % P);
		printf("Case #%d: %lld\n", N + 1, ans % P);
	}
}
