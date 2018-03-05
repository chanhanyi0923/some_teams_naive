#include<bits/stdc++.h>
using namespace std;

const double eps=1e-10;

double cmp(double a,double b){
	double delta=a-b;
	if(fabs(delta)<=eps)return 0;
	return delta;
}

struct point{
	double x,y;
	point() {}
	point(double x,double y):x(x),y(y){
	}
	point operator + (point p){
		return point(x+p.x,y+p.y);
	}
	point operator - (point p){
		return point(x-p.x,y-p.y);
	}
	point operator * (double d){
		return point(x*d,y*d);
	}
	point operator / (double d){
		return point(x/d,y/d);
	}
	bool operator == (point p){
		return cmp(x,p.x)==0 && cmp(y,p.y)==0;
	}
	double dot(point p){
		return x*p.x+y*p.y;
	}
	double det(point p){
		return x*p.y-y*p.x;
	}
};

const point NOPOINT=point(1000086,1000086);

double cmp_side(point a,point b){
	return cmp(a.x*b.y,a.y*b.x);
}

struct line{
	point u,v;
};

bool on_seg(point q,line p){
	return (p.u-q).det(p.v-q)==0 && (p.u-q).dot(p.v-q)<=0;
}

line makeline(point a,point b){
	line ans;
	if(a==b){
		ans.u=a;
		ans.v=point(0,0);
		return ans;
	}
	ans.u=(a+b)/2;
	point delta=b-a;
	ans.v=point(ans.u.x-delta.y,ans.u.y+delta.x);
	return ans;
}

point inter(line a,line b){
	point s=a.u-a.v,t=b.u-b.v;
	double at=cmp_side(s,t);
	if(at==0){
		if(on_seg(a.u,b)){
			return point(a.u);
		}else{
			return NOPOINT;
		}
	}
	point ans=point(a.u+s*(b.u-a.u).det(t)/at);
	return ans;
}

double dis(point a,point b){
	point delta=a-b;
	return sqrt(delta.x*delta.x+delta.y*delta.y);
}

point p[50];
int mi;
int n;

void check(point pp){
	vector<double> wyz;
	for(int i=0;i<n;i++){
		wyz.push_back(dis(p[i],pp));
	}
	sort(wyz.begin(),wyz.end());
	int now=0;
	double las=-1;
	for(int i=0;i<n;i++){
		if(cmp(wyz[i],las)!=0){
			las=wyz[i];
			now++;
		}
	}
	if(now<mi)mi=now;
}

int main(){
	/*           TEST
	line a;//=(line)(point(1,2),point(2,3));
	a.u.x=-1,a.u.y=2,a.v.x=2,a.v.y=-3;
	line b;//=(line)(point(2,1),point(3,2));
	b.u.x=2,b.u.y=1,b.v.x=2,b.v.y=3;
	point c=inter(a,b);
	printf("%.3f,%.3f\n",c.x,c.y);
	*/
	scanf("%d",&n);
	mi=n;
	for(int i=0;i<n;i++){
		int tempx,tempy;
		scanf("%d%d",&tempx,&tempy);
		p[i].x=tempx,p[i].y=tempy;
	}
	vector<line> lines;
	vector<point> interpoint;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			lines.push_back(makeline(p[i],p[j]));
		}
	}
	int m=(int)lines.size();
	for(int i=0;i<m;i++){
		for(int j=i+1;j<m;j++){
			point tempp=inter(lines[i],lines[j]);
			if(tempp==NOPOINT)continue;
			interpoint.push_back(tempp);
		}
	}
	int num=interpoint.size();
	for(int i=0;i<num;i++){
		check(interpoint[i]);
	}
	if(mi==n && n!=1)mi--;
	printf("%d\n",mi);
	return 0;
}
