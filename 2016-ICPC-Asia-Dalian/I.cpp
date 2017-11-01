#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	const double pi = acos(-1);
	int N, D;
	while (EOF != scanf("%d%d", &N, &D)) {
		double sum = 0;
		for (int i = 0; i < N; i ++) {
			int a; scanf("%d", &a);
			sum += 0.5 * sin(pi * a / 180.0) * D * D;
		}
		printf("%.3f\n", sum);
	}
	return 0;
}