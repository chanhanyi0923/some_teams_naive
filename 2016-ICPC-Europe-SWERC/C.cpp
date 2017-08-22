#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define mp(a, b) make_pair(a, b)

typedef long long ll;
typedef pair<int, int> pii;

int main()
{
	int D, R, T;
	scanf("%d%d%d", &D, &R, &T);
	for (int N = 1; N <= 1000; N ++) {
		int yR = N, yT = N - D;
		if (yT <= 0) continue;
		// yR * (yR + 1) / 2 - 6 + ans = R
		// yT * (yT + 1) / 2 - 3 - ans = T
		if ((yR * (yR + 1) / 2 - 6) + (yT * (yT + 1) / 2 - 3) == R + T) {
			printf("%d\n", (R - T + 3 + yT * (yT + 1) / 2 - yR * (yR + 1) / 2) / 2);
		}
	}
	return 0;
	
	
}
