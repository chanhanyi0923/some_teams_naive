#include <bits/stdc++.h>
using namespace std;

struct state
{
	int i;
	int j;
	int k;
	state() :i(0), j(0), k(0) {}
	state(int x, int y, int z) :i(x), j(y), k(z) {}
};
vector<int> page;
state from[200010][3][3];
int dp[200010][3][3] = { 0 };
int Min[200010][3] = { 0 };
int Mil[200010][3] = { 0 };

int n;
int digit(int x)
{
	int ret = 0;
	while (x > 0)
	{
		ret++;
		x /= 10;
	}
	return ret;
}

void print()
{
	vector<int> single;
	vector<int> cons;
	vector<int> odd;
	vector<int> even;

	state start(n, 0, 0);
	int mi = dp[n][0][0];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (dp[n][i][j] < mi)
			{
				mi = dp[n][i][j];
				start = state(n, i, j);
			}
		}
	}

	state now = start;
	while (now.i != 0)
	{
		int i = now.i;
		int j = now.j;
		int k = now.k;

		if (j == 0)
		{
			single.push_back(page[i]);
		}
		if (j == 1)
		{
			cons.push_back(page[i]);
		}
		if (j == 2)
		{
			if (page[i] % 2 == 0)
			{
				even.push_back(page[i]);
			}
			else
			{
				odd.push_back(page[i]);
			}
		}

		now = from[i][j][k];
	}

	bool comma = false;
	for (int i = 0; i < single.size(); i++)
	{
		if (comma)
		{
			printf(",");
		}

		printf("%d", single[i]);
		comma = true;
	}

	int i = 0;
	int j = 0;
	while (i < cons.size())
	{
		while (j + 1 < cons.size() && cons[j + 1] == cons[j] - 1)
		{
			j++;
		}
		int l = cons[j];
		int r = cons[i];

		if (comma)
		{
			printf(",");
		}
		printf("%d-%d", l, r);
		i = ++j;
		comma = true;
	}

	i = 0;
	j = 0;
	while (i < even.size())
	{
		while (j + 1 < even.size() && even[j + 1] == even[j] - 2)
		{
			j++;
		}
		int l = even[j];
		int r = even[i];

		if (comma)
		{
			printf(",");
		}
		printf("%d%%%d", l, r);
		i = ++j;
		comma = true;
	}

	i = 0;
	j = 0;
	while (i < odd.size())
	{
		while (j + 1 < odd.size() && odd[j + 1] == odd[j] - 2)
		{
			j++;
		}
		int l = odd[j];
		int r = odd[i];

		if (comma)
		{
			printf(",");
		}
		printf("%d#%d", l, r);
		i = ++j;
		comma = true;
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	cin >> n;
	page.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
	{
		cin >> page[i];
	}

	sort(page.begin() + 1, page.end());
	for (int i = 1; i <= n; i++)
	{
		int now = page[i];

		int prev1 = (i > 1 && page[i - 1] == page[i] - 1) ? i - 1 : -1;
		int prev2 = (i > 1 && page[i - 1] == page[i] - 2) ? i - 1 : -1;
		prev2 = (i > 2 && page[i - 2] == page[i] - 2) ? i - 2 : prev2;

		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				dp[i][j][k] = Min[i - 1][k];
				from[i][j][k] = state(i - 1, k, Mil[i - 1][k]);
				switch (j)
				{
					case 0:
					{
						dp[i][j][k] += digit(now) + 1;
						break;
					}
					case 1:
					{
						dp[i][j][k] += 2 * digit(now) + 2;
						if (prev1 != -1 && k == 1)
						{
							int tmp = Min[i - 1][1] - digit(now - 1) + digit(now);
							if (tmp < dp[i][j][k])
							{
								dp[i][j][k] = tmp;
								from[i][j][k] = state(i - 1, 1, Mil[i - 1][1]);
							}
						}
						break;
					}
					case 2:
					{
						dp[i][j][k] += 2 * digit(now) + 2;
						if (prev2 == -1)
						{
							break;
						}
						if (prev2 != -1)
						{
							if (prev2 == i - 1 && k == 2)
							{
								int tmp = Min[i - 1][2] - digit(now - 2) + digit(now);
								if (tmp < dp[i][j][k])
								{
									dp[i][j][k] = tmp;
									from[i][j][k] = state(i - 1, 2, Mil[i - 1][2]);
								}
							}
							else if (prev2 == i - 2)
							{
								int tmp = dp[i - 1][k][2] - digit(now - 2) + digit(now);
								if (tmp < dp[i][j][k])
								{
									dp[i][j][k] = tmp;
									from[i][j][k] = state(i - 1, k, 2);
								}
							}
						}
						break;
					}
					default:
					{
						break;
					}
				}
			}

			Min[i][j] = dp[i][j][0];
			Mil[i][j] = 0;
			for (int k = 1; k < 3; k++)
			{
				if (dp[i][j][k] <= Min[i][j])
				{
					Min[i][j] = dp[i][j][k];
					Mil[i][j] = k;
				}
			}
		}
	}

	print();
}