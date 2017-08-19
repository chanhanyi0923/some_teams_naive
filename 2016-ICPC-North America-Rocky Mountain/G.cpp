#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	
	vector<int> stage;
	stage.resize(m, 0);
	
	for (int i = 0; i < n; i++)
	{
		int t;
		cin >> t;
		stage[0] += t;
		for (int j = 1; j < m; j++)
		{
			cin >> t;
			if (stage[j - 1] > stage[j])
			{
				stage[j] = stage[j - 1] + t;
			}
			else
			{
				stage[j] = stage[j] + t;
			}
		}
	//	for (int i = 0; i < m; i++)
		//{
	//		printf("%d ", stage[i]);
	//	}
	//	printf("\n");
	
		if (i != n - 1)
		{
			printf("%d ", stage[m - 1]);
		}
		else
		{
			printf("%d", stage[m - 1]);
		}
	}
	return 0;
}