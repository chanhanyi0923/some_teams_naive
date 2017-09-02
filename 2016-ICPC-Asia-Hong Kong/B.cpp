#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;
const double eps = 1e-10;
int cmp(double x)
{
    if (fabs(x) < eps)
        return 0;
    if (x > 0)    return 1;
    return -1;
}

double sqr(double x)
{
    return x * x;
}

struct point
{
    double x;
    double y;
    point (double a, double b): x(a), y(b) {}
    
    friend point operator - (const point &a, const point &b)
    {
        return point (a.x - b.x, a.y - b.y);
    }
    
    double norm()
    {
        return sqrt(sqr(x) + sqr(y));
    }
};

double dist(const point &a, const point &b)
{
    return (a - b).norm();
}

int R, l, w;

double det(const point &a, const point &b)
{
    return a.x * b.y - a.y * b.x;
}

double dot(const point &a, const point &b)
{
    return a.x * b.x + a.y * b.y;
}
double dps(const point p, const point s, const point t)
{
    if (cmp(dot(p - s, t - s)) < 0)
        return (p - s).norm();
    if (cmp(dot(p - t, s - t)) < 0)
        return (p - t).norm();
    return fabs(det(s - p, t - p) / dist(s, t));
}
int main()
{
    cin >> R >> l >> w;
    int t;
    cin >> t;
    point p1(0, 0);
    point p2(l, 0);
    point p4(0, w);
    point p5(l, w);
    point p7(1e5, w);
    while (t--)
    {
        double Min = 2 * R;
        double th1, th2;
        cin >> th2 >> th1;
        point p3(l * (1 - cos(th1)), l * sin(th1));
        point p6(l * (1 - cos(th2)), w + l * sin(th2));
        
        Min = min(Min, dps(p3, p5, p6));
        Min = min(Min, dps(p2, p5, p6));
        Min = min(Min, dps(p5, p2, p3));
        Min = min(Min, dps(p6, p2, p3));
        Min = min(Min, dps(p4, p5, p6));
        Min = min(Min, dps(p3, p5, p7));
        Min = min(Min, dps(p2, p5, p7));
        
        printf("%.15lf\n", Min / 2);
    }
}