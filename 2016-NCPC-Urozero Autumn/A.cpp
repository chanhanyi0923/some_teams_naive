#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

#define fi first
#define se second

typedef pair<int, int> pii;
typedef pair<pii, pii> ppp;

#define SIZE 1005

int cnt[SIZE][SIZE];
ppp re[10005];
int f[SIZE * SIZE];

void init()
{
	for (int i = 0; i < SIZE * SIZE; i ++) {
		f[i] = i;
	}
}
int find(int x)
{
	return f[x] == x ? x : (f[x] = find(f[x]));
}

int ans[10005];

int main()
{
	int N, M, Q;
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 0; i < Q; i ++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		re[i] = ppp(pii(x1, y1), pii(x2, y2));
		for (int i = x1; i <= x2; i ++) {
			for (int j = y1; j <= y2; j ++) {
				cnt[i][j] ++;
			}
		}
	}
	const int dx[4] = {0, 1, 0, -1};
	const int dy[4] = {1, 0, -1, 0};
	init();
	int num = 0;
	for (int i = 1; i <= N; i ++) {
		for (int j = 1; j <= M; j ++) {
			if (cnt[i][j] == 0) {
				num ++;
				for (int k = 0; k < 4; k ++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
					if (cnt[nx][ny] != 0) continue;
					int p, q;
					if ((p = find(nx * SIZE + ny)) != (q = find(i * SIZE + j))) {
						f[p] = q;
						num --;
					}
				}
			}
		}
	}
	for (int i = Q - 1; i > -1; i --) {
		ans[i] = num;
		for (int x = re[i].fi.fi; x <= re[i].se.fi; x ++) {
			for (int y = re[i].fi.se; y <= re[i].se.se; y ++) {
				if (-- cnt[x][y] == 0) {
					num ++;
					for (int k = 0; k < 4; k ++) {
						int nx = x + dx[k], ny = y + dy[k];
						if (nx < 1 || nx > N || ny < 1 || ny > M) continue;
						if (cnt[nx][ny] != 0) continue;
						int p, q;
						if ((p = find(nx * SIZE + ny)) != (q = find(x * SIZE + y))) {
							f[p] = q;
							num --;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < Q; i ++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
