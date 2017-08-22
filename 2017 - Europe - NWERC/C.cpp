#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct sheld
{
	int l;
	int r;
	double f;
};

vector<sheld> s;
int outside_time;

double pos(double vx)
{
	double ans = vx * outside_time;
	for (int i = 0; i < s.size(); i++)
	{
		ans += (s[i].r - s[i].l) * vx * s[i].f;
	}
	
	return ans;
}

int main()
{
	int n, x, y;
	cin >> x >> y >> n;
	s.resize(n);
	if (x == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	
	int sign = x / abs(x);
	x = abs(x);
	
	outside_time = y;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i].l >> s[i].r >> s[i].f;
		outside_time -= s[i].r - s[i].l;
	}
	
	double ep = 1e-12;
	double ma = 1e10;
	double mi = 0;
	double now = (ma + mi / 2);
	while (ma - mi > ep)
	{
		if (pos(now) > x)
		{
			ma = now;
		}
		else
		{
			mi = now;
		}
		now = (ma + mi) / 2;
	}
	
	now *= sign;
	printf("%.10lf\n", now);
}
