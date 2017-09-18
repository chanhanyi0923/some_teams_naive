#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define SIZE 10005

vector<pii> G[SIZE];
ll dp[SIZE]; int deg[SIZE];
queue<int> Q;

int main()
{
	int T, N, M;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N + 3; i ++) {
			dp[i] = deg[i] = 0;
			G[i].clear();
		}
		for (int i = 0; i < M; i ++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			G[a].push_back(pii(c, b));
			deg[b] ++;
		}
		while (!Q.empty()) Q.pop();
		for (int i = 1; i <= N; i ++) {
			if (deg[i] == 0) {
				Q.push(i);
			}
		}
		while (!Q.empty()) {
			int v = Q.front(); Q.pop();
			for (int i = 0; i < G[v].size(); i ++) {
				int u = G[v][i].second;
				ll w = G[v][i].first;
				dp[u] = max(dp[u], dp[v] + w);
				if (-- deg[u] == 0) {
					Q.push(u);
				}
			}
		}
		ll ans = 0;
		for (int i = 1; i <= N; i ++) {
			ans = max(ans, dp[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
