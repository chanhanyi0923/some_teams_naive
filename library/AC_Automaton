struct Trie
{
  static Trie mem[SIZE], *pmem;
  Trie *ch[CHAR_SIZE], *next[CHAR_SIZE];
  Trie *fail, *n_fail;
  bool end, all_end;
  Trie()
  {
    all_end = end = false;
    fail = n_fail = NULL;
		for (int i = 0; i < CHAR_SIZE; i ++) {
			ch[i] = next[i] = NULL;
		}
  }
  void insert(char *s)
  {
    if (*s) {
      int idx = getIdx(*s);
      if (ch[idx] == NULL) next[idx] = ch[idx] = new(pmem ++) Trie;
      ch[idx]->insert(s + 1);
    } else {
      all_end = end = true;
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
      for (int i = 0; i < CHAR_SIZE; i ++) {
        if (t->ch[i] == NULL) continue;
        t->ch[i]->fail = getFail(t->fail, i);
        Q.push(t->ch[i]);
      }
    }
  }
  inline Trie *nextFail(Trie *t) { return t->n_fail ? t->n_fail : this; }
  void build_next()
  {
    queue<Trie*> Q;
		for (int i = 0; i < CHAR_SIZE; i ++) {
			if (next[i]) Q.push(next[i]);
		}
    while (!Q.empty()) {
      Trie *t = Q.front(); Q.pop();
      if (t->n_fail && t->n_fail->all_end) {
        t->all_end = true;
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
