#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int a, b;
		cin >> a >> b;
		if (a < b)
		swap(a, b);
		int ret = a + a + b;
		cout << ret << endl;
	}
}