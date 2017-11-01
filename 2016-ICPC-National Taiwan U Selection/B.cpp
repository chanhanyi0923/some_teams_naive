#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

#define SIZE 100005

struct Trie
{
    static Trie mem[30 * SIZE];
    static int cnt;
    int ch[2]; bool end;
    Trie() { ch[0] = ch[1] = -1; end = false; }
    void insert(int x, int b)
    {
        if (b >= 0) {
            int idx = (x & (1 << b)) ? 1 : 0;
            if (ch[idx] == -1) { ch[idx] = cnt ++; mem[ch[idx]] = Trie(); }
            mem[ch[idx]].insert(x, b - 1);
        } else {
            end = true;
        }
    }
};

Trie Trie::mem[30 * SIZE];
int Trie::cnt;

int _P[SIZE], P[SIZE];

inline int cal(int L1, int R1, int L2, int R2, int B)
{
    if (L1 > R1 || L2 > R2) return 0;
    Trie::cnt = 1; Trie::mem[0] = Trie();
    Trie &root = Trie::mem[0];
    for (int i = L1; i <= R1; i ++) {
        root.insert(P[i], B);
    }
    int ans = (1 << 30);
    for (int i = L2; i <= R2; i ++) {
        Trie t = root;
        int d = 0;
        for (int j = B; j > -1; j --) {
            int idx = (P[i] & (1 << j)) ? 1 : 0;
            if (t.ch[idx] == -1) {
                d ^= (1 << j);
                t = Trie::mem[t.ch[1 - idx]];
            } else {
                t = Trie::mem[t.ch[idx]];
            }
        }
        ans = min(ans, d);
    }
    return ans;
}

ll solve(int L, int R, int B, int base)
{
    if (R <= L) return 0;
    if (L + 1 == R) return P[L] ^ P[R];
    int M = (int)(lower_bound(P + L, P + R + 1, base + (1 << B)) - P);
    ll re = solve(L, M - 1, B - 1, base) +
            solve(M, R,     B - 1, base + (1 << B)) +
            cal(L, M - 1, M, R, B);
    return re;
}

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i ++) {
        scanf("%d", _P + i);
    }
    sort(_P, _P + N);
    int _N = 1; P[0] = _P[0];
    for (int i = 1; i < N; i ++) {
        if (_P[i] != _P[i - 1]) P[_N ++] = _P[i];
    }
    N = _N;

    int bit;
    for (bit = 30; bit > -1; bit --) {
        if (P[N - 1] & (1 << bit)) break;
    }
    printf("%lld\n", solve(0, N - 1, bit, 0));
    return 0;
}
