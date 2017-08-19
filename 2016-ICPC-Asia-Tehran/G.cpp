#include <bits/stdc++.h>

using namespace std;
double p1[10000] = {0};
double p2[10000] = {0};
double p[10000] = {0};
int main()
{

	int n;
	cin >> n;
	while (n != 0)
	{
		for (int i = 0; i <= 10000; i++)
		{
			p[i] = 0;
		}
		p[0] = 1;
			
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			double q;
			cin >> q;
		
			int num;
			cin >> num;
			sum += num;
			
			for (int j = 0; j <= sum ;j++)
			{
				p1[j] = p2[j] = 0;
			}
			for (int j = 0; j <= sum; j++)
			{
				p1[j] = p[j] * (1 - q);
				p2[j + num] = p[j] * q;
			}
		
			for (int j = 0; j <= sum; j++)
			{
				 p[j] = p1[j] + p2[j]; 
			}
			
			/*for (int j = 0; j <= sum; j++)
			{
				printf("i = %d, p1[%d] = %.4lf, p2[%d] = %.4lf, p[%d] = %.4lf\n", i, j, p1[j], j, p2[j], j, p[j]);
			}
			printf("\n");*/
		}
		
		double ans = 0;
		for (int i = sum / 2 + 1; i <= sum; i++)
		{
			ans += p[i];
		}
		
		printf("%.4lf\n", ans);
		cin >> n;
	}
	return 0;
}
		
	
