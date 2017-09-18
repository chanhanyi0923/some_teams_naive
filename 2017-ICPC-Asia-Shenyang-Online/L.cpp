#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
int a[2000100];
// int b[1000100];
//int c[1000100];
//int d[2000100];//sum
int d[2000100];
int q[2000100];
int n;
//int sum[1000100];//draw_sum

inline int calc(int l, int r)
{
    int ret;
//    printf("calc(%d %d)\n", l + 1, r);
    if (l == 0)
        ret =  a[r];
    ret =  a[r] - a[l];
//    printf("ret = %d\n", ret);
    return ret;
}

inline int get_int()
{
    int ret = 0, c;
    while ((c = getchar()) < '0' || c > '9');
    ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') {
        ret = ret * 10 + c - '0';
    }
    return ret;
}
    
int main()
{
    while (EOF != scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
        {
            a[i] = get_int();
            //scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            int bx;
            bx = get_int();
            //scanf("%d\n", &bx);
            int cx = a[i] - bx;
            d[i] = d[i - 1] + cx;
        }
        for (int i = n + 1; i <= n + n; i++)
        {
            d[i] = d[n] + d[i - n];
        }
        
        for (int i = 2; i <= n; i++)
        {
            a[i] += a[i - 1];
        }
        for (int i = n + 1; i <= n + n; i++)
        {
            a[i] = a[n] + a[i - n];
        }
        
        //printf("initalize ok\n");
    
        int qf = 0;
        int qb = 0;

        int score = 0;
        int ans = 3000000;
        for (int i = 0; i < n + n; i++)
        {
            int h = d[i];
            //printf("i = %d, d[i] = %d\n", i, d[i]);
            while (qf > qb && d[q[qf - 1]] > h)
            {
                int now_score = calc(q[qf - 1], i);
                if (now_score >= score)
                {
                
                    if (now_score == score)
                        ans = min(ans, q[qf - 1]);
                    else ans = q[qf - 1];
            //        printf("ans = %d\n", ans);
                    score = now_score;
                }
                qf--;
            }
            q[qf++] = i;
            if (i - q[qb] >= n)
            {
                int now_score = calc(q[qb], i);
                if (now_score >= score)
                {
                    
                    if (now_score == score)
                        ans = min(ans, q[qb]);
                    else ans = q[qb];
            //        printf("ans = %d\n", ans);
                    score = now_score;
                }
                qb++;
            }
        }
        
        printf("%d\n", ans);
    }
}
