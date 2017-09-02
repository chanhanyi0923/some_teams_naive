#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;

#define INF (1 << 30)

pii arr[50005];

int main()
{
    int n;
    scanf("%d", &n);
    int a_min = 2000;
    int a_max = 0;
    int b_min = 2000;
    int b_max = 0;
    
    int A_min = 2000;
    int B_min = 2000;
    int A_max = 0;
    int B_max = 0;
    long double Min = 10000000;
    long double Max = -1;
    
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a < a_min)
        {
            a_min = a;
        }
        if (a > a_max)
        {
            a_max = a;
        }
        if (b < b_min)
        {
            b_min = b;
        }
        if (b > b_max)
        {
            b_max = b;
        }
        
        long double A = a * log(2) + b * log(3);
        if (A < Min)
        {
            A_min = a;
            B_min = b;
            Min = A;
        }
        if (A > Max)
        {
            A_max = a;
            B_max = b;
            Max = A;
        }
    }
    
    for (int i = 1; i <= n; i++)
    {
        int gcd = i - 1;
        int lcm = n - i;
        if (lcm == 0)
        {
            printf("%d %d ", a_min, b_min);
        }
        else if (lcm == 1)
        {
            printf("%d %d ", A_max, B_max);
        }
        else
        {
            printf("%d %d ", a_max, b_max);
        }
        
        if (gcd == 0)
        {
            printf("%d %d\n", a_max, b_max);
        }
        else if (gcd == 1)
        {
            printf("%d %d\n", A_min, B_min);
        }
        else
        {
            printf("%d %d\n", a_min, b_min);
        }
        

    }
    
    return 0;
}