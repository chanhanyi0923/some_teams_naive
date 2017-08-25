#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct ans
{
	int u;
	int d;
};

struct arm
{
	int pos;
	int label;
};

bool cmp(const arm& a, const arm& b)
{
	return a.pos < b.pos;
}


vector<arm> rob;
vector<ans> dp;
int main()
{
	int n, m;
	cin >> n >> m;
	dp.resize(n);
	rob.resize(m);
	//rob 1: between 0 and 1
	for (int i = 0; i < n; i++)
	{
		dp[i].u = dp[i].d = i;
	}
	
	for (int i = 0; i < m; i++)
	{
		cin >> rob[i].pos >> rob[i].label;
	}
	
	sort(rob.begin(), rob.end(), cmp);
	
	for (int i = 0; i < m; i++)
	{
		int x = rob[i].label - 1;
		int y = rob[i].label;
		
		int u = min(dp[x].u, dp[y].u);
		int d = max(dp[x].d, dp[y].d);
		
		dp[x].u = dp[y].u = u;
		dp[x].d = dp[y].d = d;

	}
	
	for (int i = 0; i < n; i++)
	{
		printf("%d", dp[i].d - dp[i].u + 1);
		if (i == n - 1)
		{
			printf("\n");
		}
		else
		{
			printf(" ");
		}
	}
	
	return 0;
}
