#include "bits/stdc++.h"
#define INF 0x3f3f3f3f
#define pb push_back
#define pb push_back
#define sz(x) (int)(x).size()
#define ALL(x) x.begin(),x.end()
using namespace std;
/*
	Return a polygon representing the intersection of a half-plane created by each edge.
	Example of application: Find the polygon (can be non-convex) that 
	each point inside can view all the given polygon
*/
const double EPS = 1e-9;
struct point {
	double x, y;	
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm() { return hypot(x, y); }
	point normalized() {
		return point(x,y)*(1.0/norm());
	}
	double angle() { return atan2(y, x); }
	double polarAngle() {
		double a = atan2(y, x);
		return a < 0 ? a + 2*acos(-1.0) : a;
	}
	bool operator < (point &other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point &other) const { 
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
	point operator +(point other) const { return point(x + other.x, y + other.y); }
	point operator -(point other) const { return point(x - other.x, y - other.y); }
	point operator *(double k) const { return point(x*k, y*k); }
};

double dot(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

point lineIntersectSeg(point p, point q, point A, point B) {
	double c = cross(A-B, p-q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p-q)*(a/c)) - ((A-B)*(b/c));
}

bool parallel(point a, point b) {
	return fabs(cross(a, b)) < EPS;
}

typedef vector<point> polygon;
typedef pair<point, point> halfplane;

double signedArea(polygon &P) {
	double result = 0.0;
	int n = sz(P);
	for (int i = 0; i < n; i++) 
		result += cross(P[i], P[(i+1)%n]);
	
	return result / 2.0;
}

point dir(halfplane h) { return h.second - h.first; }

bool belongs(halfplane h, point a) {
	return cross(dir(h), a - h.first) > EPS;
}

bool hpcomp(halfplane ha, halfplane hb) {
	point a = dir(ha), b = dir(hb);
	if (parallel(a, b) && dot(a, b) > EPS)
		return cross(b, ha.first - hb.first) < -EPS;
	if (b.y*a.y > EPS) return cross(a, b) > EPS;
	else if (fabs(b.y) < EPS && b.x > EPS) return false;
	else if (fabs(a.y) < EPS && a.x > EPS) return true;
	else return b.y < a.y;
}

polygon intersect(vector<halfplane> H, double W = INF) {
	H.pb({point(-W,-W), point(W,-W)});
	H.pb({point(W,-W), point(W,W)});
	H.pb({point(W,W), point(-W,W)});
	H.pb({point(-W,W), point(-W,-W)});
	sort(ALL(H), hpcomp);
	int i = 0;
	while(parallel(dir(H[0]), dir(H[i]))) i++;
	deque<point> P;
	deque<halfplane> S;
	S.pb(H[i-1]);
	for(;i < sz(H); ++i) {
		while(!P.empty() && !belongs(H[i], P.back()))
			P.pop_back(), S.pop_back();
		point df = dir(S.front()), di = dir(H[i]);
		if (P.empty() && cross(df, di) < EPS)
			return polygon();
		P.pb(lineIntersectSeg(H[i].first, H[i].second,
			S.back().first, S.back().second));
		S.pb(H[i]);
	}
	while(!belongs(S.back(), P.front()) ||
		!belongs(S.front(), P.back())) {
		while(!belongs(S.back(), P.front()))
			P.pop_front(), S.pop_front();
		while(!belongs(S.front(), P.back()))
			P.pop_back(), S.pop_back();
	}
	P.push_back(lineIntersectSeg(S.front().first,
		S.front().second, S.back().first, S.back().second));
	return polygon(P.begin(), P.end());
}

int main() {
	
	return 0;
}