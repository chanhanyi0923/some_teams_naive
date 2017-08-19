#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define fi first
#define se second

typedef pair<int, int> pii;

#define SIZE 50005

vector<int> G[SIZE];//origin graph
vector<int> G2[SIZE];//SCC -> DAG

// SCC
vector<int> S;
int dfn[SIZE], low[SIZE];
int cpn[SIZE];
int cpn_sz[SIZE];
char cpn_t[SIZE];//component type(0: normal, 1: SCC, 2: many circle SCC)
char max_from[SIZE];//max from type
bool inS[SIZE];
bool vis[SIZE];
// DAG BFS
queue<int> Q;
int deg[SIZE];


int SCC_dfs(int v, int &o)
{
    if (low[v] != -1) return low[v];
    dfn[v] = low[v] = o ++;
    S.push_back(v);
    inS[v] = true;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        SCC_dfs(u, o);
        if (inS[u]) low[v] = min(low[v], low[u]);
    }
    if (low[v] == dfn[v]) {
        int u;
        do {
            u = S.back(); S.pop_back();
            cpn[u] = v;
            cpn_sz[v] ++;
            inS[u] = false;
        } while (u != v);
    }
    return low[v];
}

void SCC(int N)
{
    S.clear();
    for (int i = 0; i <= N; i ++) {
        inS[i] = false;
        cpn[i] = i;
        cpn_sz[i] = 0;
        dfn[i] = low[i] = -1;
    }
    int o = 0;
    for (int i = 0; i <= N; i ++) {
        SCC_dfs(i, o);
    }
}

bool dfs(int v, int c)
{
    if (vis[v]) return false;
    vis[v] = true;
    int _deg = 0;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        if (cpn[u] == c) _deg ++;
    }
    if (_deg >= 2) return true;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        if (cpn[u] == c) {
            if (dfs(u, c)) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int N, M;
    while (EOF != scanf("%d%d", &N, &M) && (N > 0 || M > 0)) {
        for (int i = 0; i <= N; i ++) {
            G[i].clear();
            G2[i].clear();
            vis[i] = false;
            cpn_t[i] = 0;
            cpn_sz[i] = 0;
            max_from[i] = 0;
        }
        for (int i = 0; i < M; i ++) {
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
        }
        SCC(N);

        for (int i = 0; i <= N; i ++) {
            if (cpn_sz[i] > 1) {// is SCC
                if (dfs(i, i)) {
                    cpn_t[i] = 2;// many circles SCC
                } else {
                    cpn_t[i] = 1;//SCC
                }
            } else if (cpn_sz[i] == 1) {
                cpn_t[i] = 0;
            }
        }

        // SCC -> DAG
        for (int i = 0; i <= N; i ++) {
            deg[i] = 0;
        }
        for (int i = 0; i <= N; i ++) {
            for (int j = 0; j < G[i].size(); j ++) {
                int a = cpn[i];
                int b = cpn[G[i][j]];
                if (a == b) continue;
                G2[b].push_back(a);
                deg[a] ++;
            }
        }
        // BFS
        int ans = 0;

        while (!Q.empty()) Q.pop();
        for (int i = 0; i <= N; i ++) {
            if (deg[i] == 0) Q.push(i);
            // second: fron_type 0 -> normal, 1 -> SCC, 2 -> many circles SCC
        }
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            char cur_t = max(max_from[v], cpn_t[v]);
            if (cpn_t[v] == 2 || max_from[v] == 2 ||
               (cpn_t[v] == 1 && max_from[v] >= 1)) {
                ans += cpn_sz[v];
                cur_t = 2;
            }
            for (int i = 0; i < G2[v].size(); i ++) {
                int u = G2[v][i];
                max_from[u] = max(max_from[u], cur_t);
                if (-- deg[u] == 0) {
                    Q.push(u);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
