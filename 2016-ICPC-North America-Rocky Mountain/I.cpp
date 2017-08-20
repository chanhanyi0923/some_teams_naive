#include <bits/stdc++.h>

using namespace std;

int n, N;
vector<int> star;

int need_to_delete(int d)
{
	int count = 0;
	int prev = star[0];
	for (int i = 1; i < n; i++)
	{
		if (star[i] - prev < d)
		{
			count++;
		}
		else
		{
			prev = star[i];
		}
	}
	return count;
}

bool isAllowed(int d)
{
	if (need_to_delete(d) > n / 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main()

{
	while (cin >> N, N != 0)
	{
		n = (1 << N) + 1;
		star.resize(n);
		for (int i = 0; i < n; i++)
		{
			cin >> star[i];
		}
		
		sort(star.begin(), star.end());
		
		int maxD = 0x7fffffff;
		int minD = 0;
		int d;
		while (maxD - minD > 1)
		{
			//printf("maxD = %d, minD = %d\t", maxD, minD);
			d = (maxD + minD) / 2;
			if (isAllowed(d))
			{
				minD = d;
				//printf("isAllowed(%d) = true\n", d);
			}
			else
			{
				maxD = d - 1;
				//printf("isAllowed(%d) = false\n", d);
			}
		}
		
		if (isAllowed(maxD))
		{
			cout << maxD << endl;
		}
		else
		{
			cout << minD << endl;
		}
		
	}
}

