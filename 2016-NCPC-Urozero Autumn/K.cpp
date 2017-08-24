#include <bits/stdc++.h>

typedef long long ll;
using namespace std;
#define pb push_back
const double eps = 1e-12;

double dis(double a,double b){
	return sqrt(a*a+b*b);
}
int cmp(double x)
{
	if (fabs(x) < eps) return 0;
	if (x > 0) return 1;
	return -1;
}
struct point{
	double x,y;
	point () {}
	point (double a, double b): x(a), y(b) {}
	friend point operator + (const point& a,const point& b){
		return (point){a.x+b.x,a.y+b.y};
	}
	friend point operator - (const point& a,const point& b){
		return (point){a.x-b.x,a.y-b.y};
	}
	friend point operator * (const point& a,const double& b){
		return (point){a.x*b,a.y*b};
	}
	friend double operator * (const point& a, const point& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	friend point operator / (const point& a,const double& b){
		return (point){a.x/b,a.y/b};
	}

};

struct vec{
	point P;
	double t;
};

double myDis(point A, point B)
{
	return dis(A.x - B.x, A.y - B.y);
}
double disPtoLine(point B, point C)
{
	point A = point(0, 0);
	double dot = (A - C) * (B - C);
	double ans = min(myDis(A, B), myDis(A, C));
	//printf("dot = %lf, myDis(b, c) = %lf\n", dot, myDis(B, C));
	if (fabs(dot / ((B.x - C.x) * (B.x - C.x) + (B.y - C.y) * (B.y - C.y))) > 1) {
		return ans;
	} else {
		
		double ans2 = abs((B.y - C.y) * (A.x - B.x) - (B.x - C.x) * (A.y - B.y));
		ans2 /= myDis(B, C);
		return min(ans, ans2);
	}
}



double det(const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}

double dot(const point &a, const point &b)
{
	return a.x * b.x + a.y * b.y;
}

double disPtoLine(point p, point s, point t)
{
	if (cmp(dot(p - s, t - s)) < 0)
		return dis(p.x - s.x, p.y - s.y);
	if (cmp(dot(p - t, s - t)) < 0)
		return dis(p.x - t.x, p.y - t.y);
	return fabs(det(s - p, t - p) / myDis(s, t));
}
vector<vec> v1, v2, vr;
vector<point> p1, p2;

void print(vector<vec>& v1)
{
		
	//for (size_t i = 0; i < v1.size(); i++)
	//{
	//	printf("(%.4lf, %.4lf), t = %.4lf\n", v1[i].P.x, v1[i].P.y, v1[i].t);
	//}
	//printf("-------\n");
	
}
int main(){
	int n1, n2;

	cin >> n1;
	p1.resize(n1);
	cin >> p1[0].x >> p1[0].y;
	for (int i = 1; i < n1; i++)
	{
		cin >> p1[i].x >> p1[i].y;
		int dy = p1[i].y - p1[i - 1].y;
		int dx = p1[i].x - p1[i - 1].x;
		
		vec tmp;
		tmp.P.x = dx / dis(dx, dy);
		tmp.P.y = dy / dis(dx, dy);
		tmp.t = dis(dx, dy);
		v1.push_back(tmp); 
	}		
	
	cin >> n2;
	p2.resize(n2);
	cin >> p2[0].x >> p2[0].y;
	for (int i = 1; i < n2; i++)
	{
		cin >> p2[i].x >> p2[i].y;
		int dy = p2[i].y - p2[i - 1].y;
		int dx = p2[i].x - p2[i - 1].x;
		
		vec tmp;
		tmp.P.x = dx / dis(dx, dy);
		tmp.P.y = dy / dis(dx, dy);
		tmp.t = dis(dx, dy);
		v2.push_back(tmp); 
	}
	
	print(v1);
	print(v2);

	point initial(p1[0].x - p2[0].x, p1[0].y - p2[0].y);
	
	point nowV;
	int cur1 = 0;
	int cur2 = 0;
	
	while (cur1 < n1 - 1 && cur2 < n2 - 1)
	{
		nowV = v1[cur1].P - v2[cur2].P;
		double t = min(v1[cur1].t, v2[cur2].t);
		v1[cur1].t -= t;
		v2[cur2].t -= t;
		if (fabs(v1[cur1].t) < eps)
		{
			cur1++;
		}
		if (fabs(v2[cur2].t) < eps)
		{
			cur2++;
		}
		
		vec tmp;
		tmp.P = nowV;
		tmp.t = t;
		vr.push_back(tmp);
	}
	
	print(vr);
	point q1 = initial;
	point q2(0, 0);
	point O(0, 0);
	double mi = dis(initial.x,initial.y);
	for (size_t i = 0; i < vr.size(); i++)
	{

		q2.x = q1.x + vr[i].t * vr[i].P.x;
		q2.y = q1.y + vr[i].t * vr[i].P.y;
		//printf("i = %d, q1 = (%.4lf, %.4lf), q2 = (%.4lf, %.4lf)\n", i, q1.x, q1.y, q2.x, q2.y);			
		//printf("disPtoLine:%.4lf\n", disPtoLine(O, q1, q2));
		mi = min(mi, disPtoLine(O, q1, q2));
		q1 = q2;
	}
	
	printf("%.15lf\n", mi);
	return 0;
}

