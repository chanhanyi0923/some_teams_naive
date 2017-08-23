#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;

inline int qp(int n, int k)
{
    int r = 1, sq = n;
    for (; k; k >>= 1) {
        if (k & 1) r = r * sq % 13;
        sq = sq * sq % 13;
    }
    return r;
}

#define T_SIZE 505
#define SIZE 205

int cof[T_SIZE][SIZE];
int con[T_SIZE];
int sol[SIZE];
bool used[T_SIZE];

void solve(int N, int M)
{
    for (int i = 0; i < N; i ++) {
        int l = -1;
        for (int j = 0; j < M; j ++) {
            if (cof[j][i] != 0 && !used[j]) {
                l = j;
                used[l] = true;
                break;
            }
        }
        for (int j = 0; j < M; j ++) {
            if (j == l || cof[j][i] == 0) continue;
            int rate = cof[j][i] * qp(cof[l][i], 11) % 13;
            for (int k = 0; k < N; k ++) {
                cof[j][k] -= cof[l][k] * rate;
                cof[j][k] = (cof[j][k] % 13 + 13) % 13;
            }
            con[j] -= con[l] * rate;
            con[j] = (con[j] % 13 + 13) % 13;
        }
        sol[i] = l;
    }
    for (int i = 0; i < N; i ++) {
        int l = sol[i];
        sol[i] = con[l] * qp(cof[l][i], 11) % 13;
        sol[i] = (sol[i] % 13 + 13) % 13;
    }
}

map<pii, int> M1;
pii M2[SIZE];

int get_num(int a, int b)
{
    static int x = -1;
    if (a > b) swap(a, b);
    map<pii, int>::iterator it = M1.find(pii(a, b));
    if (it == M1.end()) {
        M1[pii(a, b)] = ++ x;
        M2[x] = pii(a, b);
        return x;
    } else {
        return it->second;
    }
}

vector<pii> G[SIZE];
int d[SIZE]; bool vis[SIZE];
priority_queue< pii, vector<pii>, greater<pii> > Q;
int SP(int s, int t)
{
    for (int i = 0; i < SIZE; i ++) d[i] = 1 << 29;
    d[s] = 0; Q.push(pii(0, s));
    while (!Q.empty()) {
        int v = Q.top().se; Q.pop();
        vis[v] = false;
        for (int i = 0; i < G[v].size(); i ++) {
            int u = G[v][i].se, w = G[v][i].fi;
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                Q.push(pii(d[u], u));
            }
        }
    }
    return d[t];
}

int main()
{
    int N, A, R, T;
    scanf("%d%d%d%d", &N, &A, &R, &T);
    int mat_sz = 0;
    for (int i = 0; i < T; i ++) {
        int d, p, a, b;
        scanf("%d%d%d", &d, &p, &a);
        con[i] = d % 13;
        for (int j = 1; j < p; j ++) {
            scanf("%d", &b);
            int num = get_num(a, b);
            mat_sz = max(mat_sz, num + 1);
            cof[i][num] = (cof[i][num] + 1) % 13;
            a = b;
        }
    }
    solve(mat_sz, T);
    for (int i = 0; i < mat_sz; i ++) {
        pii e = M2[i]; int w = sol[i];
        G[e.fi].push_back(pii(w, e.se));
        G[e.se].push_back(pii(w, e.fi));
    }
    printf("%d\n", SP(A, R));
    return 0;
}