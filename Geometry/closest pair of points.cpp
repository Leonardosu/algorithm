#include "bits/stdc++.h"
#define f first
#define s second
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) x.begin(),x.end()
#define present(c, x) (c.find(x) != c.end())
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct pt {
    using P = pt;
    using T = long long;

    T x, y; 
    int id;
    explicit pt(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
};

pair<ll, pair<pt, pt>> ret;
void upd(const pt &a, const pt &b) {
	ll curr = (a - b).dist2();
	if(curr < ret.f) { //min dist
		ret.f = curr;
		ret.s = {a, b};
	}
}

pair<pt, pt> closest(vector<pt> v) {
	assert(sz(v) > 1);

	set<pt> S;
	sort(all(v), [](pt a, pt b) { return a.y < b.y; });
	ret = {LLONG_MAX, {pt(), pt()}};
	int j = 0;
	for (pt p : v) {
		pt d{1 + (ll)sqrt(ret.first), 0};
		while (v[j].y <= p.y - d.x) S.erase(v[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo)
			upd(*lo, p);
		
		S.insert(p);
	}
	return ret.second;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;
    cin>>n;
    vector<pt> points(n);
    int i = 1;
    for(auto &p : points) {
        cin>>p.x>>p.y;
        p.id = i++;
    }
    
    closest(points);
    cout<<ret.f<<"\n";
    cout<<ret.s.f.id<<' '<<ret.s.s.id<<'\n';
}