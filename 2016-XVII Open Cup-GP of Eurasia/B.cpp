#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define SIZE 100005

vector<int> G[SIZE];
vector<int> G2[SIZE];
vector<int> S;
int dfn[SIZE], low[SIZE], cpn[SIZE], sz[SIZE];
bool inS[SIZE];

int dfs(int v, int &o)
{
	if (low[v] != -1) return low[v];
	dfn[v] = low[v] = o ++;
	S.push_back(v);
	inS[v] = true;
	for (int i = 0; i < G[v].size(); i ++) {
		int u = G[v][i];
		dfs(u, o);
		if (inS[u]) low[v] = min(low[v], low[u]);
	}
	if (low[v] == dfn[v]) {
		int u;
		do {
			sz[v] ++;
			u = S.back(); S.pop_back();
			cpn[u] = v;
			inS[u] = false;
		} while (u != v);
	}
	return low[v];
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int N, M;
	scanf("%d%d", &N, &M);
	if (N == 1) {
		puts("-1");
		return 0;
	}
	for (int i = 0; i < M; i ++) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
	}
	for (int i = 0; i < SIZE; i ++) {
		dfn[i] = low[i] = -1;
	}
	for (int i = 1, o = 0; i <= N; i ++) {
		dfs(i, o);
	}
	for (int i = 1; i <= N; i ++) {
		if (i == cpn[i] && sz[i] > 1) {
			puts("0");
			return 0;
		}
	}
	if (M == 0) {
		puts("2");
	} else {
		puts("1");
	}
	return 0;
}
