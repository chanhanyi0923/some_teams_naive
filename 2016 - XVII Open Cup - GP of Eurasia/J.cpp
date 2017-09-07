#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n;
struct point 
{
	ll x;
	ll y;
	point():x(0), y(0){}
};

bool cmpx(const point& a, const point& b)
{
	return a.x < b.x;
}

bool cmpy(const point& a, const point&b)
{
	return a.y < b.y;
}

vector<point> p;

ll calc(ll minY)
{
	ll maxY = minY + n - 1;
	ll ret = 0;
	for (ll i = 0, j = minY; j <= maxY; i++, j++)
	{
		ret += abs(p[i].y - j);
	}
	
	return ret;
}

ll solvex()
{
	sort(p.begin(), p.end(), cmpx);
	ll midx = p[(n - 1) / 2].x;
	
	ll Xstep = 0;
	ll Ystep = 0;
	for (int i = 0; i < n; i++)
	{
		Xstep += abs(p[i].x - midx);
	}
	
	sort(p.begin(), p.end(), cmpy);
	/*ll midy = p[(n - 1) / 2].y;
	
	ll minY = midy - (n / 2);
	ll maxY = minY + n - 1;
	
	for (ll i = 0, j = minY; j <= maxY; i++, j++)
	{
		Ystep += abs(p[i].y - j);
	}
	
	ll Ystep2 = 0;
	minY++;
	maxY++;
	for (ll i = 0, j = minY; j <= maxY; i++, j++)
	{
		Ystep2 += abs(p[i].y - j);
	}*/
	
	ll mi = -1000000000;
	ll ma = 1000000000;
	ll m1;
	ll m2;
	//printf("calc(0) = %lld\n", calc(0));
	while (ma - mi > 2)
	{
		m1 = (mi * 2 + ma) / 3;
		m2 = (mi + 2 * ma) / 3;
		ll f1 = calc(m1);
		ll f2 = calc(m2);
//
	//	printf("mi = %lld, m1 = %lld, m2 = %lld, ma = %lld\n", mi, m1, m2, ma);
	//	printf("f1 = %lld, f2 = %lld\n", f1, f2);
		if (f1 > f2)
		{
	//		printf("f1 > f2\n");
			mi = m1;
		}
		if (f1 < f2)
		{
		//	printf("f1 < f2\n");
			ma = m2;
		}
		if (f1 == f2)
		{
			mi = m1;
			ma = m2;
		}
	}
	
	Ystep = min(min(calc(m1), calc(m1 + 1)), calc(m2));
//	printf("----------ans = %lld-------------\n", Xstep + Ystep);
	return Xstep + Ystep;
	
}

ll solvey()
{
	for (int i = 0; i < n; i++)
	{
		swap(p[i].x, p[i].y);
	}
	return solvex();
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	cin >> n;
	p.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> p[i].x >> p[i].y;
	}
	
	ll ans = solvex();
	ans = min(ans, solvey());
	cout << ans << endl;	
}
