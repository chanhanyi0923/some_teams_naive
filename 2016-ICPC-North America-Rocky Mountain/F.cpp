#include <bits/stdc++.h>

using namespace std;

map<int, int> T1, T2;

int main()
{
	int X1, X2, N1, N2;
	scanf("%d%d", &X1, &X2);
	scanf("%d", &N1);
	for (int i = 0; i < N1; i ++) {
		int t; scanf("%d", &t);
		T1[t] = 1;
	}
	scanf("%d", &N2);
	for (int i = 0; i < N2; i ++) {
		int t; scanf("%d", &t);
		T2[t] = 1;
	}
	int s1 = 0, s2 = 0;
	int i;
	for (i = 0; i <= 1000010; i ++) {
		//printf("%d %d %d\n", i, X1, X2);
		if (abs(X1 - X2) <= 4) {
			printf("bumper tap at time %d\n", i);
			return 0;
		}
		if (T1.count(i)) {
			s1 = 1 - s1;
		}
		if (T2.count(i)) {
			s2 = 1 - s2;
		}
		X1 += s1;
		X2 += s2;
	}
	if (X1 > X2 && s1 < s2) {
		int ans = X1 - X2 - 4;
		printf("bumper tap at time %d\n", ans + i);
	} else if (X2 > X1 && s2 < s1) {
		int ans = X2 - X1 - 4;
		printf("bumper tap at time %d\n", ans + i);
	} else {
		puts("safe and sound");
	}
	return 0;
}