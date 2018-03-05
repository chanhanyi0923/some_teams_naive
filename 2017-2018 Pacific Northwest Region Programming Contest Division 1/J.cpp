#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100][100];
char color[100][100];
ll ok[100][100];
int main()
{
	memset(a, 0, sizeof(a));
	int n, m;
	cin >> n >> m;
	getchar();
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			ok[i][j] = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char c;
			c = getchar();
			if (c == 'R')
			{
				for (int ii = i + 1; ii <= n; ii++)
					for (int jj = j + 1; jj <= m; jj++)
					{
						if (color[ii][jj] == 'B')
						{
							cout << 0 << endl;
							return 0;
						}
						color[ii][jj] = 'R';
						ok[ii][jj] = false;
					}
			}
			if (c == 'B')
			{
				for (int ii = i; ii >= 0; ii--)
					for (int jj = j; jj >= 0; jj--)
					{
						if (color[ii][jj] == 'R')
						{
							cout << 0 << endl;
							return 0;
						}
						color[ii][jj] = 'B';
						ok[ii][jj] = false;
					}
			}
		}
		getchar();
	}
	

	
	a[0][m] = 1;
	for (int i = 0; i <= n; i++)
		for (int j = m; j >= 0; j--)
			if (ok[i][j])
			{
				if (i < n)
					a[i + 1][j] += a[i][j];
				if (j > 0)
					a[i][j - 1] += a[i][j];
			}
			

	printf("%lld\n", a[n][0]);
}