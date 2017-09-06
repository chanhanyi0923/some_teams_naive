#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

#define SIZE 2005

vector<pii> G[SIZE];
vector<ll> total;
int s[SIZE];

struct DivTree
{
	int root;
	int chain[SIZE];
	int dis[SIZE];
	void init(int r)
	{
		root = r;
		for (int i = 0; i < SIZE; i ++) {
			chain[i] = i;
			dis[i] = 0;
		}
	}
	pii dfs(int v, int p, int pw)
	{
		pii ans = pii(0, v);
		for (size_t i = 0; i < G[v].size(); i ++) {
			int u = G[v][i].se;
			int w = G[v][i].fi;
			if (u == p) continue;
			pii result = dfs(u, v, w);
			result.fi += w;
			ans = max(ans, result);
		}
		chain[v] = chain[ans.se];
		dis[chain[v]] = max(dis[chain[v]], ans.fi + pw);
		return ans;
	}
};

DivTree D[SIZE];

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 1; i < N; i ++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		G[a].push_back(pii(c, b));
		G[b].push_back(pii(c, a));
	}
	for (int i = 1; i <= N; i ++) {
		scanf("%d", s + i);
	}
	for (int i = 1; i <= N; i ++) {
		D[i].init(i);
		D[i].dfs(i, i, 0);
		for (int j = 1; j <= N; j ++) {
			if (D[i].dis[j] > 0) {
				total.push_back(1ll * s[i] * D[i].dis[j]);
			}
		}
	}
	sort(total.begin(), total.end());
	reverse(total.begin(), total.end());
	ll ans = 0;
	for (size_t i = 0; i < total.size() && i < M; i ++) {
		ans += total[i];
	}
	printf("%lld\n", ans);
	return 0;
}
