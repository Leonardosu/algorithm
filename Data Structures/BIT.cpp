#include "bits/stdc++.h" // Leonardo Su
using namespace std;

typedef long long ll;
struct BIT {
    vector<ll> bit;
    int N;
    BIT(int n) {
        N = n + 2;
        bit.resize(n + 2);            
    }
    
    void update(int x, ll val = 1) {
        x++;
        while(x < N)
            bit[x] += val, x += x&(-x);
    }
    
    int query(int x) {
        if(x <= 0) return 0;
        x++;
        ll sum = 0;
        while(x > 0)
            sum += bit[x], x -= x&(-x);
        return sum;
    }
};

int main() {

}