#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int mat[10][10];

int f(int x)
{
	int a = (x / 1000) % 10, b = (x / 100) % 10, c = (x / 10) % 10, d = x % 10;
	int k = mat[0][a]; k = mat[k][b]; k = mat[k][c]; k = mat[k][d];
	return k;
}

int ch(int x)
{
	int a = (x / 10000) % 10, b = (x / 1000) % 10, c = (x / 100) % 10, d = (x / 10) % 10, e = x % 10;
	int k = mat[0][a]; k = mat[k][b]; k = mat[k][c]; k = mat[k][d]; k = mat[k][e];
	return k;
}

int toInt(char *s)
{
	int x = 0;
	for (int i = 0; s[i]; i ++) {
		x = x * 10 + s[i] - '0';
	}
	return x;
}

bool CC(int x)
{
	// printf("%d\n", x);
	//if (ch(x) == 0) printf("\n!! %d\n", x);
	//return ch(x) == 0;
	if (ch(x) != 0) return false;
	//printf("! %d\n", x);
	return true;
	/*
	int y = x / 10;
	return y * 10 + f(y) != x;
	*/
}

bool err(int x)
{
	//printf("%d\n", x);
	char buf[15]; sprintf(buf, "%05d", x);
	// if (buf[0] == '0') printf("%s\n", buf);
	for (int i = 0; i < 5; i ++) {
		for (int d = 0; d < 10; d ++) {
			if (buf[i] == d + '0') continue;
			int tmp = buf[i];
			buf[i] = '0' + d;
			if (CC(toInt(buf))) return true;
			buf[i] = tmp;
		}
	}
	for (int i = 1; i < 5; i ++) {
		if (buf[i] == buf[i - 1]) continue;
		swap(buf[i], buf[i - 1]);
		if (CC(toInt(buf))) return true;
		swap(buf[i], buf[i - 1]);
	}
	return false;
}

int main()
{
	for (int i = 0; i < 10; i ++) {
		for (int j = 0; j < 10; j ++) {
			scanf("%d", &mat[i][j]);
		}
	}
	//printf("%d\n", err(9999 * 10 + f(9999))); return 0;
	int ans = 0;
	for (int i = 0; i < 10000; i ++) {
		// int c = ch(i * 10 + x);
		// if (c == 0) cnt ++;
		if (err(i * 10 + f(i))) {
			//printf("%d\n", i);
			ans ++;
		}
	}
	//printf("!! %d\n", cnt);
	printf("%d\n", ans);
	return 0;
}
