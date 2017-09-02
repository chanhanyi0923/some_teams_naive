#include <bits/stdc++.h>
using namespace std;

const int max_rating = 1040000;
struct citizen
{
	int cf;
	int tc;
	int num;
	int num_cf;
	int ans;
};
vector<citizen> l;
#define SIZE 100010

vector<int> G[SIZE], S;
int dfn[SIZE], low[SIZE], cpn[SIZE], cpn_sz[SIZE];
bool inS[SIZE];

void init(int N)
{
	S.clear();
	for (int i = 0; i < N + 3; i ++) {
		G[i].clear();
		dfn[i] = low[i] = cpn[i] = -1; cpn_sz[i] = 0;
		inS[i] = false;
	}
}

int dfs(int v, int &o)
{
	
	if (low[v] != -1) return low[v];
	dfn[v] = low[v] = o ++;
	S.push_back(v);
	inS[v] = true;
	for (size_t i = 0; i < G[v].size(); i ++) {
		int u = G[v][i];
		dfs(u, o);
		if (inS[u]) low[v] = min(low[v], low[u]);
	}
	if (low[v] == dfn[v]) {
		int u;
		do {

			u = S.back(); S.pop_back();

			cpn[u] = v; cpn_sz[v] ++;
			inS[u] = false;
		} while (u != v);
	}
	return low[v];
}

bool cmpcf(const citizen& a, const citizen& b)
{
	return a.cf < b.cf;
}

bool cmptc(const citizen& a, const citizen& b)
{
	return a.tc < b.tc;
}

bool cmpnum(const citizen& a, const citizen& b)
{
	return a.num < b.num;
}

void add_edge(int x, int y)
{
	G[x].push_back(y);
	//printf("add %d->%d\n", x, y);
}

int main()
{
	freopen("codecoder.in", "r", stdin);
	freopen("codecoder.out", "w", stdout);
	int n;
	cin >> n;
	l.resize(n);
	init(n);

	for (int i = 0; i < n; i++)
	{
		cin >> l[i].cf >> l[i].tc;
		l[i].num = i;
		l[i].ans = 0;
	}

	S.resize(n, 0);
	
	sort(l.begin(), l.end(), cmpcf);
	for (int i = 0; i < n - 1; i++)
	{
		l[i].num_cf = i;
		add_edge(i, i + 1);
	}
	l[n - 1].num_cf = n - 1;
	
	
	sort(l.begin(), l.end(), cmptc);
	for (int i = 0; i < n - 1; i++)
	{
		add_edge(l[i].num_cf, l[i + 1].num_cf);
	}
	

	int _ = 0; dfs(0, _);
	
	
	int ans = 0;
	int now_cpn = -1;

	sort(l.begin(), l.end(), cmpcf);
	for (int i = 0; i < n; i++)
	{
		if (cpn[i] != now_cpn);
		{
			ans += cpn_sz[i];
		}
		l[i].ans = ans - 1;
	}
	
	sort(l.begin(), l.end(), cmpnum);

	for (int i = 0; i < n; i++)
	{
		printf("%d\n", l[i].ans);
	}
}
