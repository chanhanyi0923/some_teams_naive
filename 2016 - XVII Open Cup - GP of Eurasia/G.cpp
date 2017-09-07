#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 22000;
const int MAXM = 440000;
struct edge
{
	int x, y;
	int c;
	int f;
	edge *next, *back;
	
	edge (int x, int y, int c, edge *next):x(x), y(y), c(c), f(0), next(next), back(0) {}
	
	void * operator new(size_t, void *p)
	{
		return p;
	}
};

struct Dinic
{

	edge *E[MAXN];
	edge *data;
	char storage[2 * MAXM * sizeof(edge)];
	int s ,t;
	int q[MAXN];
	int d[MAXN];
	void bfs()
	{
		memset(d, -1, sizeof(d));
		int head = 0;
		int tail = 0;
		q[tail++] = s;
		d[s] = 0;
		for(;;)
		{
			int i = q[head++];
			for (edge *e = E[i]; e; e = e->next)
			{
				if (e->c == 0)
				{
					continue;
				}
				int j = e->y;
				if (d[j] == -1)
				{
					d[j] = d[i] + 1;
					q[tail++] = j;
					if (j == t)
					{
						return;
					}
				}
			}
			if (head == tail)
			{
				break;
			}
		}
	}
	
	edge *cur[MAXN];
	edge *path[MAXN];
	int flow()
	{
		int res = 0;
		int path_n;
		for (;;)
		{
			bfs();
			if (d[t] == -1)
			{
				break;
			}
			memcpy(cur, E, sizeof(E));
			path_n = 0;
			int i = s;
			for (;;)
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
						path[k]->f += delta;
						path[k]->back->f -= delta;
					}
					
					path_n = mink;
					i = path[path_n]->x;
					res += delta;
				}
				
				edge*e;
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
					if (path_n == 0)
						break;
					path_n--;
					i = path[path_n] -> x;
				}
			}
		}
		return res;
	}
	
	void init(int _s, int _t)
	{
		s = _s;
		t = _t;
		data = (edge*)storage;
		memset(E, 0, sizeof(E));
	}
	
	void add_edge(int x, int y, int w)
	{
	//	printf("add_edge(%d, %d, %d)\n", x, y, w);
		E[x] = new((void*)data++) edge(x, y, w, E[x]);
		E[y] = new((void*)data++) edge(y, x, 0, E[y]);
		E[x]->back = E[y];
		E[y]->back = E[x];
	}
};

char c[101][101];
int score[101];
Dinic dinic;
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n;
	cin >> n;
	getchar();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c[i][j] = getchar();
		}
		getchar();
	}
	
	
	for (int i = 0; i < n; i++)
	{
		cin >> score[i];
	}
	
	int S = 20001;
	int T = 20002;
	int TEAM = 10000;
	dinic.init(S, T);
	
	for (int i = 0; i < n; i++)
	{
		dinic.add_edge(TEAM + i, T, score[i]);
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int w1, w2;
			switch (c[i][j])
			{
				case '.':
				{
					w1 = w2 = 3;;
					break;
				}
				case 'L':
				{
					w1 = 0;
					w2 = 3;
					break;
				}
				case 'l':
				{
					w1 = 1;
					w2 = 2;
					break;
				}
				case 'w':
				{
					w1 = 2;
					w2 = 1;
					break;
				}
				case 'W':
				{
					w1 = 3;
					w2 = 0;
					break;
				}
			}
			
			dinic.add_edge(S, i * n + j, 3);
			dinic.add_edge(i * n + j, TEAM + i, w1);
			dinic.add_edge(i * n + j, TEAM + j, w2);
		}
	}
	
	//cout << '!' << endl;
	//printf("%d\n", dinic.flow());
	dinic.flow();
	//cout << '!' << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
		//	printf("i = %d, j = %d\n", i, j);
			edge* e = dinic.E[i * n + j];
			switch (e->f)
			{
				case 0:
				{
					c[i][j] = 'W';
					c[j][i] = 'L';
					break;
				}
				case 1:
				{
					c[i][j] = 'w';
					c[j][i] = 'l';
					break;
				}
				case 2:
				{
					c[i][j] = 'l';
					c[j][i] = 'w';
					break;
				}
				case 3:
				{
					c[i][j] = 'L';
					c[j][i] = 'W';
					break;
				}
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << c[i][j];
		}
		cout << endl;
	}
	return 0;
}
