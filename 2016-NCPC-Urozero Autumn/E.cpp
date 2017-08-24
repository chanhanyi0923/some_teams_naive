#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll pow_mod(ll a,ll p,ll mod){
    if(p==0)return 1;
    ll ans=pow_mod(a,p/2,mod);
    ans=ans*ans%mod;
    if(p%2)ans=ans*a%mod;
    return ans;
}

ll euler_phi(ll n){
    ll m=(ll)sqrt(n+0.5);
    ll ans=n;
    for(int i=2;i<=m;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0)n/=i;
        }
    }
    if(n>1)ans=ans/n*(n-1);
    return ans;
}

ll expo(ll n,ll m){
    if(m==1)return 0;
    if(n==1)return 1;
    if(n-1<3)return pow_mod(n,n-1,m);
    if(n-1==3)return pow_mod(n,9,m);
    ll phi=euler_phi(m);
    return pow_mod(n,phi+expo(n-1,phi),m);
}

int main(){//printf("%lld\n",euler_phi(17));
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%lld\n",expo(n,m));
    return 0;
}
