#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll P = 998244353;
struct matrix
{
    ll a[2][2];
    matrix()
    {
        memset(a, 0, sizeof(a));
    }
    matrix operator * (const matrix& b)
    {
        matrix ret;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    ret.a[i][j] += a[i][k] * b.a[k][j];
                    ret.a[i][j] %= P;
                }
            }
        }
        return ret;
    }
    
    void print() const
    {
        printf("%lld %lld\n", a[0][0], a[0][1]);
        printf("%lld %lld\n", a[1][0], a[1][1]);
    }
};

matrix maPow(const matrix& a, ll k)
{
    //a.print();
    //printf("k = %lld\n", k);
    matrix ret;
    if (k == 0)
    {
        ret.a[0][0] = ret.a[1][1] = 1;
        ret.a[0][1] = ret.a[1][0] = 0;
        return ret;
    }
    if (k % 2 == 0)
    {
        ret = maPow(a, k / 2);
        ret = ret * ret;
        return ret;
    }
    ret = maPow(a, k - 1);
    ret = ret * a;
    return ret;
}

ll fib(ll k)
{
    matrix s;
    s.a[0][0] = s.a[0][1] = s.a[1][0] = 1;
    s.a[1][1] = 0;
    matrix t = maPow(s, k);
    //printf("maPow(s, k):\n");
    //t.print();
    return (t.a[1][0] + t.a[1][1]) % P;
}
int main()
{
    ll n;
    while (cin >> n)
    {
        //n--;
        cout << fib(2 * n + 2) - 1 << endl;
    }
}
