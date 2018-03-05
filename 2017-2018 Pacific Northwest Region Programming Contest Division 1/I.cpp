#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pii;
typedef pair<int, pii> pip;

#define SIZE 2005

pip O1[SIZE], O2[SIZE];
ll num[SIZE * 2];
int new_num[SIZE * 2];

class treap
{
	public:

	treap *lc, *rc;
	int size, pri, data;

	treap () {}
	treap (ll d) : lc(NULL), rc(NULL), size(1), pri(rand()), data(d) {}

	friend int getSize(treap *t)
	{
		return t ? t->size : 0;
	}

	inline void up()
	{
		size = 1 + getSize(lc) + getSize(rc);
	}

	inline void down() {}
};

void split(treap *t, int k, treap *&a, treap *&b)
{
	if (t == NULL) {
		a = b = NULL;
	} else {
		t->down();
		if (getSize(t->lc) + 1 <= k) {
			a = t;
			split(t->rc, k - getSize(t->lc) - 1, a->rc, b);
			a->up();
		} else {
			b = t;
			split(t->lc, k, a, b->lc);
			b->up();
		}
	}
}

treap *merge(treap *a, treap *b)
{
	if (a && b) {
		treap *t;
		if (a->pri < b->pri) {
			a->down();
			t = a;
			t->rc = merge(a->rc, b);
		} else {
			b->down();
			t = b;
			t->lc = merge(a, b->lc);
		}
		t->up();
		return t;
	} else {
		return a ? a : b;
	}
}

int a_arr[SIZE * SIZE + 10];
int b_arr[SIZE * SIZE + 10];

int print(treap *t, int k, int *arr)
{
	if (t == NULL) return k;
	k = print(t->lc, k, arr);
	//if (k < 100) printf("%d %d\n", k, t->data);
	arr[k] = t->data;
	k += 1;
	k = print(t->rc, k, arr);
	return k;
	/*
	print(t->lc, 0, arr);
	printf("%d\n", t->data);
	print(t->rc, 0, arr);
	*/
}
// rope<int> a, b;

int main()
{
	char buf[100];
	int sz1 = 0, sz2 = 0, sz3 = 0;

	num[sz3 ++] = 0; new_num[0] = 0;

	while (EOF != scanf("%s", buf) && buf[0] != 'E') {
		ll a; char c[10];
		if (buf[0] == 'D') {
			scanf("%lld", &a);
			O1[sz1 ++] = pip(0, pii(a, 0));
		} else {
			scanf("%lld%s", &a, c);
			O1[sz1 ++] = pip(1, pii(a, c[0]));
		}
		num[sz3 ++] = a;
	}

	while (EOF != scanf("%s", buf) && buf[0] != 'E') {
		ll a; char c[10];
		if (buf[0] == 'D') {
			scanf("%lld", &a);
			O2[sz2 ++] = pip(0, pii(a, 0));
		} else {
			scanf("%lld%s", &a, c);
			O2[sz2 ++] = pip(1, pii(a, c[0]));
		}
		num[sz3 ++] = a;
	}

	sort(num, num + sz3);
	for (int i = 1; i < sz3; i ++) {
		int add = min(1ll * SIZE, (num[i] - num[i - 1]));
		new_num[i] = new_num[i - 1] + add;
	}
/*
	for (int i = 0; i < sz3; i ++) {
		printf("%lld %d\n", num[i], new_num[i]);
	}
*/
	treap *a = NULL, *b = NULL;
	for (int i = 0; i < SIZE + new_num[sz3 - 1]; i ++) {
//		a.push_back(i);
//		b.push_back(i);
		a = merge(a, new treap(i));
		b = merge(b, new treap(i));
	}

	for (int i = 0; i < sz1; i ++) {
		int pos = (int)(lower_bound(num, num + sz3, O1[i].second.first) - num);
		int p = new_num[pos];
		if (O1[i].first) {
			treap *l, *r;
			split(a, p, l, r);
			a = merge(l, merge(new treap(O1[i].second.second), r));
			//a.insert(p, O1[i].second.second);
			//printf("I %d %c\n", p, O1[i].second.second);
		} else {
			treap *l, *m, *r;
			split(a, p, l, m);
			split(m, 1, m, r);
			a = merge(l, r);
			//a.erase(p, 1);
			//printf("D %d\n", p);
		}
	}

	for (int i = 0; i < sz2; i ++) {
		int pos = (int)(lower_bound(num, num + sz3, O2[i].second.first) - num);
		int p = new_num[pos];
		if (O2[i].first) {
			treap *l, *r;
			split(b, p, l, r);
			b = merge(l, merge(new treap(O2[i].second.second), r));
		} else {
			treap *l, *m, *r;
			split(b, p, l, m);
			split(m, 1, m, r);
			b = merge(l, r);
		}
	}

	if (getSize(a) != getSize(b)) { puts("1"); return 0; }
	print(a, 0, a_arr); print(b, 0, b_arr);
	bool fail = false;
	for (int i = 0; i < getSize(a); i ++) {
		fail = fail || (a_arr[i] != b_arr[i]);
		if (fail) break;
	}
	puts(fail ? "1" : "0");
	return 0;
}