#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const double PI = acos(-1);

double X;
double V(double t)
{
	double ret = 4 * X / (X + 1) * (t / 2 * sqrt(1 - t * t) + asin(t) / 2) + (4 / (X + 1) * sqrt((1 - t * t) * (1 - t * t) * (1 - t * t)) / 3);
	//printf("V(%.5lf) = %.5lf\n", t, ret);
	return ret;
}	
double D(double x)
{
	X = x;
	double v = V(x) - V(-1);
	return v / PI;
}

double S(double x)
{
	return x * sqrt(1 - x * x) + asin(x) + PI / 2;
}

double A(double x)
{
	if (x - (-1) < 1e-7)
	{
		return 0;
	}
	return sqrt(x * x + 2 * x + 5) * S(x) / (x + 1);
}

double find_x(double d)
{
	double mi = -1;
	double ma = 1;
	while (ma - mi > 1e-12)
	{
		double mid = (ma + mi) / 2;
		if (D(mid) < d)
		{
			mi = mid;
		}
		else
		{
			ma = mid;
		}
	}
	return (ma + mi) / 2;
}

double Area(double d)
{
	if (d >= 1)
	{
		//printf("d = %.5lf\n", d);
		return sqrt(d * d - 4 * d + 5) * PI;
	}
	else
	{
		double x = find_x(d);
	//	printf("x = %.5lf\n", x);
		return A(x);
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		double d;
		cin >> d;
		printf("%.5lf\n", Area(d));
	}
	
	
}