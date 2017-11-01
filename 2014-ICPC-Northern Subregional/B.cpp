#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct num
{
	ll data;
	int Rank;
};

bool cmp(const num& a, const num& b)
{
	return a.data > b.data;
}

int main()
{
	freopen("buffcraft.in", "r", stdin);
	freopen("buffcraft.out", "w", stdout);	
	ll b;
	int k, cd, cp;
	vector<num> d;
	vector<num> p;
	vector<ll> dsum;
	vector<ll> psum;

	cin >> b >> k >> cd >> cp;
	k = min(k, cd + cp);
	dsum.resize(cd + 1);
	psum.resize(cp + 1);
	k = min(k, cd + cp);
	d.resize(cd + 1);
	p.resize(cp + 1);
	for (int i = 1; i <= cd; i++)
	{
		cin >> d[i].data;
		
		d[i].Rank = i;
	}
	
	for (int i = 1; i <= cp; i++)
	{
		cin >> p[i].data;
		
		p[i].Rank = i;
	}
	
	//puts("input ok");
	sort(d.begin() + 1, d.end(), cmp);
	sort(p.begin() + 1, p.end(), cmp);
	for (int i = 1; i <= cd; i++)
	{
		dsum[i] = dsum[i - 1] + d[i].data;
	}
	for (int i = 1; i <= cp; i++)
	{
		psum[i] = psum[i - 1] + p[i].data;
	}
	int ii = min(k, cd);
	int jj = k - ii;
	ll ma = (b + dsum[ii]) * (100 + psum[jj]);
	for (int i = ii - 1, j = jj + 1; i >= 0 && j <= cp; i--, j++)
	{
	//	printf("ma = %lld\n");
	//	printf("sum = %lld\n", (b + dsum[ii]) * (100 + psum[jj]));
	//	printf("i =  %d, j = %d\n", i, j);
		if ((b + dsum[i]) * (100 + psum[j]) > ma)
		{
			ma = (b + dsum[i]) * (100 + psum[j]);
			ii = i;
			jj = j;
		}
	}
		
	printf("%d %d\n", ii, jj);
	for (int i = 1; i <= ii; i++)
	{
		printf("%d ", d[i].Rank);
	}
	printf("\n");
	for (int j = 1; j <= jj; j++)
	{
		printf("%d ", p[j].Rank);
	}
	printf("\n");
	return 0;
}
