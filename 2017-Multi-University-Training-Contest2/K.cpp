#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define eps 1e-6

int n;
struct point
{
	int x;
	int y;
	point():x(0),y(0){}
	point(int _x, int _y):x(_x), y(_y){}
};

typedef pair<pii, pii> ppp;
typedef pair<ppp, ppp> four_p;

map<pii, int> M;
map<four_p, int> MM;
vector<point> P;

int main()
{
	// const double pi = acos(-1);
	int N;
	while (cin >> N) {
		M.clear();
		MM.clear();
		P.clear();
		for (int i = 0; i < N; i ++) {
			int x, y;
			cin >> x >> y;
			M[pii(x, y)] = 1;
			P.push_back(point(x, y));
		}
		int ans = 0;
		for (int i = 0; i < N; i ++) {
			for (int j = 0; j < i; j ++) {
				int x3 = P[j].x + (P[j].y - P[i].y);
				int y3 = P[j].y - (P[j].x - P[i].x);
				int x4 = P[i].x + (P[j].y - P[i].y);
				int y4 = P[i].y - (P[j].x - P[i].x);
				if (M[pii(x3, y3)] == 1 && M[pii(x4, y4)] == 1) {
					pii aa[4] = {pii(P[i].x, P[i].y), pii(P[j].x, P[j].y), pii(x3, y3), pii(x4, y4)};
					sort(aa, aa + 4);
					if (MM[four_p(ppp(aa[0], aa[1]), ppp(aa[2], aa[3]))] == 0) {
						/*
						puts(" ");
						printf("%d %d\n", P[i].x, P[i].y);
						printf("%d %d\n", P[j].x, P[j].y);
						printf("%d %d\n", x3, y3);
						printf("%d %d\n---\n", x4, y4);
						*/
						ans ++;
						MM[four_p(ppp(aa[0], aa[1]), ppp(aa[2], aa[3]))] = 1;
					}
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
