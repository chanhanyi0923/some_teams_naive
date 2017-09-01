#include <cstdio>

using namespace std;
typedef long long ll;

#define SIZE 100005

int a[2 * SIZE];
int num[2 * SIZE];
bool tp[2 * SIZE];
double ans[2 * SIZE];

int main()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < 2 * N; i ++) {
		char buf[10]; scanf("%s", buf);
		scanf("%d", a + i);
		if (buf[0] == '+') {
			tp[i] = false;
			num[i + 1] = num[i] + 1;
		} else {
			tp[i] = true;
			num[i + 1] = num[i] - 1;
		}
	}
	// double p = 1;
	double x = 0;
	int cnt = N;
	for (int i = 2 * N - 1; i > -1; i --) {
		if (tp[i]) {
			//printf("%d\n", num[i]);
			//ans[-- cnt] = 
			x = 1.0 * a[i] / num[i] + 1.0 * x * (num[i] - 1) / num[i];
		} else {
			ans[-- cnt] = x - a[i];
		}
	}
	for (int i = 0; i < N; i ++) {
		printf("%.15f\n", ans[i]);
	}
	return 0;
}
