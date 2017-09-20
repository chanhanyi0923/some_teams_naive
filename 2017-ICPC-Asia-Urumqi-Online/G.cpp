#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

#define SIZE 100005

struct BIT
{
    #define BIAS 5
    int size; ll d[SIZE];
    void init(int N)
    {
        size = N;
        for (int i = 0; i < size + BIAS; i ++) d[i] = 0;
    }
    void add(int i, ll x)
    {
        for (i += BIAS; i < size + BIAS; i += i & -i) d[i] += x;
    }
    ll sum(int i)
    {
        ll s = 0;
        for (i += BIAS; i > 0; i -= i & -i) s += d[i];
        return s;
    }
};

BIT B;

int cnt[SIZE];
char S1[SIZE], S2[20];

namespace KMP
{
    int f[20];
    void build(char *s, int N)
    {
        int pos = f[0] = -1;
        for (int i = 1; i < N; i ++) {
            while (pos != -1 && s[pos + 1] != s[i]) pos = f[pos];
            if (s[pos + 1] == s[i]) pos ++;
            f[i] = pos;
        }
    }
    void match(char *a, int aN, char *b, int bN, int x)
    {
        int pos = -1;
        for (int i = 0; i < aN; i ++) {
            while (pos != -1 && b[pos + 1] != a[i]) pos = f[pos];
            if (b[pos + 1] == a[i]) pos ++;
            bool m = false;
            if (pos == bN - 1) {
                m = true;
                pos = f[pos];
            }
            int idx = i + x - bN + 1;
            if (idx < x) continue;
            if (cnt[idx] == 0 && m) {
                B.add(idx, 1);
                cnt[idx] = 1;
            }
            if (cnt[idx] == 1 && !m) {
                B.add(idx, -1);
                cnt[idx] = 0;
            }
        }
    }
};

int main()
{
    int T, Q;
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &Q);
        scanf("%s%s", S1, S2);
        int len = strlen(S1), len2 = strlen(S2);
        KMP::build(S2, len2);
        B.init(len);
        for (int i = 0; i < len + 5; i ++) cnt[i] = 0;
        KMP::match(S1, len, S2, len2, 0);
        while (Q --) {
            char buf[10]; scanf("%s", buf);
            if (buf[0] == 'Q') {
                int l, r; scanf("%d%d", &l, &r); l --; r --;
                r -= len2 - 1;
                if (r < l) { puts("0"); continue; }
                printf("%lld\n", B.sum(r) - B.sum(l - 1));
            } else {
                int x; scanf("%d%s", &x, buf); x --;
                S1[x] = buf[0];
                int l = max(0, x - len2 + 1), r = min(len - 1, x + len2 - 1);
                KMP::match(S1 + l, r - l + 1, S2, len2, l);
            }
        }
        puts("");
    }
    return 0;
}
