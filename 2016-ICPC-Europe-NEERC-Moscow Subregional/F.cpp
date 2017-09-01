#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;
vector<pii> V1, V2;
char str[100005];

int _idx[200];
int rev_idx[200];

void build_idx()
{
/*
	' ' -> 0
	'0' -> 1
	'1' -> 2
	'9' -> 10
	'A' -> 11 A 0
	'Z' -> 36 Z 25
*/
	_idx[' '] = 0; rev_idx[0] = ' ';
	for (int i = 0; i < 10; i ++) { _idx['0' + i] = i + 1;  rev_idx[i + 1]  = '0' + i; }
	for (int i = 0; i < 26; i ++) { _idx['A' + i] = i + 11; rev_idx[i + 11] = 'A' + i; }
	for (int i = 0; i < 26; i ++) { _idx['a' + i] = i + 37; rev_idx[i + 37] = 'a' + i; }
}

inline int idx(int c) { return _idx[c]; }
inline int C(int x) { return rev_idx[x]; }

bool app1[200], app2[200];

int main()
{
	build_idx();
	fgets(str, sizeof(str), stdin);

	for (int i = 0; i < 10; i ++) app2[idx('0' + i)] = true;
	for (int i = 0; i < 26; i ++) app2[idx('a' + i)] = app2[idx('A' + i)] = true;
	app2[idx(' ')] = true;

	for (int i = 0; str[i] && str[i] != '\n'; i ++) {
		//printf("%d ", idx(str[i]));
		app1[idx(str[i])] = true;
		app2[idx(str[i])] = false;
	}
/*
	for (int i = 0; i < 65; i ++) {
		printf("%d %c %d\n", i, C(i), app2[i]);
	}
*/
	int l = 10000, r = -1;
	for (int i = 0; i < 200; i ++) {
		if (app1[i]) {
			l = min(l, i); r = max(r, i);
		} else {
			if (l <= r) {
				V1.push_back(pii(l, r));
			}
			l = 10000; r = -1;
		}
	}
	l = 10000; r = -1;
	for (int i = 0; i < 200; i ++) {
		if (app2[i]) {
			l = min(l, i); r = max(r, i);
		} else {
			if (l <= r) {
				V2.push_back(pii(l, r));
			}
			l = 10000; r = -1;
		}
	}

	int len1 = 0, len2 = 1;
	for (size_t i = 0; i < V1.size(); i ++) {
		len1 += min(3, V1[i].se - V1[i].fi + 1);
	}
	for (size_t i = 0; i < V2.size(); i ++) {
		len2 += min(3, V2[i].se - V2[i].fi + 1);
	}
	if (len2 == 1) {
		puts("%[^!]");
		return 0;
	}
	printf("%%[");
	//printf("!  %c   !\n", C(V1[0].fi));
	//printf("%d %d\n", len1, len2);
	if (len1 < len2 || (len1 == len2 && C(V1[0].fi) <= 'a')) {
		for (size_t i = 0; i < V1.size(); i ++) {
			int _len = V1[i].se - V1[i].fi + 1;
			if (_len == 1) {
				printf("%c", C(V1[i].fi));
			} else if (_len == 2) {
				printf("%c%c", C(V1[i].fi), C(V1[i].se));
			} else {
				int cc = 1000000;
				if (C(V1[i].fi) == ' ') cc = ' ';
				else if (C(V1[i].fi) == '0') cc = '!';
				else if (C(V1[i].fi) == 'A') cc = ':';
				else if (C(V1[i].fi) == 'a') cc = '[';
				else cc = C(V1[i].fi);
				printf("%c-%c", cc, C(V1[i].se));
			}
			// printf("%c %c\n", C(V1[i].fi), C(V1[i].se));
		}
		//
	} else {
		putchar('^');
		for (size_t i = 0; i < V2.size(); i ++) {
			int _len = V2[i].se - V2[i].fi + 1;
			if (_len == 1) {
				printf("%c", C(V2[i].fi));
			} else if (_len == 2) {
				printf("%c%c", C(V2[i].fi), C(V2[i].se));
			} else {
				int cc = 1000000;
				if (C(V2[i].fi) == ' ') cc = ' ';
				else if (C(V2[i].fi) == '0') cc = '!';
				else if (C(V2[i].fi) == 'A') cc = ':';
				else if (C(V2[i].fi) == 'a') cc = '[';
				else cc = C(V2[i].fi);
				printf("%c-%c", cc, C(V2[i].se));
			}
			//printf("%c %c\n", C(V2[i].fi), C(V2[i].se));
		}
		//
	}
	printf("]\n");
	return 0;
}
