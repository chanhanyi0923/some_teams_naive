#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int SIZE = 1000000;
int D[SIZE];
int cons = 1;
int co = 0;

void add(int t)
{
	while (D[t] == 1)
	{
		D[t] = 0;
		co--;
		t--;
	}
	D[t] = 1;
	co++;
}

void update()
{
	while (D[cons] == 1)
	{
		cons++;
	}
}

int main()
{
	int n;
	cin >> n;
	bool flag = true;
	for (int i = 0; i < n; i++)
	{

		if (!flag)
		{
			int t;
			cin >> t;
			puts("No");
			continue;
		}
		
		int t;
		cin >> t;
		if (t >= SIZE)
		{
			puts("Yes");
			continue;
		}
		
		if (cons > t)
		{
			if (t == cons - 1 && cons - 1 == co)
			{
				puts("Yes");
				flag = false;
				continue;
			}
			else
			{
				puts("No");
				continue;
			}
		}
		
		puts("Yes");
		add(t);
		update();
		
	}

	return 0;
}
