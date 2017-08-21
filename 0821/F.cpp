#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, pii> ppp;

#define SIZE 100005

vector<int> G[SIZE];
ppp info[SIZE];
int pos1[SIZE];
int pos2[SIZE];
ll bit[2 * SIZE];
ll ans[SIZE];

void add(int x, ll y, int N)
{
    for (int i = x; i <= N; i += i & (-i)) {
        bit[i] += y;
    }
}
ll sum(int x)
{
    ll s = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
        s += bit[i];
    }
    return s;
}

void dfs(int v, int &o)
{
    pos1[v] = o ++;
    for (int i = 0; i < G[v].size(); i ++) {
        dfs(G[v][i], o);
    }
    pos2[v] = o ++;
}

int main()
{
    int N, root = -1;
    scanf("%d", &N);
    for (int i = 1; i <= N; i ++) {
        int p, r, t;
        scanf("%d%d%d", &p, &r, &t);
        info[i - 1] = ppp(pii(r, 0), pii(i, t));
        if (p == -1) {
            root = i;
        } else {
            G[p].push_back(i);
        }
    }
    int _o = 0; dfs(root, _o);
    for (int i = 0; i < N; i ++) {
        info[i].fi.se = pos1[info[i].se.fi];
    }
    sort(info, info + N);
    for (int i = 0; i < N; i ++) {
        int idx = info[i].se.fi;
        ans[idx] = sum(pos2[idx]) - sum(pos1[idx] - 1);
        add(pos2[idx], info[i].se.se, 2 * N);
    }
    for (int i = 1; i <= N; i ++) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
