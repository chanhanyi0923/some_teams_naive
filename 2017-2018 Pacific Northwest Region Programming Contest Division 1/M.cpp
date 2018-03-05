#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define SIZE 4005

vector<int> G[SIZE];
bool vis[SIZE];
bool to[SIZE][SIZE];
bool in[SIZE];
bool out[SIZE];

inline int toPos(int x) { return x + 2002; }

void dfs(int v, int p)
{
	if (vis[v]) return;
	vis[v] = true;
	to[p][v] = true;
	//printf("%d %d\n", p -2002, v-2002);
	if (v != p && (p -2002) * (v-2002) < 0) {
		out[p] = true;
		in[v] = true;
	}
	for (int i = 0; i < G[v].size(); i ++) {
		int u = G[v][i];
		dfs(u, p);
	}
}

int main()
{
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i ++) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[toPos(-a)].push_back(toPos(b));
		G[toPos(-b)].push_back(toPos(a));
	}
	/*
	for (int i = 0; i < SIZE; i ++) {
		for (int j = 0; j < G[i].size(); j ++) {
			printf("%d -> %d\n", i - 2002, G[i][j] - 2002);
		}
	}
	*/
	for (int i = 1; i <= N; i ++) {
		for (int j = 0; j < SIZE; j ++) vis[j] = false;
		dfs(toPos(i), toPos(i));

		for (int j = 0; j < SIZE; j ++) vis[j] = false;
		dfs(toPos(-i), toPos(-i));
	}

	int ans = -1;
	for (int i = 1; i <= N; i ++) {
		if (to[toPos(i)][toPos(-i)] && to[toPos(-i)][toPos(i)]) {
			ans = 0;
			break;
		}
	}
	if (ans != -1) goto END;
	for (int i = 1; i <= N; i ++) {
		if (to[toPos(i)][toPos(-i)]) {
			ans = 1;
			break;
		}
	}
	if (ans != -1) goto END;
	for (int i = 1; i <= N; i ++) {
		if (out[toPos(i)] && in[toPos(-i)]) {
			ans = 2;
			break;
		}
	}
	if (ans != -1) goto END;
	END:
	printf("%d\n", ans);
	return 0;
}