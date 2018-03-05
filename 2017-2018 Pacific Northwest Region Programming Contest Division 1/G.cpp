#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct edge
{
	int u;
	int v;
	int l;
	int r;
	edge():u(0), v(0), l(0), r(0){}
	edge(int U, int V, int L, int R):u(U), v(V), l(L), r(R) {}
};

vector<edge> G[1001];
vector<edge> e;
set<int> key;
vector<int> people;
map<int, int> rnk;
int n, m, k;
int s, t;

bool vis[1001];

bool bfs(int p)
{
	queue<int> q;
	memset(vis, 0, sizeof(vis));
	q.push(s);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = true;
		for (int i = 0 ;i < G[u].size(); i++)
		{
			int v = G[u][i].v;
			if (!vis[v] && G[u][i].l <= p && p < G[u][i].r)
			{
				vis[v] = true;
				q.push(v);
				if (v == t)
					return true;
			}
		}
	}
	return false;
}
int main()
{
	cin >> n >> m >> k;
	cin >> s >> t;
	key.insert(1);
	key.insert(k + 1);
	for (int i = 0; i < m; i++)
	{
		int u, v, l, r;
		cin >> u >> v >> l >> r;
		r++;
		e.push_back(edge(u, v, l, r));
		key.insert(l);
		key.insert(r);
	//	printf("%d", key.size());
	}
	
	int r = 0;
	//printf("key.size() = %d\n", key.size());
	for (auto p = key.begin(); p != key.end(); ++p)
	{
		//printf("rnk[%d] = %d\n", *p, r);
		rnk[*p] = r++;
		auto q = p;
		q++;
		if ((q) != key.end())
			people.push_back(*q - *p);
	}
	
	for (int i = 0; i < m; i++)
	{
		int u = e[i].u;
		int v = e[i].v;
		int l = rnk[e[i].l];
		int r = rnk[e[i].r];
		G[u].push_back(edge(u, v, l, r));
	}
	

	ll sum = 0;
	for (int i = 0; i < people.size(); i++)
	{
		if (bfs(i))
		{
			sum += people[i];
		//	printf("bfs(%d), sum += %d\n", i, people[i]);
		}
	}
	
	cout << sum << endl;
}