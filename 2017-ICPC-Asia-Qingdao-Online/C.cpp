#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define SIZE 200005

string ss[SIZE];

namespace SA
{
    char s[SIZE];
    int sa[SIZE], t[SIZE], t2[SIZE], c[SIZE], n;
    void build_sa(int m)
    {
        int i, *x = t, *y = t2;
        for (i = 0; i < m; i ++) c[i] = 0;
        for (i = 0; i < n; i ++) c[x[i] = s[i]] ++;
        for (i = 1; i < m; i ++) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; i --) sa[-- c[x[i]]] = i;
        for (int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for (i = n - k; i < n; i ++) y[p ++] = i;
            for (i = 0; i < n; i ++) if (sa[i] >= k) y[p ++] = sa[i] - k;
            for (i = 0; i < m; i ++) c[i] = 0;
            for (i = 0; i < n; i ++) c[x[y[i]]] ++;
            for (i = 0; i < m; i ++) c[i] += c[i - 1];
            for (i = n - 1; i >= 0; i --) sa[-- c[x[y[i]]]] = y[i];
            swap(x, y); p = 1; x[sa[0]] = 0;
            for (i = 1; i < n; i ++) {
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1: p ++;
            }
            if (p >= n) break;
            m = p;
        }
    }
    int m_size;
    int cmp_suffix(const char *pattern, int p)
    {
        return strncmp(pattern, s + sa[p], m_size);
    }
    int find(const char *P)
    {
        m_size = strlen(P);
        if (cmp_suffix(P, 0) < 0) return -1;
        if (cmp_suffix(P, n - 1) > 0) return -1;
        int L = 0, R = n - 1;
        while (R >= L) {
            int M = L + (R - L) / 2;
            int res = cmp_suffix(P, M);
            if (!res) return M;
            if (res < 0) R = M - 1; else L = M + 1;
        }
        return -1;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    int T, N;
    //scanf("%d", &T);
    cin >> T;
    while (T --) {
        //scanf("%d", &N);
        cin >> N;
        int ans = -1;
        int num = 0;
        getline(cin, ss[0]);
        for (int i = 0; i < N; i ++) {
            // gets(buf);
            getline(cin, ss[i]);// = string(buf);
            //cout << ss[i] << endl;
            if (ans == -1) {
                ans = i;
            } else {
                if (ss[ans].size() == ss[i].size() && ss[ans] != ss[i]) {
                    num ++;
                }
                if (ss[ans].size() < ss[i].size()) {
                    ans = i;
                    num = 0;
                }
            }
        }
        //cout << s_ans << endl;
        if (num > 0) {
            END:
            cout << "No" << endl;
        } else {
            SA::n = ss[ans].size();
            for (size_t i = 0; i < ss[ans].size(); i ++) {
                SA::s[i] = ss[ans][i] - 'a';
            }
            SA::build_sa(26);
            for (size_t i = 0; i < ss[ans].size(); i ++) {
                SA::s[i] += 'a';
            }
            SA::s[SA::n] = 0;

            for (int i = 0; i < N; i ++) {
                if (SA::find(ss[i].c_str()) == -1) {
                    goto END;
                }
            }
            cout << ss[ans] << endl;
        }
    }
    return 0;
}
