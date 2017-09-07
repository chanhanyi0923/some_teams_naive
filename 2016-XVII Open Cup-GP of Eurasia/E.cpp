#include <bits/stdc++.h>
using namespace std;

map<string, int> s;

vector<bitset<2000> > t[1005];

char str01[2005];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int k, n;
	cin >> k >> n;
	int set_num = 0;
	for (int i = 0; i < n; i++)
	{
		string str;
		//string str01;
		cin >> str;
		//str01.resize(str.length());
		for (size_t j = 0; j < str.length(); j++)
		{
			if ('A' <= str[j] && str[j] <= 'Z')
			{
				str01[j] = '1';
				str[j] = str[j] - 'A' + 'a';
			}
			else
			{
				str01[j] = '0';
			}
		}
		str01[str.length()] = 0;
		
		//cout << str01 << endl;
		if (s.count(str) == 0)
		{
			t[set_num].push_back(bitset<2000>(string(str01)));
			s[str] = set_num;
	//		cout << str << endl;
			set_num++;
		}
		else
		{
			t[s[str]].push_back(bitset<2000>(string(str01)));
		}
	}
	
	int m;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		string str;
		cin >> str;
		
		map<string, int>::iterator f;

		//string str01;
//		str01.resize(str.length());
		for (int j = 0; j < str.length(); j++)
		{
			if ('A' <= str[j] && str[j] <= 'Z')
			{
				str01[j] = '1';
				str[j] = str[j] - 'A' + 'a';
			}
			else
			{
				str01[j] = '0';
			}
		}
		
	//	cout << str << endl;
		str01[str.length()] = 0;
		f = s.find(str);
		if (f == s.end())
		{
			printf("0\n");
			continue;
		}
		
		int set_num = f->second;
		//puts("!");
		// cout << str01 << endl;
		bitset<2000> c = bitset<2000>(string(str01));
	//	puts("!");
		int ans = 0;
		for (size_t j = 0; j < t[set_num].size(); j++)
		{
	//		printf("coutn = %d\n", (t[set_num][j] ^ c).count());
			if ((t[set_num][j] ^ c).count() <= k)
			{
				ans++;
			}
		}
		cout << ans << endl;
	}
}	
