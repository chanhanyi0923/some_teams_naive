#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    char str[12][100] = {"rat", "ox", "tiger", "rabbit", "dragon", "snake", "horse", "sheep", "monkey", "rooster", "dog", "pig"};
    map<string, int> S;
    for (int i = 0; i < 12; i ++) {
        S[string(str[i])] = i;
    }
    int T; scanf("%d", &T);
    while (T --) {
        string A1, A2;
        cin >> A1 >> A2;
        int ans = (12 + S[A2] - S[A1]) % 12;
        if (ans == 0) ans = 12;
        cout << ans << endl;
    }
    return 0;
}
