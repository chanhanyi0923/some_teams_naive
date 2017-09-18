#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
//typedef pair<pii, pii> ppp;

#define fi first
#define se second

#define INF (1ll << 60)
#define SIZE 100005

int V[SIZE];
vector<pii> G[SIZE];
ll ans;

pii dfs(int v, int p)
{
    ll a_max = V[v], b_max = -V[v];
    int cnt = 0;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i].se;
        ll w = G[v][i].fi;
        if (u == p) continue;
        cnt ++;
        pii result = dfs(u, v);
        ll a = result.fi, b = result.se;// a = add, b = sub
        a_max = max(a_max, a - w);
        b_max = max(b_max, b - w);
    }

    ans = max(ans, a_max + b_max);
    ans = max(ans, a_max - V[v]);
    ans = max(ans, b_max + V[v]);
    return pii(a_max, b_max);
}

int main()
{
    int T, N;
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &N);
        ans = 0;
        for (int i = 0; i < N + 3; i ++) {
            V[i] = 0; G[i].clear();
        }
        for (int i = 0; i < N; i ++) {
            scanf("%d", V + i);
        }
        for (int i = 1; i < N; i ++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            -- a; -- b;
            G[a].push_back(pii(c, b));
            G[b].push_back(pii(c, a));
        }
        dfs(0, -1);
        printf("%lld\n", ans);
    }
    return 0;
}
