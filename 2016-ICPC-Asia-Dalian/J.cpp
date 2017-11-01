#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	int n;
	cin >> n;
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> k;
		while (k != 0)
		{
			if (k % 256 == 97)
			{
				cnt++;
			}
			k /= 256;
		}
	}
	cout << cnt << endl;
}