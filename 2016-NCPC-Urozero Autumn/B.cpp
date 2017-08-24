#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define fi first
#define se second

#define CHAR_SIZE 26
#define INF (1 << 29)

inline int getIdx(char c) { return c - 'a'; }

struct Trie
{
    Trie *ch[CHAR_SIZE]; Trie *back, *tab;
    bool end; int dis;
    Trie()
    {
        for (int i = 0; i < CHAR_SIZE; i ++) ch[i] = NULL;
        back = tab = NULL; end = false; dis = INF;
    }
    Trie *insert(const char *s)
    {
        Trie *ptr = this;
        if (*s) {
            int i = getIdx(*s);
            if (ch[i] == NULL) {
                ch[i] = new Trie;
                ch[i]->back = this;
            }
            ptr = ch[i]->insert(s + 1);
        } else {
            end = true;
        }
        tab = back ? (tab ? tab : ptr) : NULL;
        return ptr;
    }
    void build()
    {
        queue< pair<int, Trie*> > Q;
        this->dis = 0; Q.push(make_pair(0, this));
        while (!Q.empty()) {
            Trie *t = Q.front().se; int d = Q.front().fi; Q.pop();
            for (int i = 0; i < CHAR_SIZE; i ++) {
                if (t->ch[i] && d + 1 < t->ch[i]->dis) {
                    t->ch[i]->dis = d + 1;
                    Q.push(make_pair(d + 1, t->ch[i]));
                }
            }
            if (t->back && d + 1 < t->back->dis) {
                t->back->dis = d + 1;
                Q.push(make_pair(d + 1, t->back));
            }
            if (t->tab && d + 1 < t->tab->dis) {
                t->tab->dis = d + 1;
                Q.push(make_pair(d + 1, t->tab));
            }
        }
    }
};

string S;

int main()
{
    Trie *T = new Trie;
    int N, M;
    cin >> N >> M;
    getline(cin, S);
    for (int _ = 0; _ < N; _ ++) {
        getline(cin, S);
        T->insert(S.c_str());
    }
    T->build();
    for (int _ = 0; _ < M; _ ++) {
        getline(cin, S);
        Trie *ptr = T;
        int ans = S.size();
        for (int i = 0; i < S.size(); i ++) {
            ptr = ptr->ch[getIdx(S[i])];
            if (ptr == NULL) break;
            ans = min(ans, ptr->dis + (int)S.size() - 1 - i);
        }
        cout << ans << endl;
    }
    return 0;
}
