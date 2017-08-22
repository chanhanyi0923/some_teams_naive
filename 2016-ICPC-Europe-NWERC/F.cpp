#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
vector<pii> a1, a2;
int n;
bool comp(pii a, pii b)
{
	return a.first < b.first;
}

bool comp2(pii a, pii b)
{
	return a.second < b.second;
}

int delOdd(vector<pii> &a1)
{
	int ma = 0;
	vector<pii> tmp;
	tmp.resize(n);
	for (int i = 0; i < n; i++)
	{
		tmp[i] = a1[i];
	}
	
	sort(tmp.begin(), tmp.end(), comp);
	
	map<int, int> num;
	
	for (int i = 0; i < n; i++)
	{
		int now = tmp[i].first;
		if (!num.count(now))
		{
			num[now] = 1;
		}
		else
		{
			num[now]++;
		}
	}
	
	a1.clear();
	for (int i = 0; i < n; i++)
	{
		int now = tmp[i].first;
		if (num[now] % 2 == 1)
		{
			ma = max(now, ma);
		}
		else
		{
			a1.push_back(tmp[i]);
		}
	}
	
	sort(a1.begin(), a1.end(), comp2);
	return ma;
}

bool judge(vector<pii> &a, int k)
{
	int num = 0;
	int prev = -1;
	for (int i = 0; i < n; i++)
	{
		if (a[i].first <= k)
			continue;
		if (prev < 0 || prev == a[i].first)
		{
			prev = a[i].first;
			num++;
		}
		else
		{
			if (num % 2 != 0)
			{
				return false;
			}
			prev = a[i].first;
			num++;
		}
	}
	return true;
}

int main()
{
	cin >> n;
	a1.resize(n);
	a2.resize(n);
	
	int mi = 0;
	int ma = 0;
	for (int i = 0; i < n; i++)	
	{
		cin >> a1[i].first;
		ma = max(ma, a1[i].first);
		a1[i].second = i;
	}
	
	for (int i = 0; i < n; i++)
	{
		cin >> a2[i].first;
		ma = max(ma, a2[i].first);
		a2[i].second = i;
	}
	

	mi = max(mi, delOdd(a1));
	
/*	printf("a1:\n");
	for (int i = 0; i < a1.size(); i++)
	{
		printf("%d ", a1[i].first);
	}
	printf("\n");
	*/
	mi = max(mi, delOdd(a2));
/*
	printf("a2:\n");
	for (int i = 0; i < a2.size(); i++)
	{
		printf("%d ", a2[i].first);
	}
	printf("ma = %d, mi = %d\n", ma, mi);
	*/
	int now = (mi + ma) / 2;	
	
	while (ma - mi > 1)
	{
		//printf("mi = %d, ma = %d, now = %d\n", mi, ma, now);
		if (judge(a1, now) && judge(a2, now))
		{
			ma = now;
		}
		else
		{
			mi = now + 1;
		}
		
		now = (mi + ma) / 2;
	}
	
	if (judge(a1, mi) && judge(a2, mi))
	{
		cout << mi << endl;
	}
	else
	{
		cout << ma << endl;
	}
}
