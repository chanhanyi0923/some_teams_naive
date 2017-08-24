#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int star[26] = {0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2};

int main()
{
	char c;
	int nowRank = 25;
	int nowStar = 0;
	int combo = 0;
	while ((c = getchar()) && (c == 'W' || c == 'L'))
	{
		if (c == 'W')
		{
			nowStar++;
			combo++;
			if (combo >= 3 && nowRank >= 6)
			{
				nowStar++;
			}
		}
		if (c == 'L')
		{
			if (nowRank <= 20)
			{
				nowStar--;
			}
			combo = 0;
		}
		
		if (nowStar > star[nowRank])
		{
			nowStar -= star[nowRank];
			nowRank--;
			if (nowRank == 0)
			{
				cout << "Legend" << endl;
				return 0;
			}
		}
		
		if (nowStar < 0)
		{
			if (nowRank >= 20)
			{
				nowStar = 0;
			}
			else
			{
				nowRank++;
				nowStar += star[nowRank];
			}
		}
		
		//printf("State = %c, nowRank = %d, nowStar = %d, combo = %d\n", c, nowRank, nowStar, combo);
	}
	
	cout << nowRank << endl;
	return 0;
}
		
	
