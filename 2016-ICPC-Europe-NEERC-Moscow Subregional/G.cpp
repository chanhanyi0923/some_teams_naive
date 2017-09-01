#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int> > plate;

int main()
{
	int n;
	cin >> n;
	plate.resize(n + 1, vector<int>(n + 1, 0));
	
	for (int i = 1; i <= n; i++)
	{
		plate[i][i] = 1;
		plate[i][0] = n - 1;
	}

	for (int i = 1; i <= n - 1; i++)
	{
		if (i == 1)
		{
			puts("1 1 0");
		}
		else
		{
			printf("%d %d %d\n", i, i, n);
		}
		for (int j = i + 1; j <= n - 1; j++)
		{
			printf("%d %d %d\n", j, j, i);
			printf("%d %d %d\n", i, i, j);
		}
		printf("%d %d %d\n", n, n, i);
	}
	printf("%d %d %d\n", 0, 1, n);
	return 0;
}
