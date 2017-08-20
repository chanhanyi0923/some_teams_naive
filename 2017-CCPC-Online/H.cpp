#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

#define P 1000000007

struct func
{
	ll a, b, c, d, e, f;

	func(): a(1), b(0), c(0), d(0), e(1), f(0) { }// 相当于无操作

	func(int k)
	{
		if (k == 0)
		{
			a = 1;
			b = 1;
			c = 1;
			d = 0;
			e = 1;
			f = 0;
		}
		// (x + y + 1, y)
		else
		{
			a = 1;
			b = 0;
			c = 0;
			d = 1;
			e = 1;
			f = 1;
		}
		// (x, x + y + 1)
	}

	func(ll a, ll b, ll c, ll d, ll e, ll f): a(a), b(b), c(c), d(d), e(e), f(f) { }

	void modP()
	{
		a %= P;
		b %= P;
		c %= P;
		d %= P;
		e %= P;
		f %= P;
	}

	func operator *(const func& y) const//两函数复合
	{
		// g(f(x))
		//=a2(a1x + b1y + c1) + b2(d1x + e1y + f1) + c2 , d2(a1x + b1y + c1) + e2(d1x + e1y + f1) + f2
		//=(a2a1 + b2d1)x + (a2b1, b2e1)y + a2c1 + b2f1 + c2, (d1a1 + e2d1)x + (d2b1, e2e1)y + d2c1 + e2f1 + f2

		const func& x = *this;
		func ans(
			y.a * x.a + y.b * x.d,
			y.a * x.b + y.b * x.e,
			y.a * x.c + y.b * x.f + y.c,
			y.d * x.a + y.e * x.d,
			y.d * x.b + y.e * x.e,
			y.d * x.c + y.e * x.f + y.f
		);

		ans.modP();
		return ans;
	}

	func swap() const//翻转 01 后 (ax + by + c, dx + ey + f) 变成
	//			 (dy + ex + f, by + ax + c)
	{
		func ret({e, d, f, b, a ,c});
		return ret;
	}
};

struct _SegTree
{
	typedef func node;
	typedef int tag;

	vector<node> tree;
	vector<tag> lazy;
	vector<int> height;
	int M;

	void build(vector<node>& list)
	{
		for (M = 1; M < list.size() + 2; M <<= 1) {}
		tree.clear();
		lazy.clear();
		height.clear();

		tree.resize(2 * M, node());
		lazy.resize(2 * M, 0);
		height.resize(2 * M, 0);

		for (int i = 0; i < list.size(); i++)
		{
			tree[M + i + 1] = list[i];
		}

		for (int i = M - 1; i >= 1; i--)
		{
			tree[i] = tree[i + i] * tree[i + i + 1];
			height[i] = height[i + i] + 1;
		}
	}

	void up(int x)
	{
		while (x > 1)
		{
			up_tag(x >>= 1);
		}
	}

	void down(int x)
	{
		for (int i = height[1]; i > 0; i--)
		{
			down_tag(x >> i);
		}
	}

	void change(int l, int r)
	{
		int L = l + M - 1;
		int R = r + M + 1;

		down(L);
		down(R);

		for (int s = L, t = R; s ^ t ^ 1; s >>= 1 , t >>= 1)
		{
			if (~s & 1)
				put_tag(s ^ 1);
			if (t & 1)
				put_tag(t ^ 1);
		}

		up(L);
		up(R);
	}

	ll query(int l, int r)
	{
		int L = l + M - 1;
		int R = r + M + 1;

		down(L);
		down(R);

		vector<int> ql;
		vector<int> qr;
		for (int s = L, t = R; s ^ t ^ 1; s >>= 1 , t >>= 1)
		{
			if (~s & 1)
				ql.push_back(s ^ 1);
			if (t & 1)
				qr.push_back(t ^ 1);
		}

		ql.insert(ql.end(), qr.rbegin(), qr.rend());

		//ql 是所有需要的区间从左到右排好序的列表
		//由于本题的特殊性，需要从左往右访问各区间

		return calc(ql);
	}

	//----------------------以上为线段树部分，实现不依赖于具体题目-----------------

	ll calc(vector<int>& q)
	{
		func ans;
		for (int i = 0; i < q.size(); i++)
		{
			int t = q[i];
			ans = ans * tree[t];
		}

		return (ans.c + ans.f) % P;
	}


	void put_tag(int x)
	{
		lazy[x] ^= 1;
		//lazy[x] 表示，当前标记下推到此处，即这整个区间已翻转
		//若需要继续下推或者重新反转回来，则标记清零
		tree[x] = tree[x].swap();
	}

	void up_tag(int x)
	{
		tree[x] = tree[x + x] * tree[x + x + 1];
	}

	void down_tag(int x)
	{
		if (lazy[x])
		{
			lazy[x] = 0;
			put_tag(x + x);
			put_tag(x + x + 1);
		}
	}
};

_SegTree segTree;

int main()
{
#ifdef __LOCAL__
	freopen("input", "r", stdin);
#endif

	int t;
	cin >> t;
	while (t--)
	{
		int n, q;
		cin >> n >> q;
		vector<func> list(n);
		getchar();
		for (int i = 0; i < n; i++)
		{
			char c = getchar();
			list[i] = func(c - '0');
		}

		segTree.build(list);
		int type;
		for (int i = 0; i < q; i++)
		{
			int l, r;
			cin >> type >> l >> r;
			if (type == 1)
			{
				segTree.change(l, r);
			}
			else
			{
				cout << segTree.query(l, r) << endl;
			}
		}
	}
}
