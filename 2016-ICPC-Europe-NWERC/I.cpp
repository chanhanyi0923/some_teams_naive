#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define SIZE 100005
#define INF (1 << 29)

vector<int> G1[SIZE], G2[SIZE];
queue<pii> Q1, Q2;
int D1[SIZE], D2[SIZE], D3[SIZE];

int main()
{
	for (int i = 0; i < SIZE; i ++) {
		D1[i] = D2[i] = D3[i] =  INF;
	}
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 0; i < M; i ++) {
		int x; scanf("%d", &x);
		Q1.push(pii(0, x));
	}
	for (int i = 0; i < K; i ++) {
		int x; scanf("%d", &x);
		Q2.push(pii(0, x));
	}
	for (int i = 1; i <= N; i ++) {
		int a; scanf("%d", &a);
		for (int j = 0; j < a; j ++) {
			int x; scanf("%d", &x);
			G1[i].push_back(x);
			G2[x].push_back(i);
		}
	}
	
	while (!Q1.empty()) {
		int v = Q1.front().second;
		int s = Q1.front().first;
		Q1.pop();
		if (D1[v] != INF) continue;
		D1[v] = s;
		for (int i = 0; i < G2[v].size(); i ++) {
			int u = G2[v][i];
			if (D1[u] == INF) {
				Q1.push(pii(s + 1, u));
			}
		}
	}
	while (!Q2.empty()) {
		int v = Q2.front().second;
		int s = Q2.front().first;
		Q2.pop();
		if (D2[v] != INF) continue;
		D2[v] = s;
		for (int i = 0; i < G2[v].size(); i ++) {
			int u = G2[v][i];
			if (D2[u] == INF) {
				Q2.push(pii(s + 1, u));
			}
		}
	}

	Q1.push(pii(0, 1));
	while (!Q1.empty()) {
		int v = Q1.front().second;
		int s = Q1.front().first;
		Q1.pop();
		if (D3[v] != INF) continue;
		D3[v] = s;
		for (int i = 0; i < G1[v].size(); i ++) {
			int u = G1[v][i];
			if (D3[u] == INF) {
				Q1.push(pii(s + 1, u));
			}
		}
	}
	ll ans = 1ll << 60;
	for (int i = 1; i <= N; i ++) {
		ans = min(ans, 1ll * D1[i] + D2[i] + D3[i]);
	}
	if (ans >= INF) {
		puts("impossible");
	} else {
		printf("%lld\n", ans);
	}
	return 0;
}
