#include <bits/stdc++.h>

using namespace std;

#define SIZE 200005

int a[SIZE], b[SIZE], pos_a[SIZE], pos_b[SIZE], X[SIZE];

int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i ++) {
		scanf("%d", a + i);
		pos_a[a[i]] = i;
	}
	for (int i = 0; i < N; i ++) {
		scanf("%d", b + i);
		pos_b[b[i]] = i;
	}
	/*
	for (int i = 0; i < N; i ++) {
		printf("%d ", pos_a[i]);
	}
	puts("");
	for (int i = 0; i < N; i ++) {
		printf("%d ", pos_b[i]);
	}
	puts("");
	*/
	int add = 0;
	for (int s = N + N - 2; add < N; s --) {
		for (int i = s - (N - 1); i < N; i ++) {
			//printf("! %d %d\n", i, s - i);
			int idx1 = (pos_a[i] + pos_b[s - i]) % N;
			int idx2 = (pos_a[s - i] + pos_b[i]) % N;
			//printf("%d %d\n", idx1, idx2);
			if (X[idx1] == 0) { X[idx1] = s; add ++; }
			if (X[idx2] == 0) { X[idx2] = s; add ++; }
		}
	}
	printf("%d", X[0]);
	for (int i = 1; i < N; i ++) {
		printf(" %d", X[i]);
	}
	puts("");
	return 0;
}
