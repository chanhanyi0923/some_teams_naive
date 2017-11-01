#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define SIZE 105

vector<int> G[SIZE];
__int128 connect[SIZE];
//[SIZE];
__int128 vis;
__int128 V;
//bool vis[SIZE];
int S;
//vector<int> V;

bool check(int v)
{
	if (V == (connect[v] & V)) {
		return true;
	} else {
		return false;
	}
/*
	for (size_t i = 0; i < V.size(); i ++) {
		int u = V[i];
		if (!connect[v][u]) return false;
	}
	return true;
*/
}

/*
void print()
{
	vector<int> K;
	for (size_t i = 0; i < V.size(); i ++) {
		K.push_back(V[i]);
	}
	sort(K.begin(), K.end());
	for (size_t i = 0; i < V.size(); i ++) {
		printf("%d ", K[i]);
	}
	puts("");
}
*/

int dfs(int v, int num)
{
	//printf("vertex %d %d\n", v, num);
	if (num == S) {
		//printf("v = %d\n", v);
		//print();
		return 1;
	}
	if (!check(v)) {
		//puts("!");
		return 0;
	}
	//printf("S = %d, num = %d\n", S, num);
	if (num + 1 == S) {
		//V.push_back(v);
		// printf("v = %d\n", v);
		//print();
		//V.pop_back();
		return 1;
	}

	//V.push_back(v);
	//vis[v] = true;
	vis |= (__int128)(1) << v;
	V |= (__int128)(1) << v;

	int ans = 0;
	for (size_t i = 0; i < G[v].size(); i ++) {
		int u = G[v][i];
		if (u < v || (vis & ((__int128)(1) << u))) continue;
		if (G[u].size() < S - 1) continue;
		ans += dfs(u, num + 1);
	}

	//V.pop_back();
	//if (!(vis & ((__int128)(1) << v))) { puts("!"); }
	vis -= (__int128)(1) << v;
	V -= (__int128)(1) << v;
	//vis[v] = false;
	return ans;
}

int main()
{
	int T, N, M;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d%d", &N, &M, &S);

		vis = 0;
		for (int i = 0; i < N + 3; i ++) {
			/*
			for (int j = 0; j < N + 3; j ++) {
				connect[i][j] = false;
			}
			*/
			connect[i] = 0;
			G[i].clear();
			//vis[i] = false;
		}
		for (int i = 0; i < M; i ++) {
			int a, b;
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
			//
			connect[a] |= (__int128)(1) << b;
			connect[b] |= (__int128)(1) << a;
			//connect[a][b] = connect[b][a] = true;
		}
		int cnt = 0;
		for (int i = 1; i <= N; i ++) {
			//printf("i = %d\n", i);
			V = 0;
			cnt += dfs(i, 0);
			vis |= (__int128)(1) << i;
			//vis[i] = true;
			//puts("---");
		}
		printf("%d\n", cnt);
	}
	return 0;
}