#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll getF(int s)
{
	if (s == 0) return 0;
	char dig[20];
	int i;
	for (i = 0; i < 20; i ++) {
		if (s >= 9) {
			dig[i] = 9;
			s -= 9;
		} else {
			dig[i] = s;
			break;
		}
	}
	ll x = 0;
	for (; i > -1; i --) {
		x = x * 10 + dig[i];
	}
	return x;
}

ll nextD(ll x, int s)
{
	char buf[20];
	sprintf(buf, "%lld", x);
	int len = strlen(buf);

	bool f = false; int p;
	for (int i = len - 2; i > -1; i --) {
		if (buf[i] != '9' && buf[i + 1] != '0') {
			p = i;
			buf[i] ++;
			buf[i + 1] --;
			f = true;
			break;
		}
	}
	if (f) {
		int q = 0;
		for (int i = p + 1; i < len; i ++) {
			q += buf[i] - '0';
		}
		int qq = getF(q);
		for (int i = p + 1; i < len; i ++) buf[i] = '0';
		for (int i = len - 1; qq > 0; i --) {
			buf[i] = '0' + qq % 10;
			qq /= 10;
		}
	} else {
		int qq = getF(s - 1);
		len ++;

		for (int i = 0; i < len; i ++) buf[i] = '0';
		for (int i = len - 1; qq > 0; i --) {
			buf[i] = '0' + qq % 10;
			qq /= 10;
		}
		buf[0] = '1';
	}

	ll y = 0;
	for (int i = 0; i < len; i ++) {
		y = y * 10ll + buf[i] - '0';
	}
	return y;
}

int main()
{
	freopen("digits.in", "r", stdin);
	freopen("digits.out", "w", stdout);
	int N;
	scanf("%d", &N);
	ll ans = (1ll << 62);
	for (int s = 1; s < 90; s ++) {
		ll x = getF(s);

		ll sum = 0;
		//printf("s: %d\n", s);
		//
		//vector<ll> V; V.clear();
		//		
		for (int i = 0; i < N; i ++) {
		//V.push_back(x);
			//printf("%lld\n", x);
			sum += x;
			//printf("%lld\n", x);
			x = nextD(x, s);
			if (x > (1ll << 55) || (sum > (1ll << 55))) {
				sum = (1ll << 62);
				break;
			}
		}
		/*printf("! %d %lld\n", s, sum);
		if (sum < 0) {
			for (int i = 0; i < V.size(); i ++) printf("%lld\n", V[i]);
		}
		*/
		ans = min(ans, sum);
	}
	printf("%lld\n", ans);
	return 0;
}
