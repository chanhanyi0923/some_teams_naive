#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(double a, double b)
{
	return a > b;
}

int main()
{
	vector<double> p;
	
	int n;
	cin >> n;

	p.resize(n);
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		cin >> p[i];
	}
	
	sort(p.begin(), p.end(), cmp);
	
	double ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans += (i + 1) * p[i];
	}
	
	printf("%.4lf\n", ans);
	return 0;
}