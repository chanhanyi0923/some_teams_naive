#include <bits/stdc++.h>

#define P 1000000007

using namespace std;
typedef long long ll;

long long F[40][40];  // 0110 wrong 0 correct

long long F0[40][40]; // 301103 : 0110 correct

void init()
{    
    for (int p = 2; p <= 36; p++)
    {
        F0[p][1] = p;
        F[p][1] = p - 1;
        for (int k = 2; k <= 40; k++)
        {
            F[p][k] = F[p][k - 1] * p;
            F0[p][k] = F0[p][k - 1] * p;
            //F[p][k] %= P;
            //F0[p][k] %= P;
        }
    }
    

    for (int p = 2; p <= 36; p++)
        for (int k = 40; k >= 2; k--)
        {
            F[p][k] = F[p][(k + 1) / 2];
            F0[p][k] = F0[p][(k + 1) / 2];
        }
    
    for (int p = 2; p <= 36; p++)
    {
        F[p][1]++;
    }
    
}

vector<int> num;

bool judge(int l, int r)
{
    while (l <= r)
    {
        if (num[l] != num[r])
        {
            return false;
        }
        l++;
        r--;
    }
    return true;
}


ll G(int l, int r, int p, int flag)
{
    
    if (l == r)
    {
        //printf("G(%d, %d) = %d\n", l, r, num[l] + 1);
        return num[l] + 1;
    }
    else if (r - l == 1)
    {
        //printf("G(%d, %d) = %d\n", l, r, min(num[l], num[r]) + 1 - flag);
        //return min(num[l], num[r]) + 1 - flag;
        ll ans;
        if (num[l] <= num[r])
            ans = num[l] + 1 - flag;
        else 
            ans = num[l] - flag;
        return ans;
    }
    
    ll ans = 0;
    
    ans += G(l + 1, r - 1, p, 0);

    if (num[l] > num[r] && judge(l + 1, r - 1))
    {
        ans--;
    };
    
    // 3????3
    
    ans += (num[l] - flag) * F0[p][r - l - 1];
    //printf("G(%d, %d) = %lld\n", l, r, ans);
    return ans;
}


ll work(int p)
{
    if (num.empty())
    {
        return 1;
    }
    
    ll ans = G(0, num.size() - 1, p, 1);
    for (int k = 1; k < num.size(); k++)
    {
        ans += F[p][k];
        //printf("ans += F[%d][%d] = %lld\n", p, k, F[p][k]);
    }
    //ans %= P;
    return ans;
}

void trans(int x, int p)
{
    num.clear();
    while (x > 0)
    {
        num.push_back(x % p);
        x /= p;
    }
    
    while (num.back() == 0)
    {
        num.pop_back();
    }
    
    reverse(num.begin(), num.end());
    
}

int main()
{
    init();

    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        ll l, r, L, R;
        cin >> L >> R >> l >> r;
        ll ans = 0;
        for (int p = l; p <= r; p++)
        {
            trans(R, p);
            ll a1 = work(p);
            trans(L - 1, p);
            ll a2 = work(p);
            ll a = a1 - a2;
            
            //printf("p = %d a = %lld\n", p, a);
            ans += a * p + (R - L + 1 - a);
            //ans %= P;
        }
        
        //ans %= P;
        cout << "Case #" << i + 1 << ": " << ans << endl;
    }
}