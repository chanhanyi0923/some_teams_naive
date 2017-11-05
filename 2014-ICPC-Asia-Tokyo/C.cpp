#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> vis;
	vis.resize(2 * n + 100, false);
	
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		for (int j = 2 * x; j <= 2 * y - 1; j++)
		{
			vis[j] = true;
		}
	}	
	int ans = n + 1;
	int i = 0;
	for (int i = 0; i < vis.size(); i++)
	{
		if (vis[i])
			ans++;
	}
	cout << ans << endl;
}