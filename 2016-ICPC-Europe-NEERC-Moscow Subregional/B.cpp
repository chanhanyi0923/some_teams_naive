#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() 
{
	ll l, r, w;
	cin >> l >> r >> w;
	ll ep = __gcd(r, w);
	if (r + w - l > ep)
	{
		puts("DEADLOCK");
	}
	else
	{
		puts("OK");
	}
}
