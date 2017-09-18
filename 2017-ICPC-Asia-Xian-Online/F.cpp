#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#define MOD 998244353

ll qp(ll n, int k)
{
	ll r = 1, sq = n;
	for (; k > 0; k >>= 1) {
		if (k & 1) { r *= sq; r %= MOD; }
		sq *= sq; sq %= MOD;
	}
	return r;
}

int main()
{
	int N, M;
	while (EOF != scanf("%d%d", &N, &M)) {
		if ((N + M) & 1) { puts("0"); continue; }
		if (N < M) { puts("0"); continue; }
		int x = (N + M) / 2 - 1;
		int y = (N - M) / 2;
		ll ans = 1;
		if (y & 1) ans = MOD - 1;
		for (int i = y + 1; i <= x; i ++) {
			ans *= i; ans %= MOD;
		}
		for (int i = 1; i <= M; i ++) {
			ans *= qp(i, MOD - 2); ans %= MOD;
		}
		ans *= qp(2, M); ans %= MOD;
		ans *= N; ans %= MOD;
		ans *= qp(2, MOD - 2); ans %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
