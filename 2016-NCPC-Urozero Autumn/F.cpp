#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int n, p;

double cal(ll x)
{
	double ans = 1.0 * p * x / (n + x);
	for (int i = 0; i < p - 1; i ++) {
		ans *= 1.0 * (n - i) / (n + x - 1 - i);
	}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &p);
	ll l = 1, r = 1000000000ll * 1000000000ll;
	double t1 = -1;
	for (ll i = 1; i < (1ll << 61); i *= 2) {
		double t2 = cal(i);
		if (t2 < t1) {
			r = i;
			break;
		}
		t1 = t2;
	}
	while (l + 5 < r) {
		ll ml = (2 * l + r) / 3, mr = (l + 2 * r) / 3;
		if (cal(ml) < cal(mr)) {
			l = ml;
		} else {
			r = mr;
		}
	}
	double ans = 0;
	for (int i = l; i <= r; i ++) {
		ans = max(ans, cal(i));
	}
	printf("%.15lf\n", ans);
	return 0;
}
