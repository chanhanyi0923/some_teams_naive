#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int T[10100][52];
int depth[60];
int fa[60];
int idx[60];
int init[60];
vector<int> sw;
int main()
{
	freopen("instruction.in", "r", stdin);
	freopen("instruction.out", "w", stdout);
	int n;
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		init[i] = 1000;
		depth[i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		char c;
		getchar();
		c = getchar();
		if (c == 's')
		{
			int t;
			cin >> t;
			fa[i] = t;
			init[t] = min(init[t], i);
			sw.push_back(i);
		}
		else
		{
			int t;
			cin >> t;
			fa[i] = t;
			getchar();
			c = getchar();
			idx[c - 'a'] = i;
			init[t] = min(init[t], i);
		}
	}
	
//	for (int i = 0; i <= n; i++)
//	{
//		printf("fa[%d] = %d\n", i, fa[i]);
//	}
	for (int i = 1; i <= n; i++)
	{
		int j = i;
		while (j != 0)
		{
			depth[i]++;
			j = fa[j];
		}
	}
	
//	for (int i = 0; i <= n; i++)
//	{
//		printf("depth[%d] = %d\n", i, depth[i]);
//	}
	int m;
//	for (int i = 0; i <= n; i++)
//	{
//		printf("%d ", init[i]);
//	}
//	printf("\n");
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		getchar();
		char c = getchar();
		int des = idx[c - 'a'];
		int now = des;
		int now_t = t + depth[des];
		while (now != 0)
		{
//			printf("now = %d\n", now);
			now_t--;
			T[now_t][fa[now]] = now;
			now = fa[now];
		}
	}
	
//	for (int i = 0; i <= 7; i++)
//	{
//		for (int j = 0; j <= n; j++)
//		{
//			printf("%d ", T[i][j]);
//		}
//		printf("\n");
//	}
	vector<pair<int, int> > ans;
//	printf("sw.size() = %d\n", sw.size());
	for (int i = 0; i < sw.size(); i++)
	{
	//	puts("!");
		int k = sw[i];
		int now = init[k];
		for (int j = 0; j < 10100; j++)
		{
			if (T[j][k] == 0)
				continue;
			if (T[j][k] != now)
			{
				ans.push_back(make_pair(j, k));
			//	printf(".");
				now = T[j][k];
			}
		}
	}
//	puts("!");
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
	{
		printf("%d %d\n", ans[i].second, ans[i].first);
	}
}
