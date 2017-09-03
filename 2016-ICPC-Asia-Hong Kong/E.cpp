#include<bits/stdc++.h>
using namespace std;
const int maxn = 5001000;
const double PI = acos(-1);
void FFT(complex<double> *a,int len,int inv){
    for(int i=0,n1=0,n2=0;i<len;++i,n2^=(len/(i&-i)>>1),n1^=(i&-i))
        if(n1>n2)
            swap(a[n1],a[n2]);
    for(int m=1;m<=len>>1;m<<=1){
        complex<double> w0(cos(PI/m),sin(PI/(inv*m))),w=1,t;
        for(int k=0;k<len;k+=(m<<1),w=1)
            for(int j=0;j<m;++j,w*=w0){
                t=w*a[k+j+m];
                a[k+j+m]=a[k+j]-t;
                a[k+j]+=t;
            }
    }
    if(inv==-1)
        for(int i=0;i<len;++i)a[i]/=len;
}
complex<double> a[maxn],b[maxn];
int main(){
    int n;
    char s[maxn];
    scanf("%s",s);
    n=strlen(s);
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(int i=0;i<n;i++){
        char ch=s[i];
        if(ch=='A'){
            a[i]=complex<double>(0,0);
            b[n-i-1]=complex<double>(1,0);
        }
        if(ch=='B'){
            a[i]=complex<double>(1,0);
            b[n-i-1]=complex<double>(0,0);
        }
    }

    int nn=1;
    while(nn<=n*2)nn<<=1;
    FFT(a,nn,1);
    FFT(b,nn,1);
    for(int i=0;i<=nn;i++){
        a[i]*=b[i];
    }
    FFT(a,nn,-1);
    for(int i=n-2;i>=0;i--)printf("%d\n",(int)(a[i].real()+0.5));
    return 0;
}
