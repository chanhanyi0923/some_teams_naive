#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 100000;
bool d[N];
int n;
ll res = LLONG_MAX;

struct nodes
{
	ll x, y;
}p[N];
nodes* ans;
bool cmpx(nodes a, nodes b)
{
	return a.x < b.x;
}

bool cmpy(nodes a, nodes b)
{
	return a.y < b.y;
}

ll dis(nodes a, nodes b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void build(int l, int r, nodes p[])
{
	if (l > r) return;
	int minx = min_element(p + l, p + r + 1, cmpx)->x;//STL
	int maxx = max_element(p + l, p + r + 1, cmpx)->x;
	int miny = min_element(p + l, p + r + 1, cmpy)->y;//STL
	int maxy = max_element(p + l, p + r + 1, cmpy)->y;
	int mid = l + r >> 1;
	d[mid] = (maxx - minx > maxy - miny);
	//选择极差较大的维划分
	nth_element(p + l, p + mid, p + r + 1, d[mid] ? cmpx : cmpy);//STL 可以在O(n)的时间里使第mid大的数在第mid位置上。但是不保证前后两部分数据有序
	build(l, mid - 1, p);
	build(mid + 1, r, p);
}

void find(int l, int r, nodes ask, nodes p[])
{//a为询问点
	if (l > r) return;
	int mid = l + r >> 1;
	ll dist = dis(ask, p[mid]);
	ll d1 = d[mid] ? (ask.x - p[mid].x) : (ask.y - p[mid].y);
	res = min(res, dist);
	int l1 = l, r1 = mid - 1;
	int l2 = mid + 1, r2 = r;
	if (d1 > 0)
	{//交换左右区间
		swap(l1, l2);
		swap(r1, r2);
	}
	find(l1, r1, ask, p);
	if (d1 * d1 < res) find(l2, r2, ask, p);
}
