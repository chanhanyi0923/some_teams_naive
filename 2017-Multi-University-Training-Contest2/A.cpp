#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
string s;
string t;
int n, x, y;
int main()
{
	int T;
	cin >> T;
	while (T--)
	{ 
		cin >> n >> x >> y;
		getchar();	
		getline(cin, s);
		getline(cin, t);
		if (x < y)
		{
			swap(x, y);
			swap(s, t);
		}
		
	//	cout << s << endl;
	//	cout << t << endl;
	
		int len = s.length();
		if (x > len || y > len)
		{
			puts("Lying");
			continue;
		}
		
		int same = 0;
		int diff = 0;
		for (int i = 0; i < len; i++)
		{
			if (s[i] == t[i])
			{
				same++;
			}
			else
			{
				diff++;
			}
		}	
		
		int now_same = min(x, same);
		int now_diff = x - now_same;
		
		int maxac = -1;
		int minac = 10000000;
	//	printf("x = %d, y = %d\n", x, y);
	//	printf("now_same = %d, now_diff = %d\n", now_same, now_diff);

		for (; now_same >= 0 && now_diff <= diff; now_same--, now_diff++)
		{
			int sc = now_same;
			int sw = same - now_same;
			int dc = now_diff;
			int dw = diff - now_diff;
			
			int now_max = sc + dw;
			int now_min = sc;
	//		printf("sc = %d, sw = %d, dc = %d, dw = %d, now_max = %d, now_min = %d\n", sc, sw, dc, dw, now_max, now_min);
			maxac = max(maxac, now_max);
			minac = min(minac, now_min);
		}
		
		if (minac <= y && y <= maxac)
		{
			puts("Not lying");
		}
		else
		{
			puts("Lying");
		}
	}
}
