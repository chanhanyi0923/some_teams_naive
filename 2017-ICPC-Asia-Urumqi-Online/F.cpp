#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define SIZE 10005

vector<int> G[SIZE];
vector<int> S;
int dfn[SIZE], low[SIZE], cpn[SIZE], cpn_sz[SIZE];
bool inS[SIZE];
int inDeg[SIZE], outDeg[SIZE];

int dfs(int v)
{
	static int o = 0;
	if (low[v] != -1) return low[v];
	dfn[v] = low[v] = o ++;
	S.push_back(v);
	inS[v] = true;
	for (int i = 0; i < G[v].size(); i ++) {
		int u = G[v][i];
		dfs(u);
		if (inS[u]) low[v] = min(low[v], low[u]);
	}
	if (low[v] == dfn[v]) {
		int u;
		do {
			u = S.back(); S.pop_back();
			cpn_sz[v] ++;
			cpn[u] = v;
			inS[u] = false;
		} while (u != v);
	}
	return low[v];
}

int main()
{
	int T, N, M;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d", &N, &M);
		S.clear();
		for (int i = 0; i < N + 3; i ++) {
			G[i].clear();
			low[i] = dfn[i] = cpn[i] = -1;
			cpn_sz[i] = 0; inS[i] = false;
			inDeg[i] = outDeg[i] = 0;
		}
		for (int i = 0; i < M; i ++) {
			int a, b;
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
		}
		for (int i = 1; i <= N; i ++) dfs(i);
		int num = 0, sz = 0;
		for (int i = 1; i <= N; i ++) {
			if (cpn[i] == i) {
				num ++;
				sz += cpn_sz[i];
			}
		}
		if (num == 1) {
			puts("0");
		} else {
			for (int i = 1; i <= N; i ++) {
				for (int j = 0; j < G[i].size(); j ++) {
					int a = cpn[i], b = cpn[G[i][j]];
					if (a == b) continue;
					outDeg[a] ++; inDeg[b] ++;
				}
			}
			int id = 0, od = 0;
			for (int i = 1; i <= N; i ++) {
				if (i == cpn[i]) {
					if (outDeg[i] == 0) od ++;
					if (inDeg[i] == 0) id ++;
				}
			}
			printf("%d\n", max(id, od));
		}
	}
	return 0;
}
