#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;

int times[300010] = {0};
int level[300010] = {0};
int sum[300010] = {0};
vector<int> ans[300010];
vector<int> job[300010];
struct _player
{
    int job;
    int num;
    _player(int j, int n):job(j), num(n) {}
    _player():job(0), num(0) {}
};


_player player[300010];

bool cmp(const _player& a, const _player& b)
{
    return job[a.job].size() > job[b.job].size() || (job[a.job].size() == job[b.job].size() && a.job < b.job);
}

int main()
{
    int n, m, p;
    scanf("%d%d%d\n", &n, &m, &p);
    for (int i = 0; i < m; i++)
    {
        int size;
        scanf("%d", &size);
        job[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &job[i][j]);
            job[i][j]--;    
        }
    }
    
    for (int i = 0; i < p; i++)
    {
        player[i].num = i + 1;
        scanf("%d", &player[i].job);
        player[i].job--;
    }
    
    sort(player, player + p, cmp);
    
    for (int i = 0; i < p; i++)
    {
        times[player[i].job]++;
    }
    
/*    for (int i = 0; i < p; i++)
    {
        printf("player#%d: job = %d, num = %d\n", i, player[i].job, player[i].num);
    }
    
    for (int i = 0; i < m; i++)
    {
        printf("times[%d] = %d\n", i, times[i]);
    }
*/
    for (int i = 0; i < p; i+= times[player[i].job])
    {
        vector<int> & now_job = job[player[i].job];
        int this_level = level[now_job[0]] + 1;
        
        for (size_t j = 0; j < now_job.size(); j++)
        {
            level[now_job[j]] += times[player[i].job];
        }
        
        for (int j = 0; j < times[player[i].job]; j++)
        {
            sum[this_level + j] += now_job.size();
            ans[this_level + j].push_back(player[i + j].num);
        }
        
    /*    printf("i = %d\n", i);
        printf("this_level = %d\n", this_level);
        printf("\nlevel:\n");
        for (int i = 0; i < n;i++)
        {
            printf("%d ", level[i]);
        }
        printf("\nsum:\n");
        for (int i = 0; i < p; i++)
        {
            printf("%d ", sum[i]);
        }
        printf("\n--------\n");
        */
    }
    
    int tot = 0;
    while (sum[tot + 1] == n)
    {
        tot++;
    }
    
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
    {
        printf("%d", ans[i].size());
        for (size_t j = 0; j < ans[i].size(); j++)
        {
            printf(" %d", ans[i][j]);
        }
        printf("\n");
    }
    
    return 0;    
}