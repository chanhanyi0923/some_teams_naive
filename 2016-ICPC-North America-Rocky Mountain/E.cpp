#include <bits/stdc++.h>

using namespace std;
#define eps 1e-12
struct func
{
	double a;
	double b;
	double c;
	
	double A;
	double B;
	
	double f(double x)
	{
		return a * x * x + b * x + c;
	}
};

vector<func> f;
int n;
int T;
double calc(double D)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		double t = (D - f[i].B) / f[i].A;
		if (t > 0)
		{
			sum += f[i].f(t);
		}
		else
		{
			sum += f[i].f(0);
		}
	}
	return sum;
}

bool isAllowed(double D)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		double t = (D - f[i].B) / f[i].A;
		if (t > 0)
		{
			sum += t;
		}
	}
	//printf("idAllowed(%lf) = %d, sum = %lf, T = %d\n", D, sum <= T, sum, T);
	return (sum <= T);
}

int main()
{

	cin >> n >> T;
	f.resize(n);
	
	double maxB = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> f[i].a >> f[i].b >> f[i].c;
		f[i].A = 2 * f[i].a;
		f[i].B = f[i].b;
		
		if (f[i].B > maxB)
		{
			maxB = f[i].B;
		}
	}
	
	double min = 0;
	double max = maxB;
	double D = (max + min) / 2;
	double prevD = 0;
	while (abs(calc(D) - calc(prevD)) > eps)
	{
		if (isAllowed(D))
		{
			max = D;
		}
		else
		{
			min = D;
		}
		prevD = D;
		D = (min + max) / 2;
	}
	
	printf("%.10lf\n", calc(D) / n);
	return 0;
}