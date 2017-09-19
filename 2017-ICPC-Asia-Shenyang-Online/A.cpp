#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define SIZE 100005

struct Node
{
    int val;
    int ch[27], fa;
    Node()
    {
        for (int i = 0; i < 27; i ++) ch[i] = -1;
        val = 0; fa = -1;
    }
} pool[SIZE * 2];

namespace SAM
{
    int cnt, root, last;
    void init()
    {
        if (cnt) {
            for (int i = 0; i < cnt; i ++) {
                pool[i] = Node();
            }
        }
        cnt = 1;
        root = 0;
        last = root;
    }
    void add(int c)
    {
        int p = last, np = cnt ++;
        last = np;
        pool[np].val = pool[p].val + 1;
        for (; p != -1 && pool[p].ch[c] == -1; p = pool[p].fa) {
            pool[p].ch[c] = np;
        }
        if (p == -1) {
            pool[np].fa = root;
        } else {
            int q = pool[p].ch[c];
            if (pool[p].val + 1 == pool[q].val) {
                pool[np].fa = q;
            } else {
                int nq = cnt ++;
                pool[nq] = pool[q];
                pool[nq].val = pool[p].val + 1;
                pool[q].fa = nq;
                pool[np].fa = nq;
                for (; p != -1 && pool[p].ch[c] == q; p = pool[p].fa) {
                    pool[p].ch[c] = nq;
                }
            }
        }
    }
}

int K;
// int ans;

pii dp[SIZE * 2];

pii dfs(int tree, int c)
{
    if (c == 26) return pii(1, 0);
    if (dp[tree] != pii(-1, -1)) return dp[tree];
    pii num = pii(0, 0);
    for (int i = 0; i < 27; i ++) {
        if (pool[tree].ch[i] != -1) {
            pii x = dfs(pool[tree].ch[i], i);
            num.first += x.first;
            num.second += x.second;
        }
    }
    if (num.first == K) num.second ++;
    return dp[tree] = num;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%d\n", &K);
        SAM::init();
        for (int c = getchar(); c >= 'a' && c <= 'z'; c = getchar()) {
            SAM::add(c - 'a');
        }
        SAM::add(26);
        for (int i = 0; i < SAM::cnt; i ++) dp[i] = pii(-1, -1);
        //ans = 0;
        int ans = dfs(SAM::root, -1).second;
        printf("%d\n", ans);
    }
    return 0;
}
