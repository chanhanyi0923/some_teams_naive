#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

struct point
{
	int x, y, z;
	point(){}
	point(int a, int b, int c): x(a), y(b), z(c) {}
	bool operator < (const point &a) const
	{
		return x == a.x ? (y == a.y ? z < a.z : y < a.y) : x < a.x;
	}
};

map< point, vector<pii> > M;

const point O[24] = {
	point(0, 0, 1), point(0, 1, 1), point(1, 0, 1), point(1, 1, 1),
	point(1, 0, 1), point(1, 1, 1), point(1, 0, 0), point(1, 1, 0),
	point(1, 0, 0), point(1, 1, 0), point(0, 0, 0), point(0, 1, 0),
	point(0, 0, 0), point(0, 1, 0), point(0, 0, 1), point(0, 1, 1),
	point(0, 0, 0), point(0, 0, 1), point(1, 0, 0), point(1, 0, 1),
	point(0, 1, 1), point(0, 1, 0), point(1, 1, 1), point(1, 1, 0),
};

bool check1()
{
/*
	for (int i = 0; i < 6; i ++) {
		for (int j = 0; j < 4; j ++) {
			point p = O[i * 4 + j];
			vector<pii> &vec = M[p];
			for (int k = 0; k < vec.size(); k ++) {
				if (vec[k].first == i) {
					printf("%d ", vec[k].second);
				}
			}
		}
		puts("");
	}
	puts("");
*/
/*
	for (int i = 0; i < 6; i ++) {
		for (int j = 0; j < 4; j ++) {
			point p = O[i * 4 + j];
			vector<pii> &vec = M[p];
			for (int k = 0; k < vec.size(); k ++) {
					printf("%d(%d) ", vec[k].second, vec[k].first);
			}
		}
		puts("");
	}
	puts("");
*/
	set<int> S;
	for (int i = 0; i < 6; i ++) {
		int num = -1;
		for (int j = 0; j < 4; j ++) {
			point p = O[i * 4 + j];
			vector<pii> &vec = M[p];
			for (int k = 0; k < vec.size(); k ++) {
				if (vec[k].first == i) {
					if (num == -1) {
						num = vec[k].second;
						S.insert(num);
					}
					if (vec[k].second != num) {
						return false;
					}
				}
			}
		}
	}
	if (S.size() != 6) return false;
	return true;
}

int ss(int i, int a, int b)
{
	point p1 = O[i * 4 + a];
	point p2 = O[i * 4 + b];
	vector<pii> &v1 = M[p1];
	vector<pii> &v2 = M[p2];
	for (int j = 0; j < v1.size(); j ++) {
		if (v1[j].first == i) continue;
		for (int k = 0; k < v2.size(); k ++) {
			if (v2[k].first == i) continue;
			if (v1[j].first == v2[k].first) {
				return v1[j].first;
			}
		}
	}
	return -1;
}

bool check2()
{
	// 0, 1, 2, 3
	// 2, 0, 3, 1
	const int nxt[4] = {2, 0, 3, 1};
	point p1, p2;
	for (int i = 0; i < 6; i ++) {
		{
			int s[4] = {ss(i, 0, 1), ss(i, 1, 3), ss(i, 2, 3), ss(i, 0, 2)};
			int nxt_s[4] = {ss(i, 0, 2), ss(i, 0, 1), ss(i, 1, 3), ss(i, 2, 3)};
			//puts("s[]:"); for (int j = 0; j < 4; j ++) printf("%d ", s[j]); puts("");
			//puts("nxt_s[]:"); for (int j = 0; j < 4; j ++) printf("%d ", nxt_s[j]); puts("");
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 2];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 1];
			p2 = O[i * 4 + 2];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 2];
			p2 = O[i * 4 + 3];
			swap(M[p1], M[p2]);
			//
			for (int j = 0; j < 4; j ++) {
				point p = O[i * 4 + j];
				vector<pii> &v = M[p];
				for (int k = 0; k < v.size(); k ++) {
					if (i != v[k].first) {
						int t;
						for (t = 0; t < 4; t ++) {
							if (nxt_s[t] == v[k].first) break;
						}
						v[k].first = s[t];
					}
				}
			}
			//
			//printf("change %d\n", i);
			if (check1()) return true;
			for (int j = 0; j < 4; j ++) {
				point p = O[i * 4 + j];
				vector<pii> &v = M[p];
				for (int k = 0; k < v.size(); k ++) {
					if (i != v[k].first) {
						int t;
						for (t = 0; t < 4; t ++) {
							if (s[t] == v[k].first) break;
						}
						v[k].first = nxt_s[t];
					}
				}
			}
			//
			p1 = O[i * 4 + 2];
			p2 = O[i * 4 + 3];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 1];
			p2 = O[i * 4 + 2];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 2];
			swap(M[p1], M[p2]);
		}
		{
			int s[4] = {ss(i, 0, 1), ss(i, 1, 3), ss(i, 2, 3), ss(i, 0, 2)};
			int nxt_s[4] = {ss(i, 1, 3), ss(i, 2, 3), ss(i, 0, 2), ss(i, 0, 1)};
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 2];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 3];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 1];
			swap(M[p1], M[p2]);
			for (int j = 0; j < 4; j ++) {
				point p = O[i * 4 + j];
				vector<pii> &v = M[p];
				for (int k = 0; k < v.size(); k ++) {
					if (i != v[k].first) {
						int t;
						for (t = 0; t < 4; t ++) {
							if (nxt_s[t] == v[k].first) break;
						}
						v[k].first = s[t];
					}
				}
			}

			//printf("change R %d\n", i);
			if (check1()) return true;
			for (int j = 0; j < 4; j ++) {
				point p = O[i * 4 + j];
				vector<pii> &v = M[p];
				for (int k = 0; k < v.size(); k ++) {
					if (i != v[k].first) {
						int t;
						for (t = 0; t < 4; t ++) {
							if (s[t] == v[k].first) break;
						}
						v[k].first = nxt_s[t];
					}
				}
			}
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 1];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 3];
			swap(M[p1], M[p2]);
			p1 = O[i * 4 + 0];
			p2 = O[i * 4 + 2];
			swap(M[p1], M[p2]);
		}
	}
	return false;
}

int main()
{
	int TTT;
	while (EOF != scanf("%d", &TTT)) {
	while (TTT --) {
		M.clear();
		for (int i = 0; i < 6; i ++) {
			for (int j = 0; j < 4; j ++) {
				int a; scanf("%d", &a);
				point p = O[i * 4 + j];
				M[p].push_back(pii(i, a));
			}
		}
		//
		if (check1() || check2()) {
			puts("YES");
		} else {
			puts("NO");
		}
		//
	}
	}
	return 0;
}