#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

#define SIZE 100005
#define INF (1 << 29)

char str[SIZE];
bool del[SIZE];
int ch[SIZE];
pii num1[SIZE], num2[SIZE];
vector<int> G[SIZE];
pii N1[SIZE], N2[SIZE];
int N1_sz, N2_sz;

int getSize(int v, int p)
{
    int s = 1;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        if (u == p || del[u]) continue;
        s += getSize(u, v);
    }
    return s;
}

pii findCenter(int v, int p, int size)
{
    pii ans = pii(INF, INF);
    ch[v] = 1;
    int max_ch = -INF;
    for (int i = 0; i < G[v].size(); i ++) {
        int u = G[v][i];
        if (u == p || del[u]) continue;
        ans = min(ans, findCenter(u, v, size));
        ch[v] += ch[u];
        max_ch = max(max_ch, ch[u]);
    }
    max_ch = max(max_ch, size - ch[v]);
    return min(ans, pii(max_ch, v));
}

void dfs1(int v, int p, pii now, int x, bool push)
{
    // fi: ')', se: '('
    num1[v] = now;
    if (str[v] == '(') {
        num1[v].se ++;
    } else {
        if (num1[v].se > 0) {
            num1[v].se --;
        } else {
            num1[v].fi ++;
        }
    }
    if (push) {
        N1[N1_sz ++] = num1[v];
    }
	if (x != -1) {
		dfs1(x, v, num1[v], -1, true);
	} else {
		for (int i = 0; i < G[v].size(); i ++) {
			int u = G[v][i];
			if (u == p || del[u]) continue;
			dfs1(u, v, num1[v], -1, true);
		}
	}
}

void dfs2(int v, int p, pii now, int x, bool push)
{
    // fi: ')', se: '('
    num2[v] = now;
    if (str[v] == ')') {
        num2[v].fi ++;
    } else {
        if (num2[v].fi > 0) {
            num2[v].fi --;
        } else {
            num2[v].se ++;
        }
    }
    if (push) {
        N2[N2_sz ++] = num2[v];
    }
	if (x != -1) {
		dfs2(x, v, num2[v], -1, true);
	} else {
		for (int i = 0; i < G[v].size(); i ++) {
			int u = G[v][i];
			if (u == p || del[u]) continue;
			dfs2(u, v, num2[v], -1, true);
		}
	}
}

inline ll cal(int v, int x)
{
    N1_sz = N2_sz = 0;
    dfs1(v, -1, pii(0, 0), x, x == -1);
    dfs2(v, -1, pii(0, 0), x, x == -1);
    sort(N1, N1 + N1_sz);
    sort(N2, N2 + N2_sz);

    ll ans = 0;
    for (int i = 0; i < N2_sz; i ++) {
        if (N2[i].fi != 0) continue;
        pii target = pii(N2[i].se, 0);
        if (str[v] == '(') {
            if (target.fi > 0) {
                target.fi --;
            } else {
                target.se ++;
            }
        } else {
            target.fi ++;
        }
        pii *p1 = lower_bound(N1, N1 + N1_sz, target);
        pii *p2 = upper_bound(N1, N1 + N1_sz, target);
        ans += (int)(p2 - p1);
    }
    return ans;
}

ll DAC(int v, int p)
{
    int tree_size = getSize(v, -1);
    int c = findCenter(v, -1, tree_size).second;
    ll ans = cal(c, -1);
    del[c] = true;
    for (int i = 0; i < G[c].size(); i ++) {
        int u = G[c][i];
        if (u == p || del[u]) continue;
        ans -= cal(c, u);
        ans += DAC(u, c);
    }
    return ans;
}

inline int get_int()
{
	int c = getchar();
	for (; c < '0' || c > '9'; c = getchar());
	int r = 0;
	for (; c >= '0' && c <= '9'; c = getchar()) {
		r = r * 10 + c - '0';
	}
	return r;
}

int main()
{
    int N;
    scanf("%d%s", &N, str);
    for (int i = 1; i < N; i ++) {
        int a, b;
        a = get_int(); b = get_int();
		G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }
    printf("%lld\n", DAC(0, -1));
    return 0;
}
