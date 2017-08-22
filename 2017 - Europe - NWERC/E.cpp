#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int main()
{
	int N;
	int S[100];
	pii A[100];
	scanf("%d", &N);
	int sum = 0, big = 0;
	for (int i = 0; i < N; i ++) {
		scanf("%d", S + i);
		A[i] = pii(S[i], i);
		sum += S[i];
		big = max(big, S[i]);
	}
	if (sum - big < big) {
		puts("impossible");
	} else {
		sort(A, A + N);
		printf("%d", A[N - 1].second + 1);
		for (int i = 0; i < N - 1; i ++) {
			printf(" %d", A[i].second + 1);
		}
		puts("");
	}
	return 0;
}
