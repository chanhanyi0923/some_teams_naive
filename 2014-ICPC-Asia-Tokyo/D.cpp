#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int p[100], h[100];
double x[100];

int main()
{
	const double g = 1.0;
	int d, n, b;
	scanf("%d%d%d", &d, &n, &b);
	for (int i = 0; i < n; i ++) {
		scanf("%d%d", p + i, h + i);
	}
	double f_ans = 1e18;
	for (int B = 0; B <= b; B ++) {
		double len = 1.0 * d / (B + 1);
		for (int i = 0; i < n; i ++) {
			double k = floor(1.0 * p[i] / len);
			x[i] = p[i] - k * len;
		}
		//
		double big = -1;
		for (int i = 0; i < n; i ++) {
			double A = h[i] / (x[i] * (x[i] - len));
			double max_h = -1.0 * A * len * len / 4;
			//printf("%f\n", max_h);
			big = max(max_h, big);
		}
		//printf("h = %f\n", big);
		double vx_sq = 1.0 * len * len * g / (8 * big);
		double vy_sq = 1.0 * 2 * big * g;
		//printf("%f %f\n", vx_sq, vy_sq);
		if (vy_sq < vx_sq) {
			f_ans = min(f_ans, g * len);
		} else {
			double ans = vx_sq + vy_sq;
			f_ans = min(f_ans, ans);
		}
	}
	printf("%.15f\n", sqrt(f_ans));
	//printf("%.15f\n", sqrt(f_ans));
	return 0;
}
