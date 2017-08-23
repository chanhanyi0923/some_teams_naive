#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

int char_map[200];
inline void initIdx()
{
    for (int i = 0; i < 10; i ++) {
        char_map[i + '0'] = i;
    }
    for (int i = 0; i < 26; i ++) {
        char_map[i + 'A'] = char_map[i + 'a'] = i + 10;
    }
    char_map['o'] = char_map['O'] = char_map['0'];
    char_map['i'] = char_map['I'] = char_map['1'];
    char_map['e'] = char_map['E'] = char_map['3'];
    char_map['s'] = char_map['S'] = char_map['5'];
    char_map['t'] = char_map['T'] = char_map['7'];
}
inline int getIdx(char c)
{
    return char_map[c];
}

#define CHAR_SIZE 40
#define SIZE 1005
#define MAX_LEN 30
#define MOD 1000003

struct Trie
{
    static Trie mem[SIZE], *pmem;
    Trie *ch[CHAR_SIZE], *fail;
    Trie *next[CHAR_SIZE]; bool next_end[CHAR_SIZE];
    bool end;
    Trie()
    {
        fail = NULL; end = false;
        for (int i = 0; i < CHAR_SIZE; i ++) ch[i] = NULL;
        for (int i = 0; i < CHAR_SIZE; i ++) next[i] = NULL, next_end[i] = false;
    }
    void insert(char *s)
    {
        if (*s) {
            int idx = getIdx(*s);
            if (ch[idx] == NULL) ch[idx] = new(pmem ++) Trie;
            ch[idx]->insert(s + 1);
        } else {
            end = true;
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
            for (int i = 0; i < CHAR_SIZE; i ++) {
                if (t->ch[i] == NULL) continue;
                t->ch[i]->fail = getFail(t->fail, i);
                Q.push(t->ch[i]);
            }
        }
    }
    void build_next()
    {
        queue<Trie*> Q;
        Q.push(this);
        while (!Q.empty()) {
            Trie *t = Q.front(); Q.pop();
            for (int k = 0; k < CHAR_SIZE; k ++) {
                Trie *ptr = t;
                t->next[k] = ptr = ptr->ch[k] ? ptr->ch[k] : getFail(ptr, k);
                while (ptr && !t->next_end[k]) {
                    t->next_end[k] = t->next_end[k] || ptr->end;
                    ptr = ptr->fail;
                }
                if (t->ch[k]) Q.push(t->ch[k]);
            }
        }
    }
} Trie::mem[SIZE], *Trie::pmem;

ll dp[MAX_LEN][SIZE][8];

char toC(int x)
{
    if (0 <= x && x <= 9) return x + '0';
    if (10 <= x && x <= 35) return x - 10 + 'a';
    if (36 <= x && x <= 61) return x - 36 + 'A';
}

int main()
{
    initIdx();
    int A, B, N;
    char str[SIZE];
    Trie::pmem = Trie::mem;
    Trie *AC = new(Trie::pmem ++) Trie;
    scanf("%d%d%d", &A, &B, &N);
    for (int i = 0; i < N; i ++) {
        scanf("%s", str);
        AC->insert(str);
    }
    AC->build();
    AC->build_next();
    int sz = (int)(Trie::pmem - Trie::mem);
    for (int i = 0; i < MAX_LEN; i ++) {
        for (int j = 0; j < SIZE; j ++) {
            for (int k = 0; k < 8; k ++) {
                dp[i][j][k] = 0;
            }
        }
    }
    dp[0][0][0] = 1;
    for (int i = 0; i < B; i ++) {
        for (int j = 0; j < sz; j ++) {
            for (int m = 0; m < 8; m ++) {
                for (int k = 0; k < (26 + 26 + 10); k ++) {
                    char c = toC(k); int idx = getIdx(c);
                    Trie *ptr = Trie::mem + j;
                    if (ptr->next_end[idx]) continue;
                    int next = (int)(ptr->next[idx] - Trie::mem);
                    int cur_m = m;
                    if ('0' <= c && c <= '9') cur_m = cur_m | (1 << 0);
                    if ('a' <= c && c <= 'z') cur_m = cur_m | (1 << 1);
                    if ('A' <= c && c <= 'Z') cur_m = cur_m | (1 << 2);
                    dp[i + 1][next][cur_m] += dp[i][j][m];
                    dp[i + 1][next][cur_m] %= MOD;
                }
            }
        }
    }
    ll ans = 0;
    for (int i = A; i <= B; i ++) {
        for (int j = 0; j < sz; j ++) {
            ans += dp[i][j][7];
            ans %= MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
