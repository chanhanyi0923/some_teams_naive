#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

typedef pair<int, int> pii;

#define fi first
#define se second

#define INF (1 << 30)
#define SIZE 100005

int f[SIZE][18];
vector<int> G[SIZE];
int cpn[SIZE], dep[SIZE], sz[SIZE], o_l[SIZE], o_r[SIZE], gan[SIZE];
int oo[2 * SIZE];
set<int> S1[SIZE], S2[SIZE];

int dfs(int v, int p, int c, int d)
{
    // printf("%d\n", v);
    static int o = -1;
    o_l[v] = ++ o; oo[o] = v; cpn[v] = c; sz[v] = 0; dep[v] = d;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        if (u == p) continue;
        sz[v] += dfs(u, v, c == -1 ? u : c, d + 1);
    }
    o_r[v] = ++ o; oo[o] = v;
    if (sz[v] == 0) ++ sz[v];
    return sz[v];
}

void build_lca(int N)
{
    for (int i = 1; i < 18; i ++) {
        for (int j = 0; j < N; j ++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }
}

int lca(int a, int b)
{
    if (a == INF || b == -1) return -1;
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 17; i > -1; i --) {
        if (dep[f[a][i]] >= dep[b]) {
            a = f[a][i];
        }
    }
    if (a == b) return a;
    for (int i = 17; i > -1; i --) {
        if (f[a][i] != f[b][i]) {
            a = f[a][i];
            b = f[b][i];
        }
    }
    return f[a][0];
}

inline int L(int c)
{
    set<int>::iterator it = S1[c].lower_bound(-1);
    return it == S1[c].end() ? INF : oo[*it];
}

inline int R(int c)
{
    set<int>::iterator it = S2[c].lower_bound(-INF);
    return it == S2[c].end() ? (-1) : oo[-*it];
}

int main()
{
    freopen("gangsters.in", "r", stdin);
    freopen("gangsters.out", "w", stdout);
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i < N; i ++) {
        int x; scanf("%d", &x); x --;
        f[i][0] = x;
        G[x].push_back(i);
    }
    build_lca(N);
    dfs(0, -1, -1, 0);

/*
    for (int i = 0; i < N; i ++) {
        printf("%d %d %d\n", cpn[i], o_l[i], o_r[i]);
    }
*/
    pii ans = pii(0, 0);
    for (int i = 0; i < M; i ++) {
        char buf[10]; scanf("%s", buf);
        int x; scanf("%d", &x); x --;
        
        int c = cpn[x]; int ori_lca = lca(L(c), R(c));
        int ori_num = ori_lca == -1 ? 0 : (sz[ori_lca] - gan[c]);
        if (buf[0] == '+') {
            gan[c] ++;
            S1[c].insert(o_l[x]); S2[c].insert(-o_r[x]);
            int cur_lca = lca(L(c), R(c));
            int cur_num = sz[cur_lca] - gan[c];
            if (ori_lca == -1) {
                ans.fi ++;
            }
            ans.se += cur_num - ori_num;
            //add x

        } else if (buf[0] == '-') {
            gan[c] --;
            S1[c].erase(o_l[x]); S2[c].erase(-o_r[x]);
            int cur_lca = lca(L(c), R(c));
            int cur_num = cur_lca == -1 ? 0 : (sz[cur_lca] - gan[c]);
            //sub x
            if (cur_lca == -1) {
                ans.fi --;
            }
            ans.se += cur_num - ori_num;
        }
        printf("%d %d\n", ans.fi, ans.se);
    }
    return 0;
}
