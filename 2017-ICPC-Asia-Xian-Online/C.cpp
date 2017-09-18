#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int digit(int x)
{
	int ret = 0;
	while (x > 0)
	{
		x /= 10;
		ret++;
	}
	return ret;
}


void solve(int x)
{
	int d = digit(x);
	for (int i = 0; i < 232; i++)
	{
		cout << '1';
		for (int j = 0; j < d - 1; j++)
		{
			cout << '0';
		}
	}
	cout << '1';
	cout << endl;
}

int main()
{
	int x;
	int t;
	cin >> t;
	while (cin >> x)
	{
		solve(x);
	}
}	
