#include <bits/stdc++.h>

using namespace std;

int main()
{
	int X, Y, N;
	scanf("%d%d%d", &X, &Y, &N);
	for (int i = 1; i <= N; i ++) {
		if (i % X == 0 && i % Y == 0) {
			puts("FizzBuzz");
		} else if (i % X == 0) {
			puts("Fizz");
		} else if (i % Y == 0) {
			puts("Buzz");
		} else {
			printf("%d\n", i);
		}
	}
	return 0;
}