#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int jump[100010][31];
int l[100010];
int nxt[100010][4];
string s;
int ask(int L, int R)
{
	int ret = 0;
	int w = 30;
	int now = nxt[L][0];
	
	while (now <= R && w >= 0)
	{
		//printf("now = %d\n", now);
		if (jump[now][w] <= R)
		{
			now = jump[now][w];
			ret += 1 << w;
		}
		w--;
	}
	
	//printf("ret = %d\n", ret);
	
	ret++;
	return ret / 4;
}
	
	
int main()
{
	cin >> s;
	int n = s.length();
	for (int i = 1; i <= n; i++)
	{
		switch (s[i - 1])
		{
			case 'e':
				l[i] = 0;
				break;
			case 'a':
				l[i] = 1;
				break;
			case 's':
				l[i] = 2;
				break;
			case 'y':
				l[i] = 3;
				break;
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		nxt[n + 1][i] = n + 1;
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (l[i] == j)
			{
				nxt[i][j] = i;
			}
			else
			{
				nxt[i][j] = nxt[i + 1][j];
			}
		}
	}
	
	
	for (int i = 1; i <= n + 1; i++)
	{
		jump[i][0] = nxt[i][(l[i] + 1) % 4];
	}
	
	for (int p = 1; p <= 30; p++)
	{
		for (int i = 1; i <= n + 1; i++)
		{
			jump[i][p] = jump[jump[i][p - 1]][p - 1];
		}
	}
	
	
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int L, R;
		scanf("%d%d", &L, &R);
		printf("%d\n", ask(L, R));
	}
}
	
