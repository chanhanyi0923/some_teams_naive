#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

const ll tot = 100000;
vector<ll> dp_prev(tot + 1);
vector<ll> dp_next(tot + 1);
vector<bool> vis_prev(tot + 1);
vector<bool> vis_next(tot + 1);

int main()
{
	int n;
	cin >> n;
	fill(dp_next.begin(), dp_next.end(), 0);
	fill(vis_next.begin(), vis_next.end(), false);
	dp_next[0] = 100;
	vis_next[0] = true;
	for (int i = 0; i < n; i++)
	{
		int price;
		cin >> price;
		for (int i = 0; i <= tot; i++)
		{
			dp_prev[i] = dp_next[i];
			vis_prev[i] = vis_next[i];
			dp_next[i] = 0;
			vis_next[i] = false;
		}
		
		for (int i = 0; i <= tot; i++)
		{
			if (vis_prev[i])
			{
				dp_next[i] = max(dp_next[i], dp_prev[i]);
				vis_next[i] = true;
				// do nothing
				
				int buy = min(tot - i, dp_prev[i] / price);
				dp_next[i + buy] = max(dp_next[i + buy], dp_prev[i] - (buy * price));
				vis_next[i + buy] = true;
				//buying
				
				int sell = i;
				dp_next[0] = max(dp_next[0], dp_prev[i] + (sell * price));
				vis_next[0] = true;
				//selling
			}
		}
	}
	
	cout << dp_next[0] << endl;
}
