#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> m >> n;
	while (n != 0 && m != 0)
	{
		int a[20];
		for (int i = 0; i < m; i++)
		{
			cin >> a[i];
		}
		
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			bool flag = true;
			for (int j = 0; j < m; j++)
			{
				int t;
				cin >> t;
				if (t > a[j])
				{
					flag = false;
				}
			}
			if (flag)
				ans++;
		}
		
		cout << ans << endl;
		cin >> m >> n;
	}
}
