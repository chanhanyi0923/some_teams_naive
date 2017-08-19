#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

bool a[3000][3000];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 0; i + 1 < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                scanf("%d", &a[i][j]);
                a[j][i] = a[i][j];
            }
        
        }
        
        int flag = true;
        
        if (n > 10)
            flag = false;
        else
        
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    if ((a[i][j] == 1 && a[i][k] == 1 && a[j][k] == 1) || (a[i][j] == 0 && a[i][k] == 0 && a[j][k] == 0))
                    {
                        flag = false;
                        goto ED;
                    }
                }
            }
        }
        
        ED:
        if (flag)
        {
            cout << "Great Team!" << endl;
        }
        else
        {
            cout << "Bad Team!" << endl;
        }
    }
}

