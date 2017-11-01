#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll dp1[25][10];
ll dp2[25][10];
vector<ll> num;

void build()
{
	for (int i = 0; i < 10; i ++) {
		dp1[0][i] = dp2[0][i] = 0;
		dp1[1][i] = dp2[1][i] = 1;
	}
	for (int i = 2; i < 25; i ++) {
		for (int j = 0; j < 10; j ++) {
			for (int k = j; k < 10; k ++) {
				dp1[i][j] += dp1[i - 1][k];
			}
			//printf("dp1[%d][%d] = %lld\n", i, j, dp1[i][j]);
		}
	}
	for (int i = 2; i < 25; i ++) {
		for (int j = 0; j < 10; j ++) {
			for (int k = j; k >= 0; k --) {
				dp2[i][j] += dp2[i - 1][k];
			}
			//printf("dp2[%d][%d] = %lld\n", i, j, dp2[i][j]);
		}
	}
	num.push_back(0);
	for (int k = 1; k < 25; k ++) {
		for (int i = 1; i < 10; i ++) {
			ll x = 0;
			for (int j = 0; j < k; j ++) x = x * 10 + i;
			if (x > 1000000000ll * 1000000000ll) return;
			//printf("%lld\n", x);
			num.push_back(x);
		}
	}
}

ll f(ll N)
{
	if (N < 100) return N + 1;
	if (N == 1000000000000000000ll) return f(999999999999999999ll) + 1;
	ll ans = 0;

	//sub
	vector<ll>::iterator it = lower_bound(num.begin(), num.end(), N);
	if (it != num.end() && *it > N) ans ++;
	ans -= 1 + (int)(it - num.begin());

	int sz = 0;
	int a[25];
	{
		int ___a[25];
		for (; N > 0; N /= 10) ___a[sz ++] = N % 10;
		for (int i = 0; i < sz; i ++) a[i] = ___a[sz - i - 1];
	}

	{
		for (int j = 0; j < a[0]; j ++) ans += dp1[sz][j];
		for (int i = 1; i < sz; i ++) {
			if (a[i - 1] <= a[i]) {
				for (int j = a[i - 1]; j < a[i]; j ++) {
					ans += dp1[sz - i][j];
				}
				if (i == sz - 1) ans ++;
			} else {
				break;
			}
		}
	}
	//printf("%lld\n", ans);	
	{
		for (int j = 1; j < a[0]; j ++) ans += dp2[sz][j];
		//ans += dp2[sz][9];
		for (int i = 1; i <= sz - 1; i ++) {
			//ans += dp2[i][9];
			for (int j = 1; j <= 9; j ++) ans += dp2[i][j];
		}
		ans ++;
		//printf("~~~ %lld\n", dp2[sz][9]);
		//
		//printf("-- %lld\n", ans);
		//for (int j = 0; j < 10; j ++) ans += dp2[sz - 1][j];
		for (int i = 1; i < sz; i ++) {
			for (int j = 0; j <= min(a[i - 1], a[i] - 1); j ++) {
				ans += dp2[sz - i][j];
				//printf("! %d %d\n", sz - i, j);
			}
			if (a[i - 1] >= a[i]) {
				if (i == sz - 1) ans ++;
			} else {
				break;
			}
		}
	}
	//printf("%lld\n", ans);
	return ans;
}

int main()
{
	build();
	int T;
	scanf("%d", &T);
	while (T --) {
		ll L, R;
		scanf("%lld%lld", &L, &R);
		printf("%lld\n", f(R) - f(L - 1));
	}
	return 0;
}
