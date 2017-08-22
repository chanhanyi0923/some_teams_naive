#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define mp(a, b) make_pair(a, b)

typedef long long ll;
typedef pair<int, int> pii;

#define SIZE 100005

pii a;
pii p[SIZE];
pii online[SIZE];
bool comp (const pii& a, const pii& b)
{
	if (a.fi == 0) return a.se < 0;
	if (b.fi == 0) return b.se > 0;
	return (1.0 * a.se / a.fi < 1.0 * b.se / b.fi);
}

bool par(const pii& a, const pii& b)
{
	return b.fi * a.se == a.fi * b.se;
}

int sgn(int x)
{
	if (x > 0)
	{
		return 1;
	}
	if (x == 0)
	{
		return 0;
	}
	return -1;
}

int sign[SIZE];

int main()
{
	int n;
	scanf("%d", &n);
	
	int maxRank = n + 1;
	int minRank = 0;
	
	int bigger = 0;
	int smaller = 0;
	int equal_pos = 0;
	int equal_neg = 0;
	int equal_zero = 0;
	
	int numMax = 0;
	int numMin = 0;
	scanf("%d%d", &a.fi, &a.se);
	
	int N = 0;
	for (int i = 1; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		x -= a.fi;
		y -= a.se;
		
		if (x == 0 && y == 0)
		{
			equal_zero++;
			continue;
		}
		
		if (x > 0 || (x == 0 && y < 0))
		{
			bigger++;
		}
		
		if (x < 0 || (x == 0 && y > 0))
		{
			smaller++;
		}
		
		if (x > 0 && y > 0 || x < 0 && y < 0)
		{
			continue;
		}

		p[N++] = pii(x, y);
		
	}
	
	maxRank = 100000;
	minRank = -1;
	//printf("N = %d\n", N);
	sort(p, p + N, comp);
	//printf("b = %d, s = %d, p = %d, n = %d\n", bigger, smaller, equal_pos, equal_neg);
		
	//for (int i = 0; i < N; i++)
	//{
	//	printf("#%d, %d %d\n", i, p[i].fi, p[i].se);
	//}
	
	int i = 0;
	int sz = 0;
	
	while (true)
	{	
		int j = i;
		while (j < N && par(p[i], p[j]))
		{
			//puts("?");
			online[sz++] = p[j];
			if (p[j].fi < 0 || (p[j].fi == 0 && p[j].se > 0))
			{
				equal_pos++;
				smaller--;
			}
			else if (p[j].fi > 0 || (p[j].fi == 0 && p[j].se < 0))
			{
				equal_neg++;
				bigger--;
			}
			j++;
		}
		
		//printf("b = %d, s = %d, p = %d, n = %d\n", bigger, smaller, equal_pos, equal_neg);
		maxRank = min(maxRank, bigger + 1);
		minRank = max(minRank, bigger + equal_pos + equal_neg + equal_zero + 1);
		//printf("maxRank = %d, minRank = %d\n", maxRank, minRank);
		if (j == i) break;
		i = j;
		//printf("size = %d\n", online.size());
	
		for (int j = 0; j < sz; j++)
		{
			//printf("online: %d %d\n", online[j].fi, online[j].se);
			if (online[j].fi < 0 || (online[j].fi == 0 && online[j].se > 0))
			{
				//puts("!");
				equal_pos--;
				bigger++;
			}
			else if (online[j].fi > 0 || (online[j].fi == 0 && online[j].se < 0))
			{
				//puts("!");
				equal_neg--;
				smaller++;
			}
		}
		sz = 0;
		if (i >= N)
		{
			break;
		}
	}

	cout << maxRank << " " << minRank << endl;
		
}
