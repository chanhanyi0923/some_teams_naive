#include <bits/stdc++.h>

using namespace std;

#define SIZE 55
#define eps 1e-5

double P[SIZE];

void build(int n)
{
	for (int i = 0; i <= n; i ++) {
		P[i] = 1;
		for (int j = 0; j < i; j ++) {
			P[i] *= 0.5 * (n - j) / (i - j);
		}
		for (int j = i; j < n; j ++) {
			P[i] *= 0.5;
		}
	}
}

int main()
{
	int T, N, V1, V2, W;
	scanf("%d", &T);
	for (int _c = 0; _c < T; _c ++) {
		scanf("%d%d%d%d", &N, &V1, &V2, &W);
		build(N - V1 - V2);
		
		/*
		for (int i = 0; i <= N - V1 - V2; i ++) {
			printf("%d %lf\n", i, P[i]); 
		}
		*/
		
		double ans = 0;
		bool flag = false;
		for (int i = 0; i <= N - V1 - V2; i ++) {
			if (V1 + i > V2 + N - V1 - V2 - i) {
				ans += P[i];
				flag = true;
			}
		}
		//printf("%lf\n", ans);
		if (ans * 100 > W + eps) {
			puts("GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!");
		} else if (!flag) {
			puts("RECOUNT!");
		} else {
			puts("PATIENCE, EVERYONE!");
		}
	}
	return 0;
}