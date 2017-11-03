#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define EPS 1e-7
#define SIZE 105
#define CHAR_SIZE 6

struct Trie
{
	static Trie mem[SIZE], *pmem;
	Trie *ch[CHAR_SIZE], *next[SIZE];
	Trie *fail, *n_fail;
	bool end, all_end;
	int end_num;
	Trie()
	{
		all_end = end = false;
		fail = n_fail = NULL;
		for (int i = 0; i < CHAR_SIZE; i ++) {
			ch[i] = next[i] = NULL;
		}
		end_num = -1;
	}
	void insert(int a[], int n, int ed_num)
	{
		if (n > 0) {
			int idx = a[0] - 1;
			if (ch[idx] == NULL) next[idx] = ch[idx] = new(pmem ++) Trie;
			ch[idx]->insert(a + 1, n - 1, ed_num);
		} else {
			all_end = end = true;
			end_num = ed_num;
		}
	}
	Trie *getFail(Trie *ptr, int idx)
	{
		while (ptr && ptr->ch[idx] == NULL) ptr = ptr->fail;
		return ptr ? ptr->ch[idx] : this;
	}
	inline Trie *nextFail(Trie *t) { return t->n_fail ? t->n_fail : this; }
	void build_next()
	{
		queue<Trie*> Q;
		for (int i = 0; i < CHAR_SIZE; i ++) {
			if (next[i]) Q.push(next[i]);
			else next[i] = this;
		}
		while (!Q.empty()) {
			Trie *t = Q.front(); Q.pop();
			if (t->n_fail && t->n_fail->all_end) {
				t->all_end = true;
				t->end_num = t->n_fail->end_num;
			}
			for (int i = 0; i < CHAR_SIZE; i ++) {
				if (t->next[i]) {
					Q.push(t->next[i]);
					t->next[i]->n_fail = nextFail(t)->next[i];
				} else {
					t->next[i] = nextFail(t)->next[i];
				}
			}
		}
	}
} Trie::mem[SIZE], *Trie::pmem;

struct Gauss
{
	typedef double e;
	e a[SIZE][SIZE], b[SIZE], c[SIZE];
	bool solve(int n) // return: if there is an unique solution
	{
		int i, j, k, row, col, idx[SIZE];
		double maxp, t;
		for (i = 0; i < n; i ++) {
			idx[i] = i;
		}
		for (k = 0; k < n; k ++) {
			for (maxp = 0, i = k; i < n; i ++) {
				for (j = k; j < n; j ++) {
					if (fabs(a[i][j]) > fabs(maxp)) {
						maxp = a[row = i][col = j];
					}
				}
			}
			if (fabs(maxp) < EPS) {
				return false;
			}
			if (col != k) {
				for (i = 0; i < n; i ++) {
					swap(a[i][col], a[i][k]);
				}
				swap(idx[col], idx[k]);
			}
			if (row != k) {
				for (j = k; j < n; j ++) {
					swap(a[k][j], a[row][j]);
				}
				swap(b[k], b[row]);
			}
			for (j = k + 1; j < n; j ++) {
				a[k][j] /= maxp;
				for (i = k + 1; i < n; i ++) {
					a[i][j] -= a[i][k] * a[k][j];
				}
			}
			b[k] /= maxp;
			for (i = k + 1; i < n; i ++) {
				b[i] -= b[k] * a[i][k];
			}
		}
		for (i = n - 1; i >= 0; i --) {
			for (j = i + 1; j < n; j ++) {
				b[i] -= a[i][j] * b[j];
			}
		}
		for (k = 0; k < n; k ++) {
			a[0][idx[k]] = b[k];
		}
		for (k = 0; k < n; k ++) {
			b[k] = a[0][k];
			c[k] = b[k];
		}
		return true;
	}
};

Gauss G;

int main()
{
	const double f16 = 1.0 / 6;
	int TTT;
	scanf("%d", &TTT);
	while (TTT --) {
		Trie::pmem = Trie::mem;
		Trie *root = new(Trie::pmem ++) Trie;

		int N, L, sz = 0;
		scanf("%d%d", &N, &L);
		for (int i = 0; i < N; i ++) {
			int a[20];
			for (int j = 0; j < L; j ++) {
				scanf("%d", a + j);
			}
			root->insert(a, L, i);
		}
		sz = (int)(Trie::pmem - Trie::mem);
		root->build_next();
		for (int i = 0; i < sz; i ++) {
		    for (int j = 0; j < sz; j ++) {
				G.a[i][j] = 0;
			}
			G.b[i] = 0;
			G.a[i][i] = -1;
		}
		G.b[0] = -1;

		int idx[20];
		for (int j = 0; j < sz; j ++) {
			if ((Trie::mem + j)->all_end) {
				int qqq = (Trie::mem + j)->end_num;
				assert(qqq >= 0 && qqq <= N - 1);
				idx[(Trie::mem + j)->end_num] = j;
				continue;
			}
			for (int k = 0; k < 6; k ++) {
				Trie *ptr = (Trie::mem + j)->next[k];
				int nxt = (int)(ptr - Trie::mem);
				G.a[nxt][j] += f16;
			}
		}
		G.solve(sz);
		double ans[20];
		double sum = 0;
		for (int i = 0; i < N; i ++) {
			ans[i] = fabs(G.c[idx[i]]);
			sum += ans[i];
		}

		printf("%.6f", ans[0] / sum);
		for (int i = 1; i < N; i ++) {
			printf(" %.6f", ans[i] / sum);
		}
		puts("");
	}
	return 0;
}
