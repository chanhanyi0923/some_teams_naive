#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 20100;
const int maxm = 100000;
const ll inf = 1ll << 60;
ll flow = 0;
struct Edge
{
	Edge() {};
	Edge(int a, int b, ll c, int d) {v = a; f = b; w = c; next = d;};
	int v, f, next;
	ll w;
};

int n,lmt;
int g[maxn + 10];
Edge e[maxm + 10];
int nume;
int src, sink;
queue<int> que;
bool inQue[maxn + 10];
ll dist[maxn + 10];
int _prev[maxn + 10], pree[maxn + 10];

void init()
{
	n = 0;
	lmt = 0;
	memset(g, 0, sizeof(g));
	memset(e, 0, sizeof(e));
	nume = 1;
	src = 0;
	sink = 0;
	flow = 0;
	memset(inQue, 0, sizeof(inQue));
	memset(dist, 0, sizeof(dist));
	memset(_prev, 0, sizeof(_prev));
	memset(pree, 0, sizeof(pree));
}

void add_edge(int u, int v, int c, ll w)
{
	//printf("add_edge(%d, %d, %d, %d)\n", u, v, c, w);
	e[++nume] = Edge(v, c, w, g[u]);
	g[u] = nume;
	e[++nume] = Edge(u, 0, -w, g[v]);
	g[v] = nume;
}


bool findPath()
{
	while (!que.empty())
		que.pop();
	que.push(src);
	memset(dist, 63, sizeof(dist));
	dist[src] = 0;
	inQue[src] = true;
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		for (int i = g[u]; i; i = e[i].next)
		{
			if (e[i].f > 0 && dist[u] + e[i].w < dist[e[i].v])
			{
				dist[e[i].v] = dist[u] + e[i].w;
				_prev[e[i].v] = u;
				pree[e[i].v] = i;
				if (!inQue[e[i].v])
				{
					inQue[e[i].v] = true;
			//		printf("inQue[%d] = true\n", e[i].v);
			//		printf("dist[e[i].v] = %d\n", dist[e[i].v]);
			
					que.push(e[i].v);
				}
			}
		}
		inQue[u] = false;
	//	printf("inQue[%d] = false\n", u);
	}
	if (dist[sink] < inf)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int augment()
{
	int u = sink;
	ll delta = inf;
	while (u != src)
	{
		if (e[pree[u]].f < delta)
			delta = e[pree[u]].f;
		u = _prev[u];
	}
	u = sink;
	while (u != src)
	{
		e[pree[u]].f -= delta;
		e[pree[u] ^ 1].f += delta;
		u = _prev[u];
	}
	flow += delta;
	//printf("delta = %d\n", delta);
	return dist[sink] * delta;
}

ll mincostflow()
{
	ll cur = 0;
	ll ans = inf;
	while (findPath())
	{
		cur += augment();
	//	printf("cur = %d\n", cur);
		if (cur < ans)
			ans = cur;
	}
	return cur;
}

map<string, int> M;

int main()
{
	int t;
	cin >> t;
	int k;
	while (t--)
	{
		init();
		k = 0;
		M.clear();
		int m;
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			string s1, s2;
			cin >> s1 >> s2;
			int u, v;
			if (M.count(s1) > 0)
			{
				u = M[s1];
			}
			else
			{
				u = k++;
				M[s1] = u;
				add_edge(u, u + 10000, 1, 0);
			
			}
			
			if (M.count(s2) > 0)
			{
				v = M[s2];
			}
			else
			{
				v = k++;
				M[s2] = v;
				add_edge(v, v + 10000, 1, 0);
			}
			
			int w;
			cin >> w;

			add_edge(u + 10000, v, 1, w);
			add_edge(v + 10000, u, 1, w);
		}
		int sh;
		int dl;
		int xa;
		if (M.count("Shanghai"))
		{
			sh = M["Shanghai"];
		}
		else
		{
			printf("-1\n");
			continue;
		}
		
		if (M.count("Dalian"))
		{
			dl = M["Dalian"];
		}
		else
		{
			printf("-1\n");
			continue;
		}
		
		if (M.count("Xian"))
		{
			xa = M["Xian"];
		}
		else
		{
			printf("-1\n");
			continue;
		}
		
		src = 20001;
		sink = 20002;
		add_edge(src, sh + 10000, 2, 0);
		add_edge(xa, sink, 1, 0);
		add_edge(dl, sink, 1, 0);
		
		ll ans = mincostflow();
		if (flow < 2)
		{
			printf("-1\n");
		}
		else
		{
			printf("%lld\n", ans);
		}
	}
}
