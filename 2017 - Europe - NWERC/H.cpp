#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll read(int N)
{
	char str[100];
	scanf("%s", str);
	ll x = 0;
	for (int i = N - 1; i > -1; i --) {
		ll bit = (str[N - 1 - i] - '0');
		x = x | (bit << i);
	}
	return x;
}

ll nth(ll x)
{	
	ll x2 = (x >> 1ll);
	while (x2 > 0){
		x = x ^ x2;
		x2 = x2 >> 1ll;
	}
	return x;
}

int main()
{
	int N;
	scanf("%d", &N);
	ll a = nth(read(N));
	ll b = nth(read(N));
	
	printf("%lld\n", max(0ll, abs(b - a) - 1));
	return 0;
}
