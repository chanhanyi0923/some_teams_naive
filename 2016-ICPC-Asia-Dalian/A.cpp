#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> G[1200];
vector<int> c;
vector<bool> vis;

bool dfs(int s, int color)
{
	//printf("dfs(%d, %d)\n", s, color);
	vis[s] = true;
	if (c[s] == 0)
	{
		c[s] = color;
	}
	else if (c[s] != color)
	{
	//	puts("C1");
		return false;
	}
	
	for (int i = 0; i < G[s].size(); i++)
	{
		int j = G[s][i];
		if (vis[j])
		{
			if (c[j] == color)
				return false;
			continue;
		}
		if (!dfs(j, color == 1 ? 2 : 1))
		{
	//		puts("C2");
			return false;
		}
	}
	return true;
}
int main()
{
	int n, m, x, y;
	while (cin >> n >> m >> x >> y)
	{
		bool fail = false;
		c.clear();
		vis.clear();
		c.resize(n + 1, 0);
		vis.resize(n + 1, 0);
		for (int i = 1; i <= n; i++)
		{
			G[i].clear();
		}
		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		for (int i = 0; i < x; i++)	
		{
			int t;
			cin >> t;
			if (c[t] == 2 || !dfs(t, 1))
				fail = true;
		}
		
		for (int i = 0; i < y; i++)
		{
			int t;
			cin >> t;
			if (c[t] == 1 || !dfs(t, 2))
				fail = true;
		}
		
		//puts("ok");
		for (int i = 1; i <= n; i++)
		{
			if (c[i] == 0 && G[i].size() == 0)
			{
				fail = true;
			}
			if (c[i] == 0 && G[i].size() != 0)
			{
				if (!dfs(i, 1))
				{
					fail = true;
				}
			}
		}
		
		//success
		if (!fail)
		{
			puts("YES");
		}
		else
		{
			puts("NO");
		}
	}
}