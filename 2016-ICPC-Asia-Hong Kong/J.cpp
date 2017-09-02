#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;

#define INF (1 << 30)
#define SIZE 200005

struct Trie
{
    static Trie mem[SIZE], *pmem;
    Trie *ch[2], *next[2];
    Trie *fail, *n_fail;
    bool end, all_end;
    Trie()
    {
        all_end = end = false;
        fail = n_fail = NULL;
        next[0] = next[1] = ch[0] = ch[1] = NULL;
    }
    void insert(char *s)
    {
        if (*s) {
            int idx = *s - '0';
            if (ch[idx] == NULL) next[idx] = ch[idx] = new(pmem ++) Trie;
            ch[idx]->insert(s + 1);
        } else {
            all_end = end = true;
        }
    }
    Trie *getFail(Trie *ptr, int idx)
    {
        while (ptr && ptr->ch[idx] == NULL) ptr = ptr->fail;
        return ptr ? ptr->ch[idx] : this;
    }
    void build()
    {
        queue<Trie*> Q;
        Q.push(this);
        while (!Q.empty()) {
            Trie *t = Q.front(); Q.pop();
            for (int i = 0; i < 2; i ++) {
                if (t->ch[i] == NULL) continue;
                t->ch[i]->fail = getFail(t->fail, i);
                Q.push(t->ch[i]);
            }
        }
    }
    inline Trie *nextFail(Trie *t) { return t->n_fail ? t->n_fail : this; }
    void build_next()
    {
        queue<Trie*> Q;
        if (next[0]) Q.push(next[0]);
        if (next[1]) Q.push(next[1]);
        while (!Q.empty()) {
            Trie *t = Q.front(); Q.pop();
            if (t->n_fail && t->n_fail->all_end) {
                t->all_end = true;
            }
            for (int i = 0; i < 2; i ++) {
                if (t->next[i]) {
                    Q.push(t->next[i]);
                    t->next[i]->n_fail = nextFail(t)->next[i];
                } else {
                    t->next[i] = nextFail(t)->next[i];
                }
            }
        }
    }
} Trie::mem[SIZE], *Trie::pmem;

char buf[SIZE];

bool use[SIZE];
int deg[SIZE];
int dp[SIZE];
pii last[SIZE];
map<pii, int> M;

void dfs(Trie *root)
{
    if (root == NULL) return;
    for (int i = 0; i < 2; i ++) {
        if (root->next[i]->all_end) continue;
        int a = root->next[i] - Trie::mem;
        int b = root - Trie::mem;
        pii q = pii(a, b); if(q.fi > q.se) swap(q.fi, q.se);
        if (M[q] == 0) {
            M[q] = 1;
            deg[a] ++;
            use[a] = use[b] = true;
        }
        dfs(root->ch[i]);
    }
}

int main()
{
    Trie::pmem = Trie::mem;
    Trie *AC = new(Trie::pmem ++) Trie;
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i ++) {
        scanf("%s", buf);
        AC->insert(buf);
    }
    AC->build_next();

    dfs(AC);
    bool no_ans = false;
    if (deg[0] > 0) no_ans = true;
    int ans = -1, ans_num = -1;
    if (!no_ans) {
    int sz = (int)(Trie::pmem - Trie::mem);
    for (int i = 0; i < sz; i ++) last[i] = pii(-1, -1);
    queue<Trie*> Q; Q.push(AC);

    while (!Q.empty()) {
        Trie *t = Q.front(); Q.pop();
        int num_t = (int)(t - Trie::mem);
        if (ans < dp[num_t]) {
            ans = dp[num_t];
            ans_num = num_t;
        }
        for (int i = 0; i < 2; i ++) {
            if (t->next[i]->all_end) continue;
            int num_x = (int)(t->next[i] - Trie::mem);
            if (dp[num_x] < dp[num_t] + 1) {
                dp[num_x] = dp[num_t] + 1;
                last[num_x] = pii(i, num_t);
            }
            if ((-- deg[num_x]) == 0) {
                Q.push(Trie::mem + num_x);
            }
        }
    }
    for (int i = 0; i < sz; i ++) {
        if (deg[i] > 0) {
            no_ans = true;
            break;
        }
    }
    }
    if (no_ans) {
        puts("-1");
    } else {
        int _ = 0;
        for (int i = ans_num; i != -1; i = last[i].se) {
            if (last[i].se == -1) break;
            buf[_ ++] = '0' + last[i].fi;
        }
        buf[_] = 0;
        for (-- _; _ > -1; _ --) putchar(buf[_]); puts("");
    }
    return 0;
}
