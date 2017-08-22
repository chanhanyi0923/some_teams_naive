#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define mp(a, b) make_pair(a, b)

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> ppi;
typedef pair<ppi, ppi> ppp;

map<ppp, int> E1;
map<ppp, int> E2;

#define SIZE 100005

ppi P1[SIZE];
ppi P2[SIZE];
vector<int> G1[SIZE];
vector<int> G2[SIZE];
bool vis[SIZE];

bool dfs1(int v, int p)
{
//printf("%d\n", v);
	if (vis[v]) return true;
	vis[v] = true;
	for (int i = 0; i < G1[v].size(); i ++) {
		int u = G1[v][i];
		if (u != p) {
			if (dfs1(u, v)) {
				return true;
			}
		}
	}
	return false;
}

bool dfs2(int v, int p)
{
	if (vis[v]) return true;
	vis[v] = true;
	for (int i = 0; i < G2[v].size(); i ++) {
		int u = G2[v][i];
		if (u != p) {
			if (dfs2(u, v)) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	int p1_sz = 0, p2_sz = 0;
	int K;
	scanf("%d", &K);
	for (int i = 0; i < K; i ++) {
		int x1, y1, z1, x2, y2, z2;
		scanf("%d%d%d", &x1, &y1, &z1);
		scanf("%d%d%d", &x2, &y2, &z2);
		ppi p1_1 = ppi(pii(x1, y1), z1);
		ppi p1_2 = ppi(pii(x2, y2), z2);
		ppi p2_1 = ppi(pii(x1, y1), 0);
		ppi p2_2 = ppi(pii(x2, y2), 0);
		if (p1_1 > p1_2) swap(p1_1, p1_2);
		if (p2_1 > p2_2) swap(p2_1, p2_2);
		E1[ppp(p1_1, p1_2)] = 1;
		E2[ppp(p2_1, p2_2)] = 1;
		/*
		P1.push_back(p1_1);
		P1.push_back(p1_2);
		P2.push_back(p2_1);
		P2.push_back(p2_2);
		*/
		P1[p1_sz ++] = p1_1;
		P1[p1_sz ++] = p1_2;
		P2[p2_sz ++] = p2_1;
		P2[p2_sz ++] = p2_2;
	}
	sort(P1, P1 + p1_sz);
	sort(P2, P2 + p2_sz);
//puts("1");
	for (map<ppp, int>::iterator it = E1.begin(); it != E1.end(); it ++) {
		ppi pA = it->fi.fi;
		ppi pB = it->fi.se;
		int a = (int)(lower_bound(P1, P1 + p1_sz, pA) - P1);
		int b = (int)(lower_bound(P1, P1 + p1_sz, pB) - P1);
		if (a == b) continue;
		//printf("%d: %d %d %d\n", a, pA.fi.fi, pA.fi.se, pA.se);
		//printf("%d: %d %d %d\n", b, pB.fi.fi, pB.fi.se, pB.se);
		G1[a].push_back(b);
		G1[b].push_back(a);
	}
//puts("2");
	for (map<ppp, int>::iterator it = E2.begin(); it != E2.end(); it ++) {
		ppi pA = it->fi.fi;
		ppi pB = it->fi.se;
		int a = (int)(lower_bound(P2, P2 + p2_sz, pA) - P2);
		int b = (int)(lower_bound(P2, P2 + p2_sz, pB) - P2);
		
		//printf("%d: %d %d %d\n", a, pA.fi.fi, pA.fi.se, pA.se);
		//printf("%d: %d %d %d\n", b, pB.fi.fi, pB.fi.se, pB.se);
		if (a == b) continue;
		G2[a].push_back(b);
		G2[b].push_back(a);
	}

	//puts("!");
	bool circle = false;
	for (int i = 0; i < SIZE; i ++) {
	//printf("%d\n", i);
		if (!vis[i] && dfs1(i, -1)) {
			circle = true;
			break;
		}
	}//puts("!");
	
	puts(circle ? "True closed chains" : "No true closed chains");

	for (int i = 0; i < SIZE; i ++) {
		vis[i] = false;
	}

	circle = false;
	for (int i = 0; i < SIZE; i ++) {
		if (!vis[i] && dfs2(i, -1)) {
			circle = true;
			break;
		}
	}

	puts(circle ? "Floor closed chains" : "No floor closed chains");
	return 0;	
}
