#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define SIZE 2000005

char buf[1000005];
char S[SIZE];
int Z[SIZE];

void calZ(const char *s, int n)
{
    for (int i = 0; i < n; i ++) {
        Z[i] = 0;
    }
    for (int i = 1, x = 0, y = 0; i < n; i ++) {
        if (i <= y) Z[i] = min(y - i, Z[i - x]);
        while (i + Z[i] < n && s[i + Z[i]] == s[Z[i]]) Z[i] ++;
        if (y <= i + Z[i]) x = i, y = i + Z[i];
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int _c = 0; _c < T; _c ++) {
        scanf("%s", buf);
        int l1 = strlen(buf);
        //S[l1] = '-';
        scanf("%s", S);
        int l2 = strlen(S);
        S[l2] = '-';
        for (int i = 0; i < l1; i ++) {
            S[l2 + 1 + i] = buf[i];
        }

        reverse(S, S + l2);
        reverse(S + l2 + 1, S + l1 + l2 + 1);
        calZ(S, l1 + l2 + 1);
/*
        puts("!!");
        puts(S);

        for (int i = l2 + 1; i < l1 + l2 + 1; i ++) {
            printf("%d %d\n", i, Z[i]);
        }
        puts("!");
*/
        ll ans = 0;
        for (int i = l2 + 1; i < l1 + l2 + 1; i ++) {
        
            ans += 1ll * Z[i] * (Z[i] + 1) / 2;
            ans %= 1000000007;
        }
        printf("%lld\n", ans);
    }
    return 0;
}