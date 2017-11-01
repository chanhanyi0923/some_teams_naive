#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int lcm(int a, int b)
{
	return a * b / __gcd(a, b);
}
int main()
{
	//printf("%d\n", __gcd(308, 490));
	int a, b;
	while (EOF != scanf("%d%d", &a, &b))
	{
		bool flag = false;
		for (int g = 1; g * g <= a; g ++) {
			if (a % g == 0) {
				int g2 = a / g;
				//
				ll mul = b * g;
				int tmp = floor(sqrt(1ll * a * a - 4 * mul) + 1e-4);
				int x = (a + tmp) / 2;
				int y = (a - tmp) / 2;
				//
				//printf("%d %d\n", x, y);
				if (x > 0 && y > 0 && (x + y == a) && (lcm(x, y) == b)) {
					flag = true;
					if (x > y) swap(x, y);
					printf("%d %d\n", x, y);
					break;
				}
				
				
				mul = b * g2;
				tmp = floor(sqrt(1ll * a * a - 4 * mul) + 1e-4);
				x = (a + tmp) / 2;
				y = (a - tmp) / 2;
				//
				//printf("%d %d\n", x, y);
				if (x > 0 && y > 0 && (x + y == a) && (lcm(x, y) == b)) {
					flag = true;
					if (x > y) swap(x, y);
					printf("%d %d\n", x, y);
					break;
				}

			}
		}
		/*
		for (int i = 1; i < a; i++)
		{
			int j = a - i;
			if (lcm(i, j) == b)
			{
				flag = true;
				cout << i << " " << j << endl;
				break;
			}
		}
		*/
		if (!flag)
		{
			puts("No Solution");
		}
	}	
}