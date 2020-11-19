/*
S = Area of polygon.
I = Number of points strictly inside polygon.
B = Number of points on boundary.
With Pick's Theorem: S = I + B/2 -1
https://cp-algorithms.com/geometry/picks-theorem.html
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int ll;
struct point
{   
    int x,y;    
    point(){}
    point(int _x,int _y)
    {
        x = _x,y = _y;
    }

    point operator-(const point &a)
    {
        return point(x-a.x,y-a.y);
    }
};

vector<point> p;

ll cross(point v1,point v2)
{
    return v1.x*v2.y - v1.y*v2.x;
}

ll area(vector<point>p)
{
    ll ans = 0;
    for(int i=2;i<p.size();++i)
        ans += cross(p[i]-p[0],p[i-1]-p[0]);
    return ans;
}

ll boundary(vector<point> &A)
{
    int n = A.size();
    ll ats = n;

    for(int i=0; i<n; i++)
    {
        ll dx = (A[i].x - A[(i+1)%n].x);
        ll dy = (A[i].y - A[(i+1)%n].y);
        ats+=abs(__gcd(dx,dy)) - 1;
    }
    return ats;
}

int main()
{
    int n;
    cin>>n;
    p.resize(n);
    for(int i=0;i<n;++i)
        cin>>p[i].x>>p[i].y;
    

    ll S = area(p);
    ll B = boundary(p);
    ll I = (abs(S) - B + 2LL)/2LL;

    cout << I << endl;
}