#include <bits/stdc++.h>

using namespace std;

priority_queue< int, vector<int>, greater<int> > Q;

#define SIZE 1005

int arr[SIZE];
int deg[SIZE];
int cnt[SIZE][SIZE];
vector<int> G[SIZE];
vector<int> ans;

int main()
{
	int N, K;
	while (EOF != scanf("%d%d", &N, &K) && (N > 0 || K > 0)) {
		for (int i = 0; i <= N; i ++) {
			deg[i] = 0;
			G[i].clear();
			for (int j = 0; j <= N; j ++) {
				cnt[i][j] = 0;
			}
		}

		for (int i = 0; i < K; i ++) {
			for (int j = 0; j < N; j ++) {
				scanf("%d", arr + j);
				//printf("%d ", arr[j]);
				for (int k = 0; k < j; k ++) {
					cnt[arr[k]][arr[j]] ++;
				}
			}
			//puts("");
		}

		for (int i = 1; i <= N; i ++) {
			for (int j = 1; j <= N; j ++) {
				if (cnt[i][j] > cnt[j][i]) {
					G[i].push_back(j);
					deg[j] ++;
				} else if (cnt[j][i] > cnt[i][j]) {
					G[j].push_back(i);
					deg[i] ++;
				}
			}
		}
		while (!Q.empty()) Q.pop();
		for (int i = 1; i <= N; i ++) {
			if (deg[i] == 0) {
				Q.push(i);
			}
		}
		if (Q.empty()) {
			puts("No solution");
			continue;
		}
		ans.clear();
		while (!Q.empty()) {
			int v = Q.top(); Q.pop();
			ans.push_back(v);
			for (int i = 0; i < G[v].size(); i ++) {
				int u = G[v][i];
				if (-- deg[u] == 0) {
					Q.push(u);
				}
			}
		}
		bool fail = false;
		for (int i = 0; i <= N; i ++) {
			if (deg[i] != 0) {
				fail = true;
				break;
			}
		}
		if (fail) {
			puts("No solution");
		} else {
			printf("%d", ans[0]);
			for (int i = 1; i < ans.size(); i ++) {
				printf(" %d", ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
