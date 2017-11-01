#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
	int N;
	scanf("%d", &N);
	while (N --) {
		char buf[100];
		scanf("%s", buf);
		int cnt = 0;
		for (int i = 0; buf[i]; i ++) {
			if (buf[i] == 'H') cnt ++;
			if (buf[i] == 'C') cnt += 12;
			if (buf[i] == 'O') cnt += 16;
		}
		printf("%d\n", cnt);
	}
	return 0;
}