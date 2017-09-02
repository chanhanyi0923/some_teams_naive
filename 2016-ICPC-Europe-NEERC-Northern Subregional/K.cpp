#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define fi first
#define se second

typedef pair<int, int> pii;
typedef pair<int, pii> pip;

int main()
{
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);
	int d, m, y, n;
	scanf("%d%d%d", &d, &m, &y);
	pip X = pip(y, pii(m, d));
	scanf("%d", &n);
	pip A = pip(0, pii(0,0));
	int ans = -1;
	for (int i = 0; i < n; i ++) {
		scanf("%d%d%d", &d, &m, &y);
		pip K = pip(y, pii(m, d));
		if (X.fi - K.fi >= 19 || (X.fi - K.fi == 18 && (X.se.fi > K.se.fi || (X.se.fi == K.se.fi && X.se.se >= K.se.se)))) {
			//printf("! %d\n", i);
			if (K > A) {
				ans = i + 1;
				A = K;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
