#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 11000, MAXM = 100000;
int N, Q, S;
struct Dinic
{
	struct edge
	{
		int x, y;
		int c;
		edge *next, *back;
		edge (int x, int y, int c, edge *next):x(x), y(y), c(c), next(next), back(0){}
		
		void *operator new(size_t, void *p)
		{
			return p;
		}
	};
	
	edge *E[MAXN], *data;
	
	char storage[2 * MAXM * sizeof(edge)];
	
	int s, t;
	
	int q[MAXN];
	int d[MAXN];
	
	void bfs()
	{
		memset(d, -1, sizeof(d));
		int head = 0, tail = 0;
		q[tail++] = s;
		d[s] = 0;
		for(;;)
		{
			int i = q[head++];
			for (edge *e = E[i]; e; e = e->next)
			{
				if (e->c == 0)
					continue;
				int j = e->y;
				if (d[j] == -1)
				{
					d[j] = d[i] + 1;
					q[tail++] = j;
					if (j == t)
						return;
				}
			}
			if (head == tail)
				break;
		}
	}
	
	edge *cur[MAXN];
	edge *path[MAXN];
	
	int flow()
	{
		int res = 0;
		int path_n;
		for(;;)
		{
			bfs();
			if (d[t] == -1)
				break;
			memcpy(cur, E, sizeof(E));
			path_n = 0;
			int i = s;
			for(;;)
			{
				if (i == t)
				{
					int mink = 0;
					int delta = INT_MAX;
					for (int k = 0; k < path_n; k++)
					{
						if (path[k]->c < delta)
						{
							delta = path[k]->c;
							mink = k;
						}
					}
					
					for (int k = 0; k < path_n; k++)
					{
						path[k]->c -= delta;
						path[k]->back->c += delta;
					}
					
					path_n = mink;
					i = path[path_n]->x;
					res += delta;
				}
				
				edge *e;
				for (e = cur[i]; e; e = e->next)
				{
					if (e->c == 0)
						continue;
					int j = e->y;
					if (d[i] + 1 == d[j])
						break;
				}
		
				cur[i] = e;
				if (e)
				{
					path[path_n++] = e;
					i = e->y;
				}
				else
				{
					d[i] = -1;
					if(path_n == 0)
						break;
					path_n--;
					i = path[path_n]->x;
				}
			}
		}
		return res;
	}


	void init(int _s, int _t)
	{
		s = _s;
		t = _t;
		data = (edge *)storage;
		memset(E, 0, sizeof(E));
	}

	void add_edge(int x, int y, int w)
	{
		//printf("add_edge(%d, %d, %d)\n", x, y, w);
		E[x] = new((void*)data++) edge(x, y, w, E[x]);
		E[y] = new((void*)data++) edge(y, x, 0, E[y]);
		E[x]->back = E[y];
		E[y]->back = E[x];
	}
};
