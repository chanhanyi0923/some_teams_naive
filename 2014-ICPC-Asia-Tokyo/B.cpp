#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll getA(char *s)
{
	ll a[100];
	for (int i = 0; i < 100; i ++) a[i] = -1;
	for (int i = 0; s[i]; i ++) {
		if (s[i] == '*') {
			if (a[i - 1] == -1) {
				ll qq = (s[i - 1] - '0') * (s[i + 1] - '0');
				a[i + 1] = qq;
				s[i - 1] = s[i] = s[i + 1] = '.';
			} else {
				ll qq = a[i - 1] * (s[i + 1] - '0');
				a[i + 1] = qq;
				s[i - 1] = s[i] = s[i + 1] = '.';
				a[i - 1] = -1;
			}
		}
	}
	ll ans = 0;
	for (int i = 0; s[i]; i ++) {
		if (a[i] == -1) {
			if (s[i] >= '0' && s[i] <= '9') {
				ans += s[i] - '0';
			}
		} else {
			ans += a[i];
		}
	}
	return ans;
}

ll getB(char *s)
{
	ll k, op = -1;
	for (int i = 0; s[i]; i ++) {
		if (s[i] >= '0' && s[i] <= '9') {
			ll r = 0;
			while (s[i] >= '0' && s[i] <= '9') {
				r = r * 10ll + s[i] - '0';
				i ++;
			}
			if (op != -1) {
				if (op == '+') {
					k = k + r;
				} else {
					k = k * r;
				}
			} else {
				k = r;
			}
			if (s[i] == 0) break;
		}
		if (s[i] == '+') {
			op = '+';
		}
		if (s[i] == '*') {
			op = '*';
		}
	}
	return k;
}

int main()
{
//2147483647
//999999999
	char buf[1005];
	char buf2[1005];
	while (EOF != scanf("%s", buf)) {
		for (int i = 0; i == 0 || buf[i - 1]; i ++) buf2[i] = buf[i];
		int x; scanf("%d", &x);
		ll a = getA(buf2);
		//printf("a = %lld\n", a);
		//puts("!!!!!!");
		ll b = getB(buf);
		//printf("b = %lld\n", b);
		if (a == x && b == x) {
			puts("U");
		} else if (a == x) {
			puts("M");
		} else if (b == x) {
			puts("L");
		} else {
			puts("I");
		}
	}
	return 0;
}
