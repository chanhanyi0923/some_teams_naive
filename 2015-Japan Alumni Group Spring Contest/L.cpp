#include <bits/stdc++.h>

using namespace std;

int sg[22][22][22][22] = {0};
int matrix[22][22];
set<int> l;
int n, m;
void work(int x1, int y1, int x2, int y2)
{
	l.clear();	

	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			if (matrix[i][j] == 1)
				continue;
			int now_sg = 0;
			now_sg ^= sg[x1][y1][i - 1][j - 1];
			now_sg ^= sg[x1][j + 1][i - 1][y2];
			now_sg ^= sg[i + 1][y1][x2][j - 1];
			now_sg ^= sg[i + 1][j + 1][x2][y2];
			
			l.insert(now_sg);
		}
	}
	
	
	for (int i = 0; ; i++)
	{
		if (l.count(i) == 0)
		{
			sg[x1][y1][x2][y2] = i;
			return;
		}
	}
}
		
int main()
{
	cin >> n >> m;
	getchar();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			char c = getchar();
			if (c == '.')
			{
				matrix[i][j] = 0;
			}
			else
			{
				matrix[i][j] = 1;
			}
		}
		getchar();
	}
	
	for (int h = 0; h < n; h++)
	{
		for (int w = 0; w < m; w++)
		{
			for (int x = 1; x + h <= n; x++)
			{
				for (int y = 1; y + w <= m; y++)
				{
					work(x, y, x + h, y + w);
				}
			}
		}
	}
	
	if (sg[1][1][n][m] == 0)
	{
		puts("Second");
	}
	else
	{
		puts("First");
	}
	
}
