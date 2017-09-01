#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define SIZE 2505
#define MOD 998244353ll

struct Trie
{
	static Trie mem[SIZE], *pmem;
	Trie *ch[2], *fail; int tag; int sp_tag;
	Trie *next[2]; int next_tag[2]; int next_sp_tag[2];
	Trie()
	{
		fail = NULL; tag = 0; sp_tag = 0;
		ch[0] = ch[1] = next[0] = next[1] = NULL;
		next_tag[0] = next_tag[1] = next_sp_tag[0] = next_sp_tag[1] = 0;
	}
	void insert(char *s, bool sp, int val)
	{
		if (*s) {
			int idx = *s - '0';
			if (ch[idx] == NULL) ch[idx] = new(pmem ++) Trie;
			ch[idx]->insert(s + 1, sp, val);
		} else {
			if (sp) sp_tag |= val;
			else tag |= val;
		}
	}
	Trie *getFail(Trie *ptr, int idx)
	{
		while (ptr && ptr->ch[idx] == NULL) ptr = ptr->fail;
		return ptr ? ptr->ch[idx] : this;
	}
	void build()
	{
		queue<Trie*> Q;
		Q.push(this);
		while (!Q.empty()) {
			Trie *t = Q.front(); Q.pop();
			for (int i = 0; i < 2; i ++) {
				if (t->ch[i] == NULL) continue;
				t->ch[i]->fail = getFail(t->fail, i);
				Q.push(t->ch[i]);
			}
		}
	}
	void build_next()
	{
		queue<Trie*> Q;
		Q.push(this);
		while (!Q.empty()) {
			Trie *t = Q.front(); Q.pop();
			for (int k = 0; k < 2; k ++) {
				Trie *ptr = t;
				t->next[k] = ptr = ptr->ch[k] ? ptr->ch[k] : getFail(ptr, k);
				while (ptr) {
					t->next_tag[k] |= ptr->tag;
					t->next_sp_tag[k] |= ptr->sp_tag;
                    ptr = ptr->fail;
				}
				if (t->ch[k]) Q.push(t->ch[k]);
			}
		}
	}
} Trie::mem[SIZE], *Trie::pmem;

ll dp[2][SIZE][1 << 6];

int main()
{
	int T, N, L;
	scanf("%d", &T);
	while (T --) {
		Trie::pmem = Trie::mem;
		scanf("%d%d", &N, &L);
		Trie *AC = new(Trie::pmem++) Trie;
		for (int _ = 0; _ < N; _ ++) {
			char buf[30], str[30], tmp[30];
			scanf("%s", buf);
			int len = strlen(buf);
            AC->insert(buf, false, 1 << _);
			for (int i = 0; i < len; i ++) {
				bool fail = false;
				for (int j = 0; j + i < len && i - j - 1 > -1; j ++) {
					if (buf[i + j] - '0' != 1 - (buf[i - j - 1] - '0')) {
                        fail = true; break;
					}
				}
				if (fail) continue;
				if (i < len - i) {
					int j;
					for (j = 0; j + i < len; j ++) str[j] = buf[i + j];
					int len2 = j; str[j] = 0;
					for (j = 0; j < len2; j ++) tmp[j] = 1 - (str[j] - '0') + '0';
					for (j = 0; j < len2; j ++) str[j] = tmp[len2 - j - 1];
				} else {
					int j;
					for (j = 0; j < i; j ++) str[j] = buf[j];
					str[j] = 0;
				}
				AC->insert(str, i != 0, 1 << _);
            }
		}
		AC->build();
		AC->build_next();
		int sz = (int)(Trie::pmem - Trie::mem);

		for (int i = 0; i < 2; i ++) {
			for (int j = 0; j < sz; j ++) {
			    for (int k = 0; k < (1 << N); k ++) {
				    dp[i][j][k] = 0;
				}
			}
		}
		dp[0][0][0] = 1;
		for (int i = 0; i < L; i ++) {
			for (int j = 0; j < sz; j ++) {
			    for (int k = 0; k < (1 << N); k ++) {
				    for (int nxt = 0; nxt < 2; nxt ++) {
					    Trie *ptr = Trie::mem + j;
					    int next = (int)(ptr->next[nxt] - Trie::mem);
                        int nxt_tag = k;
                        nxt_tag |= ptr->next_tag[nxt];
                        if (i == L - 1) nxt_tag |= ptr->next_sp_tag[nxt];
			            dp[(i + 1) & 1][next][nxt_tag] += dp[i & 1][j][k] % MOD;
						dp[(i + 1) & 1][next][nxt_tag] %= MOD;
				    }
                    dp[i & 1][j][k] = 0;
			    }
			}
		}
		ll ans = 0;
		for (int i = 0; i < sz; i ++) {
            ans += dp[L & 1][i][(1 << N) - 1];
			ans %= MOD;
		}
		printf("%lld\n", ans % MOD);
	}
	return 0;
}
