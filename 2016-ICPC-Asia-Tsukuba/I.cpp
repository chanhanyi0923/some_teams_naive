#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll extend_gcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1; y = 0;
		return a;
	}
	else
	{
		ll r = extend_gcd(b, a % b, y, x);
		y -= x * (a / b);
		return r;
	}
}

ll line_mod_equation(ll a, ll b, ll n)
{
	//a x % n == b
	//("%lld x %% %lld == %lld\n", a, n, b);
	ll x, y;
	ll d = extend_gcd(a,n,x,y);

	if (b % d == 0)
	{
		x %= n; x += n; x %= n;
		return x * (b / d) % (n / d);
	}
	return 0;
}

const double eps = 1e-15;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		ll a, b;
		cin >> a >> b;
	
		ll x, y;
		ll gcd = extend_gcd(a, b, x, y);
	
		a /= gcd;
		b /= gcd;
		
		//cout << a << ' ' << b << endl;
		ll ans = line_mod_equation(b, a - 1, a);
		x = ans;
		//y = ceil(1.0 * b * x / a + eps);
		y = (b * x + a) / a;

		
		if (abs(a * gcd * y - b * gcd * x) > 50000) {
			puts("4");
			
			int xa = a * gcd, ya = b * gcd - 1;
			int xb = a * gcd - 1, yb = b * gcd;
			//int xd = a, yd = b;
			printf("%d %d\n%d %d\n%lld %lld\n%d %d\n",0,0,xa,ya,a,b,xb,yb);
			
		} else {
			printf("3\n");
			printf("%lld %lld\n", 0ll, 0ll);
			printf("%lld %lld\n", x, y);
			printf("%lld %lld\n", a * gcd, b * gcd);
		}
	}
}

	
