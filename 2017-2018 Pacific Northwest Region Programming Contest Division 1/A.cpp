#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
	string s;
	cin >> s;
	bool ans = true;
	for (int l = 0; l < s.length(); l++)
	{
		for (int r = l; r < s.length(); r++)
		{
			bool is_pali = true;
			for (int i = l, j = r; i < j; i++, j--)
			{
				if (s[i] != s[j])
				{
					is_pali = false;
					break;
				}
			}
			
			if (is_pali && (r - l + 1) % 2 == 0)
			{
				ans = false;
				//printf("l = %d, r = %d\n", l, r);
			}
		}
	}
	
	if (ans)
	{
		cout << "Odd." << endl;
	}
	else
	{
		cout << "Or not." << endl;
	}
	return 0;
}