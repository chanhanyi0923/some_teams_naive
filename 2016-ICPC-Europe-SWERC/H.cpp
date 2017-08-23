#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

map<string, ll> dp;
map<ll, int> ans;
vector<int> V, tmp;
char buf[100];

ll cal(string S)
{
	if (S.size() == 1) return 1;
	map<string, ll>::iterator it = dp.find(S);
	if (it != dp.end()) return it->second;
	ll result = 0;
	for (int i = 0; i < S.size(); i ++) {
		if (S[i] == '0') continue;
		tmp.clear();
		for (int j = 0; j < S.size(); j ++) {
			tmp.push_back(S[j] - (i == j));
			if (tmp.back() == '0') tmp.pop_back();
		}
		sort(tmp.begin(), tmp.end(), greater<int>());
		for (int j = 0; j < tmp.size(); j ++) {
			buf[j] = tmp[j];
		}
		buf[tmp.size()] = 0;
		result += cal(string(buf));
	}
	return dp[S] = result;
}

void solve(int D, int H, int M)
{
	if (V.size() >= D && H > 0) return;
	if (H == 0) {
		for (int i = 0; i < V.size(); i ++) {
			buf[i] = '0' + V[i];
		}
		buf[V.size()] = 0;
		ans[cal(string(buf))] = 1;
	} else {
		for (int i = min(H, M); i >= 1; i --) {
			V.push_back(i);
			solve(D, H - i, i);
			V.pop_back();
		}
	}
}

int main()
{
	int D, H;
	scanf("%d%d", &D, &H);
	solve(D, H - 1, H - 1);
	for (map<ll, int>::iterator it = ans.begin(); it != ans.end(); it ++) {
		printf("%lld\n", it->first);
	}
	return 0;
}