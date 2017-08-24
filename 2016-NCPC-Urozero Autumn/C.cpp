#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

vector<vector<int> > card;

void init()
{
	vector<int> p;
	for (int i1 = 1; i1 < 52; i1 += 13)
		for (int i2 = 1; i2 < 52; i2 += 13)
			if (i1 != i2) for (int i3 = 1; i3 < 52; i3 += 13)
				if ((i1 != i3) && (i2 != i3)) for (int i4 = 1; i4 < 52; i4 += 13)
					if ((i1 != i4) && (i2 != i4) && (i3 != i4)) for (int j1 = 0; j1 <= 1; j1++)
						for (int j2 = 0; j2 <= 1; j2++)
							for (int j3 = 0; j3 <= 1; j3++)
								for (int j4 = 0; j4 <= 1; j4++)
								{
									p.resize(52);
									int cur = 0;
									if (j1)
									{
										for (int k = 0; k < 13; k++)
										{
											p[k] = i1 + cur;
											cur++;
										}
									}
									else
									{	
										for (int k = 12; k >= 0; k--)
										{
											p[k] = i1 + cur;
											cur++;
										}
									}
									
									cur = 0;
									if (j2)
									{
										for (int k = 13; k < 26; k++)
										{
											p[k] = i2 + cur;
											cur++;
										}
									}
									else
									{
										for (int k = 25; k >= 13; k--)
										{
											p[k] = i2 + cur;
											cur++;
										}
									}
									
									cur = 0;
									if (j3)
									{
										for (int k = 26; k < 39; k++)
										{
											p[k] = i3 + cur;
											cur++;
										}
									}
									else
									{
										for (int k = 38; k >= 26; k--)
										{
											p[k] = i3 + cur;
											cur++;
										}
									}
									
									cur = 0;
									if (j4)
									{
										for (int k = 39; k < 52; k++)
										{
											p[k] = i4 + cur;
											cur++;
										}
									}
									else
									{
										for (int k = 51; k >= 39; k--)
										{
											p[k] = i4 + cur;
											cur++;
										}
									}
									
									card.push_back(p);
									p.clear();
								}
}

int getNum(char a, char b)
{
	int n1;
	int n2;
	switch (a)
	{
		case 'T':
		{
			n1 = 8;
			break;
		}
		case 'J':
		{
			n1 = 9;
			break;
		}
		case 'Q':
		{
			n1 = 10;
			break;
		}
		case 'K':
		{
			n1 = 11;
			break;
		}
		case 'A':
		{
			n1 = 12;
			break;
		}
		default:
		{
			n1 = a - '0' - 2;
			break;
		}
	}
	
	switch (b)
	{
		case 's':
		{
			n2 = 0;
			break;
		}
		case 'h':
		{
			n2 = 1;
			break;
		}
		case 'd':
		{
			n2 = 2;
			break;
		}
		case 'c':
		{
			n2 = 3;
			break;
		}
	}
	
	int ret = n2 * 13 + n1;
	return ret;
}
const int INF = 10000000;
int dp[100];
int solve(vector<int> &a)
{
	int ma = 0;
	for (size_t i = 0; i < a.size(); i ++) {
		dp[i] = 0;
		for (size_t j = 0; j < i; j ++) {
			if (a[j] < a[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		if (dp[i] > ma)
			{
				ma = dp[i];
			}
	}
	return ma + 1;
}
int main()
{
	init();
	int n;
	cin >> n;
	vector<int> p;
	p.resize(n);
	for (int i = 0; i < n; i++)
	{
		getchar();
		char a = getchar();
		char b = getchar();
		int num = getNum(a, b);
		p[i] = num;
	}
	
	int mi = 0x7fffffff;
	for (size_t i = 0; i < card.size(); i++)
	{
		vector<int> q;
		for (int j = 0; j < n; j++)
		{
			q.push_back(card[i][p[j]]);
		}
		/*
		for (size_t i = 0; i < q.size(); i++)
		{
			printf("%d ", q[i]);
		}
		printf(":%d\n", solve(q));
		printf("\t");
		for (size_t t = 0; t < q.size(); t++)
		{
			printf("%d ", dp[t]);
		}
		printf("\n");
		*/
		mi = min(mi, n - solve(q));
	}
	
	cout << mi << endl;
}

