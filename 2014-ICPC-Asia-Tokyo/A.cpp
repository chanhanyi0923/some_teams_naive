#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, m;
int solve(vector<int> a, vector<int> b)
{
	int sum0 = 0;
	int sum1 = 0;
	for (int i = 0; i < m; i += 2)
	{
		sum0 += b[i];
		if (i + 1 < m)
			sum1 += b[i + 1];
	}
	
	int cnt0 = 0;
	int cnt1 = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 0)
			cnt0++;
		else
			cnt1++;
	}
	
	if ((sum0 != cnt0) || (sum1 != cnt1))
		return INT_MAX;
	
	vector<int> k0;
	vector<int> k1;
	int cnt = 0;
	int now = 0;
	for (int i = 0; i < m; i++)
	{
		if (now == 0)
		{
			for (int j = 0; j < b[i]; j++)
				k0.push_back(cnt++);
		}
		else
		{
			for (int j = 0; j < b[i]; j++)
				k1.push_back(cnt++);
		}
		now ^= 1;
	}
	
	int c0 = 0;
	int c1 = 0;
	
	for (int i = 0; i < n; i++)
	{
		if (a[i] == 0)
		{
			a[i] = k0[c0++];
		}
		else
		{
			a[i] = k1[c1++];
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				ans++;
			}
		}
	}
	
	return ans;
}

int main()
{
	vector<int> a;
	vector<int> b;

	while (cin >> n >> m)
	{
		a.clear();
		a.resize(n);
		b.clear();
		b.resize(m);
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < m; i++)
			cin >> b[i];
		
		int x = solve(a, b);
		for (int i = 0; i < n; i++)
		{
			a[i] ^= 1;
		}
		x = min(x, solve(a, b));
		cout << x << endl;
	}
	return 0;
}

