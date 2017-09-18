#include <bits/stdc++.h>

using namespace std;
int a[100010];
int g[100010];
int d[100010];
typedef long long ll;
const ll INF = 1000000007;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        int m;
        cin >> n >> m;

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        
        
        memset(g, 0, sizeof(g));
        memset(d, 0, sizeof(d));
        
        int ans1 = 0;
        for (int i = 1; i <= n; i++)
        {
            g[i] = INF;
        }
        for (int i = 0; i < n; i++)
        {
            int k = upper_bound(g + 1, g + n + 1, a[i]) - g;
            d[i] = k;
            g[k] = a[i];
            ans1 = max(ans1, d[i]);
        }
        //printf("ans1 = %d\n", ans1);
        
        int ans2 = 0;
        for (int i = 1; i <= n; i++)
        {
            g[i] = INF;
            a[i - 1] = -a[i - 1];
        }
    
        //memset(g, 0, sizeof(g));
        memset(d, 0, sizeof(d));
        for (int i = 0; i < n; i++)
        {
            int k = upper_bound(g + 1, g + n + 1, a[i]) - g;
            d[i] = k;
            g[k] = a[i];
            ans2 = max(ans2, d[i]);
        }
        
    //    printf("ans2 = %d\n", ans2);
        int ans = max(ans1, ans2);
        if (n - ans <= m)
        {
            printf("A is a magic array.\n");
        }
        else
        {
            printf("A is not a magic array.\n");
        }
    }
}
