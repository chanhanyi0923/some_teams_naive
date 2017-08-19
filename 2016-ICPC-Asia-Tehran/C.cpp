#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> ppp;

map<int, int> M;
map<int, int> F, S;
vector<ppp> ans;

int main()
{
	int N;
	while (EOF != scanf("%d", &N) && N > 0) {
		M.clear(); F.clear(); S.clear();
		ans.clear();
		for (int i = 0; i < N; i ++) {
			int d; scanf("%d", &d);
			for (int j = 0; j < d; j ++) {
				int x; scanf("%d", &x);
				M[x] += 3 - j;
				if (j == 0) {
					F[x] ++;
				}
				if (j == 1) {
					S[x] ++;
				}
			}
		}
		for (map<int, int>::iterator it = M.begin(); it != M.end(); it ++) {
			int idx = it->first;
			int point = it->second;
			// printf("! %d %d\n", idx, point);
			ans.push_back(ppp(pii(point, F[idx]), pii(S[idx], idx)));
		}
		sort(ans.begin(), ans.end());
		reverse(ans.begin(), ans.end());
		int sz = 0;
		for (int i = 1; i < ans.size(); i ++) {
			ppp a = ans[i], b = ans[i - 1];
			a.second.second = b.second.second = 0;
			if (a != b) {
				sz = i;
				break;
			}
		}
		vector<int> ans2;
		for (int i = 0; i < sz; i ++) {
			ans2.push_back(ans[i].second.second);
		}
		sort(ans2.begin(), ans2.end());
		printf("%d", ans2[0]);
		for (int i = 1; i < ans2.size(); i ++) {
			printf(" %d", ans2[i]);
		}
		puts("");
	}
	return 0;
}
