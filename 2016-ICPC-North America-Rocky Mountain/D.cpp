#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define SIZE 1005
#define INF (1ll << 60)

typedef long long ll;
typedef pair<ll, ll> pii;

int N;
bool isC[SIZE], vis[SIZE];
vector<pii> O[SIZE];
ll d[SIZE];
priority_queue< pii, vector<pii>, greater<pii> > Q;

struct edge{ int to, rev, cap; };
vector<edge> G[SIZE * 2];
void add_edge(int a, int b)
{
    // printf("%d -> %d\n", a, b);
    G[a].push_back((edge){b, G[b].size(), 1});
    G[b].push_back((edge){a, G[a].size() - 1, 0});
}

void dfs2(int v, int s)
{
    if (vis[v]) return;
    vis[v] = true;
    if (isC[v] && isC[s] && v != s) {
        // printf("%d -> %d\n", s, v);
        add_edge(s, v + SIZE);
    }
    for (int i = 0; i < O[v].size(); i ++) {
        int u = O[v][i].second;
        ll w = O[v][i].first;
        if (d[v] + w == d[u]) {
            dfs2(u, s);
        }
    }
}

void build_sp_graph(int s, int t)
{
    for (int i = 0; i < N; i ++) {
        d[i] = INF;
        vis[i] = false;
    }
    d[0] = 0;
    Q.push(pii(0, 0));
    while (!Q.empty()) {
        int v = Q.top().second; Q.pop();
        if (vis[v]) continue;
        vis[v] = true;
        for (int i = 0; i < O[v].size(); i ++) {
            int u = O[v][i].second;
            ll w = O[v][i].first;
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                Q.push(pii(d[u], u));
            }
        }
    }
    for (int i = 0; i < N; i ++) {
        if (!isC[i]) continue;
        for (int j = 0; j < N; j ++) {
            vis[j] = false;
        }
        dfs2(i, i);
    }

    for (int i = 0; i < N; i ++) {
        add_edge(s, i);
        add_edge(i + SIZE, t);
    }
}


int dfs(int s, int t, int f)
{
    if (s == t) return f;
    if (f == 0) return 0;
    if (vis[s]) return 0;
    vis[s] = true;
    for (int i = 0; i < G[s].size(); i ++) {
        edge &e = G[s][i];
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
            e.cap -= d;
            G[e.to][e.rev].cap += d;
            return d;
        }
    }
    return 0;
}

int match(int s, int t)
{
    int f = 0, d = 0;
    while (true) {
        vis[s] = vis[t] = false;
        for (int i = 0; i < N; i ++) {
            vis[i] = vis[i + SIZE] = false;
        }
        if (d = dfs(s, t, 1 << 30)) {
            f += d;
        } else {
            break;
        }
    }
    return f;
}

int main()
{
    int M, C;
    scanf("%d%d%d", &N, &M, &C);

    isC[0] = true;
    for (int i = 0; i < C; i ++) {
        int a;
        scanf("%d", &a);
        isC[a] = true;
    }

    for (int i = 0; i < M; i ++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        O[a].push_back(pii(c, b));
    }

    int s = 2 * SIZE - 1, t = 2 * SIZE - 2;
    build_sp_graph(s, t);
    printf("%d\n", C + 1 - match(s, t));
    return 0;
}