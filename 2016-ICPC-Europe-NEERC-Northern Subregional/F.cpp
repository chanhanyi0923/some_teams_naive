#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x7fffffff;

int solve(int W, int H, int w, int h)
{
	if (w > W || h > H)
	{
		return INF;
	}
	
	int ans = 0;
	while (W > w)
	{
		W = (W + 1) / 2;
		ans++;
	}
	while (H > h)
	{
		H = (H + 1) / 2;
		ans++;
	}
	return ans;
}
int main()
{
	freopen("folding.in", "r", stdin);
	freopen("folding.out", "w", stdout);
	int W, H, w, h;
	cin >> W >> H >> w >> h;
	int ans = min(solve(W, H, w, h), solve(W, H, h, w));
	
	if (ans == INF)
	{
		cout << -1 << endl;
	}
	else
	{
		cout << ans << endl;
	}
}
