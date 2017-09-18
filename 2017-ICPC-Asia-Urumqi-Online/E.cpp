#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct quest
{
	quest():n(0), num(0){}
	ll n;
	ll ans;
	int num;
};


bool cmp(const quest& a, const quest& b)
{
	return a.n < b.n;
}

bool cmp2( const quest& a, const quest &b)
{
	return a.num < b.num;
}

bool is_sqr(ll n)
{
	ll k = sqrt(n);
	if (n == k * k)
	{
		return true;
	}
	return false;
}

ll judge(ll k)
{
	if (k == 1)
	{
		return 1;
	}
	ll i = k * k - 1;	
	if (is_sqr(i / 2))
	{
		return i;
		//printf("Case #%d: %lld\n", ce, i);
	}
	i += 2;
	if (is_sqr(i / 2))
	{
		return i - 1;
		//printf("Case #%d: %lld\n", ce, i - 1);
	}
	return -1;
}


vector<quest> q;
int main()
{
	ll t;
	cin >> t;
	q.resize(t);
	for (int i = 0; i < t; i++)
	{
		cin >> q[i].n;
		q[i].num = i + 1;
	}
	
	sort(q.begin(), q.end(), cmp);
	
	size_t i = 0;
	ll k = 1;
	while (i < q.size())
	{
		ll r;
		while (true)
		{
			r = judge(k);
			if (r == -1)
			{
				k += 2;
			}
			else
			{
			//	printf("k = %lld, r = %lld, ok\n", k, r);
				break;
			}
		}
		
		while (i < q.size() && q[i].n <= r)
		{
			//printf("Case #%d: %lld\n", q[i].num, r);
			q[i].ans = r;
		//	printf("q[%d] = %lld\n", i, r);
			i++;
		}
		k += 2;
	}
	
	sort(q.begin(), q.end(), cmp2);
	for (size_t i = 0; i < q.size(); i++)
	{
		printf("Case #%d: %lld\n", q[i].num, q[i].ans);
	}
	return 0;	
}
