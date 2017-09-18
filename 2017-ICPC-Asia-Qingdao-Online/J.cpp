#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int a[100010];
int _prev[100010];
int _next[100010];
int flag[100010];

int is_del(int idx)
{
    int p = _prev[idx];
    int n = _next[idx];
    if (a[p] <= a[idx] && a[idx] <= a[n])
    {
        return false;
    }
    return true;
}

void del(int idx)
{
    int pr = _prev[idx];
    int ne = _next[idx];
    _next[pr] = ne;
    _prev[ne] = pr;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        memset(a, 0, sizeof(a));
        memset(_prev, 0, sizeof(_prev));
        memset(_next, 0, sizeof(_next));
        memset(flag, 0, sizeof(flag));
        
        for (int i = 1; i <= n; i++)
        {
            _prev[i] = i - 1;
            _next[i] = i + 1;
            flag[i] = 0;
            scanf("%d\n", &a[i]);
        }
        a[0] = -1;
        _prev[0] = -1;
        _next[0] = 1;
        flag[0] = 1000000;
            
        _prev[n + 1] = n;
        a[n + 1] = 1000000;
        _next[n + 1] = -1;
        flag[n + 1] = 1000000;
    
        vector<int> q;
        for (int i = 1; i <= n; i++)
        {
            if (is_del(i))
            {
                q.push_back(i);
                flag[i] = 1;
            }
        }
        int k = 0;
        int co = n;
        while (!q.empty())
        {
            k++;
            vector<int> to_del;
            vector<int> _next_q;
            to_del.clear();
            _next_q.clear();
            for (size_t i = 0; i < q.size(); i++)
            {
                if (flag[q[i]] == 1000000)
                {
                    continue;
                }
                if (is_del(q[i]))
                {
                    to_del.push_back(q[i]);
                    int pr = _prev[q[i]];
                    int ne = _next[q[i]];
                    if (pr != -1 && flag[pr] < k)
                    {
                        //printf("pr = %d\n", pr);
                        _next_q.push_back(pr);
                        flag[pr] = k;
                    }
                    if (ne != -1 && flag[ne] < k)
                    {
                        //printf("ne = %d\n", ne);
                        _next_q.push_back(ne);
                        flag[ne] = k;
                    }
                }
            }
            
            for (size_t i = 0; i < to_del.size(); i++)
            {
                del(to_del[i]);
                flag[to_del[i]] = 1000000;
                co--;
            }
            
            q.clear();
            for (size_t i = 0; i < _next_q.size(); i++)
            {
                q.push_back(_next_q[i]);
            }
        }
        
        int st = _next[0];
        vector<int> output;
        output.clear();
        while (st != n + 1)
        {
            output.push_back(a[st]);
            st = _next[st];
        }
        cout << output.size() << endl;
        for (size_t i = 0; i < output.size(); i++)
        {
            printf("%d ", output[i]);
        }

        printf("\n");
    }
    return 0;
}
