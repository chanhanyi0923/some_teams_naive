#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<ll, pii> pip;

#define fi first
#define se second

#define VSIZE 505
#define SIZE 50005

bool tag[SIZE];
bool on_mst[SIZE];
pip E[SIZE];

struct UF
{
	int f[VSIZE];
	inline void init(int N) { for (int i = 0; i < N + 3; i ++) f[i] = i; }
	int find(int x) { return f[x] == x ? x : (f[x] = find(f[x])); }
	inline void merge(int a, int b) { f[find(a)] = f[find(b)]; }
} U;

ll mst1(int N, int M)
{
	U.init(N);
	ll ans = 0;
	for (int i = 0; i < M; i ++) {
		int a = E[i].se.fi, b = E[i].se.se;
		if (U.find(a) != U.find(b)) {
			U.merge(a, b);
			ans += E[i].fi;
			on_mst[i] = true;
		}
	}
	return ans;
}

ll mst2(int N, int M)
{
	int cnt = 0;
	U.init(N);
	ll ans = 0;
	for (int i = 0; i < M; i ++) {
		if (tag[i]) continue;
		int a = E[i].se.fi, b = E[i].se.se;
		if (U.find(a) != U.find(b)) {
			U.merge(a, b);
			ans += E[i].fi;
			cnt ++;
		}
	}
	if (cnt < N - 1) ans = (1ll << 62);
	return ans;
}

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i ++) {
		ll a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		E[i] = pip(c, pii(a, b));
	}
	sort(E, E + M);
	ll mst_sum = mst1(N, M);

	ll ans = 0; int cnt = 0;
	for (int i = 0; i < M; i ++) {
		if (on_mst[i]) {
			tag[i] = true;
			//
			if (mst2(N, M) > mst_sum) {
				ans += E[i].fi;
				cnt ++;
			}
			//
			tag[i] = false;
		}
	}
	printf("%d %lld\n", cnt, ans);
	return 0;
}