 #include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
	freopen("anniversary.in", "r", stdin);
	freopen("anniversary.out", "w", stdout);
	int w, h, x1, x2, y1, y2;
	scanf("%d%d", &w, &h);
	scanf("%d%d", &x1, &y1);
	scanf("%d%d", &x2, &y2);
	if (x1 == x2) {
		printf("%d %d %d %d\n", 0, y1, w, y2);
	} else {
		printf("%d %d %d %d\n", x1, 0, x2, h);
	}
	return 0;
}
