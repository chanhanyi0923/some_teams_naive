#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
struct point
{
	int x, y;
	point():x(0),y(0){}
};
	
ll c[2][2][2]; // c[ x % 2][y % 2][area % 2]
vector<point> pl;

/*
void print()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				printf("c[%d][%d][%d] = %lld\n", i, j, k, c[i][j][k]);
	printf("\n");
}
*/

int m2det(int x1, int y1, int x2, int y2)
{
	return (x1 * y2 - x2 * y1) & 1;
}

int m2area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int _x1 = x2 ^ x1;
	int _y1 = y2 ^ y1;
	int _x2 = x3 ^ x2;
	int _y2 = y3 ^ y2;
	int ans = m2det(_x1, _y1, _x2, _y2);
	return ans;
}

void init()
{
	int area = 0;
	int x0 = pl[0].x;
	int y0 = pl[0].y;
	//printf("n = %d\n", n);
	for (int i = 1; i < n; i++)
	{
		int x1 = pl[i - 1].x;
		int y1 = pl[i - 1].y;
		int x2 = pl[i].x;
		int y2 = pl[i].y;
		area ^= m2area(x0, y0, x1, y1, x2, y2);
	//	printf("c[%d][%d][%d]++\n", x2, y2, area);
		c[x2][y2][area]++;
	}
	
	if (area == 1)
	{
		printf("0\n");
		exit(0);
	}
}


ll stat()
{
	ll ans = 0;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			ans += c[i][j][0];
	return ans;
}

void update(int x)
{
	ll d[2][2][2];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				d[i][j][k] = 0;
	int x1 = pl[x].x;
	int x2 = pl[x - 1].x;
	int y1 = pl[x].y;
	int y2 = pl[x - 1].y;
	c[x1][y1][0]--;
	c[x2][y2][0]++;	
	for (int x3 = 0; x3 < 2; x3++)
	{
		for (int y3 = 0; y3 < 2; y3++)
		{
			int area = m2area(x1, y1, x2, y2, x3, y3);
			
			d[x3][y3][0 ^ area] += c[x3][y3][0];
			d[x3][y3][1 ^ area] += c[x3][y3][1];
		}
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				c[i][j][k] = d[i][j][k];
			}
}

int main()
{
	freopen("integral.in", "r", stdin);
	freopen("integral.out", "w", stdout);
	cin >> n;
	pl.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> pl[i].x >> pl[i].y;
		pl[i].x &= 1;
		pl[i].y &= 1;
	}
	
	init();
	//print();
	
	ll ans = 0;
	for (int i = 1; i < n; i++)
	{
		ans += stat();
		update(i);
		//print();
	}
	ans += stat();
	
//	printf("ans = %lld\n", ans);
	cout << ans / 2 - n << endl;
	return 0;
}
