#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> pip;
typedef pair<pii, pii> ppp;
typedef pair<int, ppp> pipp;

#define fi first
#define se second

bool road[4][60][60];
int dis[1000];
int dir[1000];

int dir_int(int x)
{
    switch (x) {
        case 'E': return 0;
        case 'W': return 1;
        case 'N': return 2;
        case 'S': return 3;
    }
}
void connect(pii p, int d) { road[d][p.fi][p.se] = true; }
int rev_dir(int x)
{
    switch (x) {
        case 0: return 1;
        case 1: return 0;
        case 2: return 3;
        case 3: return 2;
    }
}
void add_edge(pii a, pii b)
{
    if (a.fi == b.fi) {
        if (a.se < b.se) {
            connect(a, 2);
            connect(b, 3);
        } else if (a.se > b.se) {
            connect(a, 3);
            connect(b, 2);
        }
    } else if (a.se == b.se) {
        if (a.fi < b.fi) {
            connect(a, 0);
            connect(b, 1);
        } else if (a.fi > b.fi) {
            connect(a, 1);
            connect(b, 0);
        }
    }
}

struct point
{
    bool lock; pii pos; int dir;
    point(){}
    bool operator < (const point &a) const
    {
        ppp b = ppp(pii(lock, dir), pos);
        ppp c = ppp(pii(a.lock, a.dir), a.pos);
        return b < c;
    }
};
struct bfs
{
    int dis; point p;
    bfs(){}
    bool operator < (const bfs &a) const
    {
        return dis == a.dis ? p < a.p : dis < a.dis;
    }
};

int main()
{
    int N, t_max;
    pii s;
    scanf("%d%d%d%d", &N, &s.fi, &s.se, &t_max);
    for (int i = 0; i < N; i ++) {
        pii pa, pb;
        scanf("%d%d%d%d", &pa.fi, &pa.se, &pb.fi, &pb.se);
        if (pa.fi == pb.fi) {
            int x = pa.fi, y1 = min(pa.se, pb.se), y2 = max(pa.se, pb.se);
            for (int y = y1; y < y2; y ++) {
                add_edge(pii(x, y), pii(x, y + 1));
            }
        }
        if (pa.se == pb.se) {
            int y = pa.se, x1 = min(pa.fi, pb.fi), x2 = max(pa.fi, pb.fi);
            for (int x = x1; x < x2; x ++) {
                add_edge(pii(x, y), pii(x + 1, y));
            }
        }
    }
    for (int i = 0; i < t_max; i ++) {
        int b1; char b2[10]; scanf("%d%s", &b1, b2);
        dis[i] = b1; dir[i] = dir_int(b2[0]);
    }
    //
    vector<point> points;
    point _fi; _fi.dir = -1; _fi.lock = false; _fi.pos = s;
    points.push_back(_fi);
    for (int t = 0; t < t_max; t ++) {
        queue<bfs> Q;
        for (int i = 0; i < points.size(); i ++) {
            bfs tmp; tmp.dis = 0; tmp.p = points[i];
            Q.push(tmp);
        }
        //printf("---\nt = %d:\n", t);
        points.clear();
        set<bfs> vis;
        while (!Q.empty()) {
            bfs tmp = Q.front(); point tmp2 = tmp.p;
            int cur_dis = tmp.dis;
            int lock = tmp2.lock;
            int cur_dir = tmp2.dir;
            pii cur_pos = tmp2.pos;
            Q.pop();
            //printf("dir = %d, (%d, %d), dir = %d\n", cur_dis, cur_pos.fi, cur_pos.se, cur_dir);
            if (cur_dis == dis[t]) {
                if (cur_dir == dir[t]) {
                    point tmp3;
                    tmp3.dir = dir[t]; tmp3.lock = false; tmp3.pos = cur_pos;
                    points.push_back(tmp3);
                } else if (cur_dir != rev_dir(dir[t])) {
                    point tmp3;
                    tmp3.dir = dir[t]; tmp3.lock = true; tmp3.pos = cur_pos;
                    points.push_back(tmp3);
                }
                continue;
            }
            const int dx[4] = {1, -1, 0, 0};
            const int dy[4] = {0, 0, 1, -1};
            for (int i = 0; i < 4; i ++) {
                if (!road[i][cur_pos.fi][cur_pos.se]) continue;

                bfs nxt;
                {
                    point tmp3;
                    tmp3.pos = pii(cur_pos.fi + dx[i], cur_pos.se + dy[i]);
                    tmp3.lock = false;
                    tmp3.dir = i;
                    nxt.dis = cur_dis + 1; nxt.p = tmp3;
                }

                if (lock) {
                    if (cur_dir != i) continue;
                    if (vis.find(nxt) == vis.end()) {
                        vis.insert(nxt);
                        Q.push(nxt);
                    }
                } else {
                    if (cur_dir == rev_dir(i)) continue;
                    if (vis.find(nxt) == vis.end()) {
                        vis.insert(nxt);
                        Q.push(nxt);
                    }
                }
            }
        }
    }
    set<pii> ans;
    for (int i = 0; i < points.size(); i ++) {
        if (points[i].lock) {
            if (road[points[i].dir][points[i].pos.fi][points[i].pos.se]) {
                ans.insert(points[i].pos);
            }
        } else {
            ans.insert(points[i].pos);
        }
    }
    for (set<pii>::iterator it = ans.begin(); it != ans.end(); it ++) {
        printf("%d %d\n", it->fi, it->se);
    }
    return 0;
}