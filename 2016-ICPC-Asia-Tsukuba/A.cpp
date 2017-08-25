#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct num
{
	int x;
	int rank;
};
vector<num> number;

bool cmp(const num& a, const num& b)
{
	return a.rank < b.rank;
}

const int INF = 1000000;
int main()
{
	int n, m;
	cin >> n >> m;
	number.resize(n + 1);
	int now = INF;
	for (int i = 1; i <= n; i++)
	{
		number[i].x = i;
		number[i].rank = INF + i;
	}
	
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		number[t].rank = now;
		now--;
	}
	
	sort(number.begin() + 1, number.end(), cmp);
	for (int i = 1; i <= n; i++)
	{
		printf("%d\n", number[i].x);
	}
	return 0;
}
		

