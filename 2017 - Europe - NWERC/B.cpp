#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

typedef pair<int, int> pii;

#define fi first
#define se second

#define SIZE 100005

vector<pii> G[SIZE * 2];

// SCC
vector<int> S;
vector<int> C[SIZE];
int dfn[SIZE], low[SIZE], cpn[SIZE]; bool inS[SIZE];
int SCC(int v)
{
    static int o = 0;
    if (low[v] != -1) return low[v];
    dfn[v] = low[v] = o ++;
    S.push_back(v); inS[v] = true;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i].se; SCC(u);
        if (inS[u]) low[v] = min(low[v], low[u]);
    }
    if (low[v] == dfn[v]) {
        int u;
        do {
            u = S.back(); S.pop_back();
            C[v].push_back(u);
            cpn[u] = v;
            inS[u] = false;
        } while (u != v);
    }
    return low[v];
}

// modify graph
map<int, bool> vis;
map< int, map<int, int> > dis;
void dfs(int s, int v, int d)
{
    if (vis[v]) return;
    vis[v] = true;
    if (s != v) dis[s][v] = max(dis[s][v], d);
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i].se;
        if (cpn[v] != cpn[u]) continue;
        dfs(s, u, d + 1);
    }
    vis[v] = false;
}
void modify(int v)
{
    if (C[v].size() == 1) return;
    dis.clear(); vis.clear();
    for (int i = 0; i < C[v].size(); i ++) {
        dfs(C[v][i], C[v][i], 0);
    }
    for (int i = 0; i < C[v].size(); i ++) {
        int u = C[v][i];
        for (int j = 0; j < G[u].size(); j ++) {
            if (cpn[G[u][j].se] != cpn[u]) {
                G[u + SIZE].push_back(G[u][j]);
            }
        }
        G[u].clear();
    }
    for (int i = 0; i < C[v].size(); i ++) {
        for (int j = 0; j < C[v].size(); j ++) {
            int x = C[v][i], y = C[v][j];
            if (dis[x][y] > 0) {
                G[x].push_back(pii(dis[x][y], y + SIZE));
            } else if (x == y) {
                G[x].push_back(pii(0, y + SIZE));
            }
        }
    }
}

// DP
queue<int> Q;
int dp[SIZE * 2];
int deg[SIZE * 2];

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i ++) {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a - 1].push_back(pii(1, b - 1));
    }
    for (int i = 0; i < N; i ++) cpn[i] = i, dfn[i] = low[i] = -1;
    for (int i = 0; i < N; i ++) SCC(i);
    for (int i = 0; i < N; i ++) if (cpn[i] == i) modify(i);
    for (int i = 0; i < 2 * SIZE; i ++) {
        for (int j = 0; j < G[i].size(); j ++) {
            deg[G[i][j].se] ++;
        }
    }
    for (int i = 0; i < 2 * SIZE; i ++) {
        if (deg[i] == 0) {
            Q.push(i);
        }
    }
    int ans = 0;
    while (!Q.empty()) {
        int v = Q.front(); Q.pop();
        ans = max(ans, dp[v]);
        for (int i = 0; i < G[v].size(); i ++) {
            int u = G[v][i].se, w = G[v][i].fi;
            dp[u] = max(dp[u], dp[v] + w);
            if (-- deg[u] == 0) Q.push(u);
        }
    }
    printf("%d\n", ans + 1);
    return 0;
}
