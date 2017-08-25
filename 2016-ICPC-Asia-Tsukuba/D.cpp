#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct stat
{
	vector<int> a;
	stat()
	{
		a.resize(26);
		fill(a.begin(), a.end(), 0);
	}
	void clear()
	{
		fill(a.begin(), a.end(), 0);
	}
	
	friend bool operator < (const stat& s, const stat& t)
	{
		for (int i = 0; i < 26; i++)
		{
			if (s.a[i] < t.a[i])
			{
				return true;
			}
			if (s.a[i] > t.a[i])
			{
				return false;
			}
		}
		return true;
	}
	
	bool operator == (const stat& s) const
	{
		for (int i = 0; i < 26; i++)
		{
			if (s.a[i] != a[i])
			{
				return false;
			}
		}
		return true;
	}
};

map<vector<int>, int> c;

int main()
{
	string s;
	string t;
	cin >> s;
	cin >> t;
	
	int l1 = s.length();
	int l2 = t.length();

	int ans = 0;
	int len = min(l1, l2);
	
	
	for (int l = len; l >= 1; l--)
	{
	
		c.clear();
		stat now;
		for (int i = 0; i < l; i++)
		{
			now.a[s[i] - 'a']++;
		}
		
		c[now.a] = 1;

		for (int i = 1; i + l <= l1; i++)
		{
			now.a[s[i - 1] - 'a']--;
			now.a[s[i + l - 1] - 'a']++;
			c[now.a] = 1;

		}
		
		now.clear();
		for (int i = 0; i < l; i++)
		{
			now.a[t[i] - 'a']++;
		}



		if (c[now.a] == 1)
		{
			ans = l;
			goto END;
		}
		
		for (int i = 1; i + l <= l2; i++)
		{
			now.a[t[i - 1] - 'a']--;
			now.a[t[i + l - 1] - 'a']++;


			if (c[now.a] == 1)
			{
				ans = l;
				goto END;
			}
		}

	}
	
	
END:
	cout << ans << endl;
	return 0;
}
