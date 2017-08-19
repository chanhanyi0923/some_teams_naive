#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct ques
{
    int a;
    int label;
    int ans;
};

bool compa(const ques& a, const ques& b)
{
    return (a.a < b.a);
}

bool compla(const ques& a, const ques& b)
{
    return (a.label < b.label);
}

double f(int x){
    if(x%4 == 0)return x/4-0.5;
    if(x%4 == 3)return x/4+1.5;
    return x/4+0.5;
}

int main()
{
    
    vector<ques> ask;
    int n;
    cin >> n;
    ask.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> ask[i].a;
        ask[i].label = i;
        ask[i].ans = 0;
    }
    
    sort(ask.begin(), ask.end(), compa);
    
    int now = 4;
    double s = 2;
    for (int i = 0; i < n; i++)
    {
        while(ask[i].a>s+0.1){
            s+=f(now);
            now++;
            //printf("s=%.4f\n",s);
        }
        ask[i].ans=now;
    }
    
    sort(ask.begin(), ask.end(), compla);
    
    for (int i = 0; i < n; i++)
    {
        cout << ask[i].ans << endl;
    }
    
}