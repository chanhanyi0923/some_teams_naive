#include <cstdio>

typedef long long ll;

#define MOD 1000000007
#define SIZE 50000

inline int getK(int s)
{
    int l = 2, r = s + 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (1ll * mid * (mid + 1) / 2 - 1 <= s) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

ll f[SIZE];

ll qp(ll n, ll k)
{
    ll r = 1, sq = n;
    for (; k; k >>= 1) {
        if (k & 1) r = r * sq % MOD;
        sq = sq * sq % MOD;
    }
    return r;
}

int main()
{
    f[0] = 1;
    for (int i = 1; i < SIZE; i ++) {
        f[i] = (1ll * f[i - 1] * i) % MOD;
        //printf("%lld\n", f[i]);
    }
    //
    int T, N;
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &N);
        if (N <= 4) { printf("%d\n", N); continue; }
        int k = getK(N);
        ll sum = 1ll * k * (k + 1) / 2 - 1;
        //printf("k = %d\n", k);
        int r = N - sum;
        //printf("r = %d\n", r);
        ll ans;
        if (r == k) {
//            ans = f[k] / 2 * (k + 2);
            ans = f[k] * qp(2, MOD - 2) % MOD;
            ans = ans * (k + 2) % MOD;
        } else {
//            ans = f[k + 1] / (k - r - 1);
            ans = f[k + 1] * qp(k - r + 1, MOD - 2) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}