#include "bits/stdc++.h" // Leonardo Su
using namespace std;
typedef long long ll;
const long long int maxn = 1e18 + 100;

struct Node{
    int val, lazy, tl, tr;
    Node* left;
    Node* right;

    Node(int l, int r) {
        val = lazy = 0;
        left = NULL;
        right = NULL;
        tl = l, tr = r;
    }
    
    void push(){
        int tm = (tl + tr)/2;
        if(left == NULL && right == NULL){
            left = new Node(tl,tm);
            right = new Node(tm+1,tr);
        }
        
        if(lazy){
            left->lazy = 1;
            right->lazy = 1;
            left->val = tm - tl + 1;
            right->val = tr - (tm+1) + 1;
            lazy = 0;
        }
    }
    
    int query(int l, int r){
        if(l>r || r<tl  || l>tr) return 0;
        if(l<= tl && r>= tr) return val;
        push();
        int ans = 0;
        if(left != NULL) ans += left->query(l,r);
        if(right != NULL) ans += right->query(l,r);
        return ans;
    }
    
    void update(int l, int r){
        if(l>r ||  r<tl || l>tr) return;
        if(l<= tl && r>= tr){
            val = tr-tl+1;
            lazy = 1;
            return;
        }
        push();
        val = 0;
        if(left != NULL) {
            left->update(l,r);
            val += left->val;
        }
        if(right != NULL) {
            right->update(l,r);
            val += right->val;
        }
    }
};

node *tree = new node();
int main() {

}