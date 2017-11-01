#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define MOD 2147493647ll

struct mat
{
	ll d[9][9];
	mat()
	{
		for (int i = 0; i < 9; i ++) {
			for (int j = 0; j < 9; j ++) {
				d[i][j] = 0;
			}
		}
	}
	void put(int n, int a[])
	{
		for (int i = 0; i < 9; i ++) {
			d[n][i] = a[i];
		}
	}
	mat operator * (const mat &a) const
	{
		mat re;
		for (int i = 0; i < 9; i ++) {
		for (int j = 0; j < 9; j ++) {
			re.d[i][j] = 0;
		for (int k = 0; k < 9; k ++) {
			re.d[i][j] += d[i][k] * a.d[k][j] % MOD;
			re.d[i][j] %= MOD;
		}
		}
		}
		return re;
	}
};

int main()
{
	mat q, one;


	int b[9][9] = {
		{1, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 1}
	};
	for (int i = 0; i < 9; i ++) {
		one.put(i, b[i]);
	}

//	q.d[0][0] = 1; q.d[0][1] = 1; q.d[0][2] = 1; q.d[0][3] = 1; q.d[0][4] = 1; q.d[0][5] = 1; q.d[0][6] = 1; 
	int a[9][9] = {
		{1, 2, 0, 1, 4, 6, 4, 1},
		{1, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 4, 6, 4, 1},
		{0, 0, 0, 0, 1, 3, 3, 1},
		{0, 0, 0, 0, 0, 1, 2, 1},
		{0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1}
	};
	for (int i = 0; i < 9; i ++) {
		q.put(i, a[i]);
	}
	/*
	for (int i = 0; i < 9; i ++) {
		for (int j=  0; j < 9; j ++) {
			printf("%lld ", q.d[i][j]);
		}
		puts("");
	}
	*/
	int T;
	scanf("%d", &T);
	while (T --) {
		ll N, a1, a2;
		scanf("%lld%lld%lld", &N, &a1, &a2);
		if (N <= 2) {
			if (N == 1) printf("%lld\n", a1 % MOD);
			if (N == 2) printf("%lld\n", a2 % MOD);
			continue;
		}
		mat r = one, sq = q;
		N --;
		for (; N; N >>= 1) {
			if (N & 1) r = r * sq;
			sq = sq * sq;
		}
		ll a3 = (2ll * a1 + a2 + 81) % MOD;
		
		ll ans = 0;
		ll seq[9] = {a3, a2, a1, 81, 27, 9, 3, 1};
		for (int i = 0; i < 9; i ++) {
			ans += seq[i] * r.d[2][i];
			ans %= MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}