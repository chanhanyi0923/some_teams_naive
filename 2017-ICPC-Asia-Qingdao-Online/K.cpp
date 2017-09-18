#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

set<ll> k;

int main()
{
    for (int i = 2; i <= 1000010; i++)
    {
        ll tmp = 1ll * i * i * i - 1ll * (i - 1) * (i - 1) * (i - 1);
        k.insert(tmp);
        if (tmp > 1000000000000ll)
        {
            break;
        }
    }
    
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        ll p;
        cin >> p;
        if (k.count(p) != 0)
        {
            puts("YES");
        }
        else
        {
            puts("NO");
        }
    }
}    
