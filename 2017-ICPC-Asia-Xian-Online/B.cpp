#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

#define MOD 1000000007

struct mat
{
	ll d[2][2];
	mat()
	{
		d[0][0] = d[0][1] = d[1][0] = d[1][1] = 0;
	}
	mat operator * (const mat &a) const
	{
		mat r;
		for (int i = 0; i < 2; i ++) {
			for (int j = 0; j < 2; j ++) {
				for (int k = 0; k < 2; k ++) {
					r.d[i][j] += d[i][k] * a.d[k][j];
					r.d[i][j] %= MOD;
				}
			}
		}
		return r;
	}
};

ll qp(ll n, int k)
{
	ll r = 1, sq = n;
	for (; k > 0; k >>= 1) {
		if (k & 1) { r *= sq; r %= MOD; }
		sq *= sq; sq %= MOD;
	}
	return r;
}

mat qp_mat(mat n, int k)
{
	mat r, sq = n;
	r.d[0][0] = r.d[1][1] = 1;
	for (; k > 0; k >>= 1) {
		if (k & 1) r = r * sq;
		sq = sq * sq;
	}
	return r;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T --) {
		ll p, q, k;
		scanf("%lld%lld%lld", &p, &q, &k);
		ll x = q * qp(p, MOD - 2) % MOD;// q / p
		ll y = (p - q) * qp(p, MOD - 2) % MOD;// (p - q) / p
		mat r;
		r.d[0][0] = r.d[1][1] = y;
		r.d[0][1] = r.d[1][0] = x;
		r = qp_mat(r, k);
		ll ans = r.d[0][0];
		printf("%lld\n", ans);
	}
	return 0;
}
