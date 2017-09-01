#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll A[100];
ll B[10005];
ll dp[10005];

int main()
{
	int T, N, M;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d", &N, &M);
		ll now = -1; ll big = -1;
		for (int i = 0; i < M + 1; i ++) {
			dp[i] = 0;
			scanf("%lld", B + i);
			if (i > 0 && B[i] > 0 && now == -1) now = i;
			if (B[i] > 0) big = max(big, 1ll * i);
		}
		dp[0] = 1;
		int sz = 0;
		for (int i = 0; i < N; i ++) {
		//printf("!! %d\n", now);
			A[sz ++] = now;
			ll next = -1;
			// dp[now] --;
			for (int i = M; i >= 0; i --) {
				if (i + now <= M) {
					dp[i + now] += dp[i];
					if (dp[i + now] < B[i + now]) {
						next = i + now;
					}
				}
			}
			now = next;
			/*
			puts("--");
			for (int i = 0; i < M + 1; i ++) {
				printf("%lld ", dp[i]);
			}
			puts("--");
			*/
		}
		//ll sum = 0;
		printf("%lld", A[0]);
		for (int i = 1; i < sz; i ++) {
			printf(" %lld", A[i]);
			//sum += A[i];
		}
		puts("");
		//printf("%lld\n", big - sum);
	}
	return 0;
}
