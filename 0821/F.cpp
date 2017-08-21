#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define mp(a, b) make_pair(a, b)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> ppi;

class BIT
{
public:
	int SIZE;
	static const int BIAS = 5;
	vector<ll> u;
	void clear(int N)
	{
		SIZE = N;
		u.resize(SIZE);
		for (int i = 0; i < SIZE; i ++) u[i] = 0;
	}
	void add(int x, ll v)
	{
		for (x += BIAS; x < SIZE; x += x & -x) u[x] += v;
	}
	ll sum(int x)
	{
		ll s = 0;
		for (x += BIAS; x; x -= x & -x) s += u[x];
		return s;
	}
};

class TreeDiv
{
public:
	static const int SIZE = 100005;
	int sz[SIZE], lv[SIZE], rt[SIZE], fa[SIZE];
	int cnt, seg[SIZE], idx[SIZE], low[SIZE], top[SIZE], len[SIZE];
	int init(int n, const vector<int> e[]) {
		memset(len, cnt = 0, sizeof(len));
		memset(lv, 0, sizeof(lv));
		for (int i = 0; i < n; i ++) if (!lv[i]) {
			segment(rt[i] = fa[i] = i, e);
			top[seg[i]] = fa[i] = SIZE - 1;
		}
		return cnt;
	}
private:
	void segment(int x, const vector<int> e[])
	{
		int y, t = -1;
		sz[x] = 1;
		rt[x] = rt[fa[x]];
		lv[x] = lv[fa[x]] + 1;
		for (size_t i = 0; i < e[x].size(); i ++) if (e[x][i] != fa[x]) {
			fa[y = e[x][i]] = x;
			segment(y, e);
			sz[x] += sz[y];
			if (t < 0 || sz[y] > sz[t]) t = y;
		}
		seg[x] = ~t ? seg[t] : cnt;
		idx[x] = ~t ? idx[t] + 1 : 0;
		if (t < 0) low[cnt ++] = x;
		len[seg[x]] ++;
		top[seg[x]] = fa[x];
	}
};

BIT B[100005];
vector<int> fat[100005];//father
int node_idx[100005];
TreeDiv TD;
ppi node[100005];

int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i ++) {
		int p, r, t;
		scanf("%d%d%d", &p, &r, &t);
		p --;
		if (p >= 0) fat[i].push_back(p);
		node[i] = ppi(pii(r, t), i);
	}
	int cnt = TD.init(N, fat);
	for (int i = 0; i < cnt; i ++) {
		int j, k = 0;
		for (j = TD.low[i]; j != TD.top[i]; j = TD.fa[j]) {
			node_idx[j] = k ++;
		}
		B[i].clear(k);
	}
	//
	
	sort(node, node + N);
	for (int i = 0; i < N; i ++) {
		int v = node[i].se;
		int chain = TD.seg[v];
		// printf("%d\n", chain);
		printf("%lld\n", B[chain].sum(node_idx[v]));
		B[chain].add(node_idx[v], node[i].fi.se);
		int j = chain;
		while (true) {

			int ff = TD.top[j];
			// printf("%d\n", ff);
			// printf("%d\n", ff);
			if (ff == TD.SIZE - 1) break;
			j = TD.seg[ff];
			B[j].add(0, node[i].fi.se);
		}
	}
	return 0;
}
