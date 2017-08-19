#include <bits/stdc++.h>

using namespace std;

int main()
{
	int N;
	while (EOF != scanf("%d", &N) && N > 0) {
		if (N <= 1000000) {
			printf("%d\n", N);
		} else if (N <= 5000000) {
			printf("%d\n", N * 9 / 10);
		} else if (N > 5000000) {
			printf("%d\n", N * 8 / 10);
		}
	}
	return 0;
}
