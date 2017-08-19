#include<bits/stdc++.h>
using namespace std;
#define pb push_back

inline int sqr(int x){
    return x*x;
}
struct point{
    int x,y;
    point(){}
    point(int a,int b):x(a),y(b){}
    friend point operator + (const point &a,const point &b){
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator - (const point &a,const point &b){
        return point(a.x-b.x,a.y-b.y);
    }
    friend bool operator == (const point &a,const point &b){
        return a.x==b.x && a.y==b.y;
    }
    int norm(){
        return sqr(x)+sqr(y);
    }
};
int det(const point &a,const point &b){
    return a.x*b.y-a.y*b.x;
}

struct polygon_convex{
    vector <point> P;
    polygon_convex(int Size=0){
        P.resize(Size);
    }
};

bool comp_less(const point &a,const point &b){
    return a.x<b.x || a.x==b.x && a.y<b.y;
}
polygon_convex convex_hull(vector<point> a){
    polygon_convex res(2*a.size()+5);
    sort(a.begin(),a.end(),comp_less);
    a.erase(unique(a.begin(),a.end()),a.end());
    int m=0;
    for(int i=0;i<a.size();i++){
        while(m>1 && det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2])<=0)--m;
        res.P[m++]=a[i];
    }
    int k=m;
    for(int i=int(a.size())-2;i>=0;--i){
        while(m>k && det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2])<=0)--m;
        res.P[m++]=a[i];
    }
    res.P.resize(m);
    if(a.size()>1)res.P.resize(m-1);
    return res;
}

vector<point> nod[110];

void init(){
    for(int i=0;i<110;i++)nod[i].clear();
}

int main(){
    ///freopen("1.in","r",stdin);
    ///freopen("1.out","w",stdout);
    int n;
    while(scanf("%d",&n),n!=0){
        init();
        for(int i=0;i<n;i++){
            int x,y,sig;
            scanf("%d%d%d",&x,&y,&sig);
            nod[sig].pb((point){x,y});
        }
        vector<polygon_convex> nod2;
        for(int i=0;i<110;i++){
            if(nod[i].size()>0){
                nod2.pb(convex_hull(nod[i]));
            }
        }
        int N=nod2.size();

        /*for(int i=0;i<N;i++){
            int N2=nod2[i].P.size();
            for(int j=0;j<N2;j++)printf("(%d,%d) ",nod2[i].P[j].x,nod2[i].P[j].y);puts("");
        }*/

        //printf("%d\n",N);
        int ans=0;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                int ma=0,maxord=0,N2=nod2[i].P.size(),N3=nod2[j].P.size(),last=0;
                for(int k2=0;k2<N3;k2++){
                    if((nod2[i].P[0]-nod2[j].P[k2]).norm()>ma){
                        maxord=k2;
                        ma=(nod2[i].P[0]-nod2[j].P[k2]).norm();
                        //printf("(%d,%d) (%d,%d)  %d\n",nod2[i].P[0].x,nod2[i].P[0].y,nod2[j].P[k2].x,nod2[j].P[k2].y,ma);
                    }
                }
                last=maxord;
                for(int k1=1;k1<N2;k1++){
                    while((nod2[i].P[k1]-nod2[j].P[(last+1)%N3]).norm() > (nod2[i].P[k1]-nod2[j].P[last]).norm())last=(last+1)%N3;
                    if((nod2[i].P[k1]-nod2[j].P[last]).norm() > ma)ma=(nod2[i].P[k1]-nod2[j].P[last]).norm();
                    //printf("ma=%d   (%d,%d) (%d,%d)\n",ma,nod2[i].P[k1].x,nod2[i].P[k1].y,nod2[j].P[last].x,nod2[j].P[last].y);
                }
                if(ma>ans)ans=ma;

            }
        }//puts("");
        printf("%d\n",ans);
    }
    return 0;
}
