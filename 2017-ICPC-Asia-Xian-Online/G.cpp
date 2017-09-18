#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define SIZE 50005
#define LOG_SIZE 17
#define SQRT_N 255

#define fi first
#define se second

typedef pair<int, int> pii;
typedef pair<int, pii> pip;

int W[SIZE];
vector<int> G[SIZE];
vector<pip> query[SIZE];
int ans[500005];
int dep[SIZE];
int dp[SIZE][LOG_SIZE];
int f[SIZE][LOG_SIZE];
int f_k[SIZE][LOG_SIZE];

void dfs(int v, int p, int d)
{
    f_k[v][0] = f[v][0] = p;
    dep[v] = d;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        if (u == p) continue;
        dfs(u, v, d + 1);
    }
}

inline void build_normal(int N)
{
    for (int j = 1; j < LOG_SIZE; j ++) {
        for (int i = 1; i <= N; i ++) {
            f_k[i][j] = f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }
}

inline void build(int N)
{
    for (int i = 1; i <= N; i ++) {
        dp[i][0] = W[i] ^ W[f_k[i][0]];
    }
    for (int j = 1; j < LOG_SIZE; j ++) {
        for (int i = 1; i <= N; i ++) {
            int x = f_k[i][j - 1];
            f_k[i][j] = f_k[x][j - 1];
            dp[i][j] = dp[i][j - 1] ^ dp[x][j - 1] ^ W[x];
        }
    }
}

inline int lca(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = LOG_SIZE - 1; i > -1; i --) {
        if (dep[f[a][i]] >= dep[b]) {
            a = f[a][i];
        }
    }
    if (a == b) return a;
    for (int i = LOG_SIZE - 1; i > -1; i --) {
        if (f[a][i] != f[b][i]) {
            a = f[a][i];
            b = f[b][i];
        }
    }
    return f[a][0];
}

inline int go(int v, int k)
{
    for (int i = 0; (1 << i) <= k; i ++) {
        if ((1 << i) & k) {
            if (dep[v] - dep[f[v][i]] < (1 << i)) {
                return -1;
            }
            v = f[v][i];
        }
    }
    return v;
}

inline void work1(int &result, int a, int c, int k)
{
    result ^= W[a];
    for (int i = LOG_SIZE - 1; i > -1; i --) {
        if (dep[f_k[a][i]] >= dep[c] && dep[a] - dep[f_k[a][i]] == 1ll * k * (1 << i)) {
            result ^= W[a] ^ dp[a][i];
            a = f_k[a][i];
        }
    }
}

inline void work2(int &result, int a, int c, int k)
{
    for (int v = a; v != -1 && dep[v] >= dep[c]; v = go(v, k)) {
        result ^= W[v];
    }
}

inline int get_int()
{
    int c, r = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (; c >= '0' && c <= '9'; c = getchar()) r = r * 10 + c - '0';
    return r;
}

int main()
{
    int N, Q;
    while (EOF != scanf("%d%d", &N, &Q)) {
        for (int i = 0; i <= N; i ++) {
            G[i].clear();
            query[i].clear();
        }
        for (int i = 1; i < N; i ++) {
            int a = get_int(); int b = get_int();
            G[a].push_back(b);
            G[b].push_back(a);
        }
        for (int i = 1; i <= N; i ++) {
            W[i] = get_int();
        }
        dfs(1, 1, 0);
        build_normal(N);

        for (int i = 0; i < Q; i ++) {
            int a = get_int(); int b = get_int(); int k = get_int();
            query[k].push_back(pip(i, pii(a, b)));
        }
        for (int k = 1; k <= N; k ++) {
            if (query[k].size() > 0 && k < SQRT_N) build(N);
            for (int _ = 0; _ < query[k].size(); _ ++) {
                int num = query[k][_].fi;
                int a = query[k][_].se.fi;
                int b = query[k][_].se.se;
                if (a == b) { ans[num] = W[a]; continue; }
                int c = lca(a, b);
                int dis = ((dep[b] - dep[c]) - (k - (dep[a] - dep[c]) % k) % k) % k;
                b = dis < 0 ? c : go(b, dis % k);
                if (a == b) { ans[num] = W[a]; continue; }
                int result = 0;
                if (a != c) {
                    if (k < SQRT_N) {
                        work1(result, a, c, k);
                    } else {
                        work2(result, a, c, k);
                    }
                }
                if (b != c) {
                    if (k < SQRT_N) {
                        work1(result, b, c, k);
                    } else {
                        work2(result, b, c, k);
                    }
                }
                if ((a != c && (dep[a] - dep[c]) % k == 0) &&
                    (b != c && (dep[b] - dep[c]) % k == 0)) {
                    result ^= W[c];
                }
                ans[num] = result;
            }
            if (k < SQRT_N) {
                for (int i = 1; i <= N; i ++) {
                    f_k[i][0] = f[f_k[i][0]][0];
                }
            }
        }
        for (int i = 0; i < Q; i ++) {
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
