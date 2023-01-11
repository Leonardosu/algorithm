#include "bits/stdc++.h" // Leonardo Su
using namespace std;
typedef long long ll;
const long long int maxn = 1e18 + 100;
struct node {
	ll a,b,v;
	node *l,*r;

	node(ll a_ = 0,ll b_ = maxn,ll v_ = 0) {
		a = a_, b = b_, v = v_;
		l = r = NULL;
 	}

 	void upd(ll p,ll val) {
        if(p < a || p > b) return;
        if(a == b) {
        	v += val;
            return;
        }

        ll mid = (a+b)/2LL;
        if(p <= mid) {
            if(l == NULL) l = new node(a, mid,0);
            l->upd(p,val);
        } else {
            if(r == NULL) r = new node(mid + 1, b,0);
            r->upd(p,val);
        }

        v = ( (l == NULL)? 0 : l->v ) + ( (r == NULL) ? 0 : r-> v );
    }

 	ll query(ll i, ll j) {
        if(i > b || j < a) return 0LL;
        if(i <= a && b <= j) return v;

        ll A = (l == NULL)? 0 : l->query(i, j);
        ll B = (r == NULL)? 0 : r->query(i, j);

        return A + B;
    }
};


node *tree = new node();
int main() {

}