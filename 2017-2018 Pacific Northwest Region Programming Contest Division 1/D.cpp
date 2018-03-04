#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:134217728")
using namespace std;

struct edge
{
	int u;
	int v;
	int c;
	bool l;
	edge() :u(0), v(0), c(0), l(false){}
	edge(int U, int V, int C):u(U), v(V), c(C), l(false){}
};

vector<edge> e;

vector<int> G[50001];
vector<int> start[50001];
vector<int> color[50001];
vector<bool> vis(50001);
vector<bool> ban(50001);
vector<int> ans;
void find_start(int root)
{
	for (int i = 0; i < G[root].size(); i++)
	{
		int k = G[root][i];
		int v = e[k].v;
		int c = e[k].c;
		color[c].push_back(v);
	}

	for (int i = 0; i < G[root].size(); i++)
	{
		int k = G[root][i];
		int v = e[k].v;
		int c = e[k].c;
		if (color[c].size() >= 2)
		{
			start[root].push_back(v);
		}
	}

	for (int i = 0; i < G[root].size(); i++)
	{
		int k = G[root][i];
		int c = e[k].c;
		color[c].clear();
	}
}


bool dfs(int u)
{
	bool ret = true;
	vis[u] = true;
	ban[u] = true;
	for (int i = 0; i < G[u].size(); i++)
	{
		int k = G[u][i];
		int v = e[k].v;
		if (vis[v])
		{
			continue;
		}
		if (e[k].l)
		{
			continue;
		}
		e[k].l = true;
		if (e[k ^ 1].l)
		{
			ret = false;
			break;
		}
		ret &= dfs(v);
	}
	vis[u] = false;
	return ret;
}

bool solve(int root)
{
	bool ret = true;
	vis[root] = true;
	for (int i = 0; i < start[root].size(); i++)
	{
		ret &= dfs(start[root][i]);
	}
	vis[root] = false;
	return ret;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		e.push_back(edge(a, b, c));
		e.push_back(edge(b, a, c));
		G[a].push_back(i * 2);
		G[b].push_back(i * 2 + 1);
	}

	for (int i = 1; i <= n; i++)
	{
		find_start(i);
	}

	for (int i = 1; i <= n; i++)
	{
		if (solve(i) == false)
		{
			cout << 0 << endl;
			return 0;
		}
	}

	vector<int> ans;
	for (int i = 1; i <= n; i++)
	{
		if (!ban[i])
		{
			ans.push_back(i);
		}
	}

	cout << ans.size() << endl;
	for (int i = 0 ; i < ans.size(); i++)
	{
		cout << ans[i] << endl;
	}
//	system("pause");
	return 0;
}
