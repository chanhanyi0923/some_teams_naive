#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct mat
{
	int d[2][2];
	int mod;
	mat operator * (const mat &a) const
	{
		mat b;
		b.mod = this->mod;
		for (int i = 0; i < 2; i ++) {
			for (int j = 0; j < 2; j ++) {
				b.d[i][j] = 0;
				for (int k = 0; k < 2; k ++) {
					b.d[i][j] += (1ll * d[i][k] * a.d[k][j]) % this->mod;
					b.d[i][j] %= this->mod;
				}
			}
		}
		return b;
	}
};

int f(int n, int mod)
{
	mat r, sq;
	r.mod = sq.mod = mod;
	r.d[0][0] = 1; r.d[0][1] = 0;
	r.d[1][0] = 0; r.d[1][1] = 1;

	sq.d[0][0] = 0; sq.d[0][1] = 1;
	sq.d[1][0] = 1; sq.d[1][1] = 1;

	for (; n > 0; n >>= 1) {
		if (n & 1) r = r * sq;
		sq = sq * sq;
	}
	return r.d[0][1];
}

int main()
{
	//26880696
	int T, N;
	scanf("%d", &T);
	while (T --) {
		scanf("%d", &N);
		int k = f(N, 26880696);
		int ans = f(k, 20160519);
		printf("%d\n", ans);
	}
	return 0;
}
