#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int a[100][100];
int b[100][100];

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				a[i][j] = 0;
				b[i][j] = 0;
			}
		}
		
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			a[x][y] = 1;
		}
		
		for (int j = 0; j < m; j++)
		{
			int x, y;
			cin >> x >> y;
			b[x][y] = 1;
		}
		
		for (int i = 1; i <= 50; i++)
		{	
			for (int k = 1; k <= 50; k++)
			{
				bool c = true;
				for (int j = 1; j <= 50; j++)
				{
					if (a[i][j] && b[j][k])
					{
						printf("%d %d\n", i, k);
						c = false;
						break;
					}
				}
				if (!c)
					continue;
			}
		}
		
		printf("\n");
	}
	
	return 0;
}
