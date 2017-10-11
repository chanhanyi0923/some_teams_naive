namespace SAM
{
  struct Node
  {
    int val;
    int ch[CHAR_SIZE], fa;
    Node()
    {
      for (int i = 0; i < CHAR_SIZE; i ++) ch[i] = -1;
      val = 0; fa = -1;
    }
  } pool[SIZE * 2];
  int cnt, root, last;
  void init()
  {
    if (cnt) {
      for (int i = 0; i < cnt; i ++) {
        pool[i] = Node();
      }
    }
    cnt = 1;
    root = 0;
    last = root;
  }
  void add(int c)
  {
    int p = last, np = cnt ++;
    last = np;
    pool[np].val = pool[p].val + 1;
    for (; p != -1 && pool[p].ch[c] == -1; p = pool[p].fa) {
      pool[p].ch[c] = np;
    }
    if (p == -1) {
      pool[np].fa = root;
    } else {
      int q = pool[p].ch[c];
      if (pool[p].val + 1 == pool[q].val) {
        pool[np].fa = q;
      } else {
        int nq = cnt ++;
        pool[nq] = pool[q];
        pool[nq].val = pool[p].val + 1;
        pool[q].fa = nq;
        pool[np].fa = nq;
        for (; p != -1 && pool[p].ch[c] == q; p = pool[p].fa) {
          pool[p].ch[c] = nq;
        }
      }
    }
  }
}
