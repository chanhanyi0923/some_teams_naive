#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int cost[2000];
int day[2000];
int main()
{
	int now;
	int t;
	int b;
	int n;
	cin >> t;
	while (t--)
	{
		cin >> n >> b;

		for (int i = 0; i < n; i++)
		{
			cin >> cost[i];
		}
		for (int i = 0; i < n - 1; i++)
		{
			cin >> day[i];
		}
		now = cost[0];		
		for (int i = 1; i < n; i++)
		{
			now -= day[i - 1] * b;
		//	printf("i = %d\n, now = %d\n", i, now);
			if (now < 0)
			{
				printf("No\n");
				goto END;
			}
			now += cost[i];
		}
		
		printf("Yes\n");
END:;
	}
	return 0;
}
