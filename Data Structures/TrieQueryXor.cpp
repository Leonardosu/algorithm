#include "bits/stdc++.h" // Leonardo Su
using namespace std;
/*
	Given a N queries.
	There are three types.
	+ x . Add the number x in your multiset.
	- x . Remove that number from your multiset.
	? x . Print the max xor you can get with x and a number form your multiset. 
		  max value x ^ y, y in multiset
*/
z
#define N 32
#define S 2
struct node {
	int val, qtd;
	node *prox[S];

	node() {
		qtd = val = 0;
		for(int i = 0; i < S; i++) prox[i] = NULL;
	}

	void Insert(int number) {
		node *curr = this;
		for(int i=N-1;i>=0;--i) {
			bool bit = (number & (1<<i));
			if(curr->prox[bit] == NULL)
				curr->prox[bit] = new node();

			curr->qtd++;
			curr = curr->prox[bit];
		}

		curr->qtd++;
		curr->val = number;
	}

	void Remove(int number) {
		node *curr = this;
		for(int i=N-1;i>=0;--i) {
			bool bit = number & (1<<i);
			curr->qtd--;
			curr = curr->prox[bit];
		}

		curr->qtd--;
	}

	int query(int number) { // max xor with this number
		node *curr = this;
		for(int i=N-1;i>=0;--i) {
			bool bit = number & (1<<i);
			if(curr->prox[1-bit] != NULL && curr->prox[1-bit]->qtd > 0)
				curr = curr->prox[1-bit];

			else if(curr->prox[bit] != NULL && curr->prox[bit]->qtd > 0)
				curr = curr->prox[bit];
		}
		return  number ^ curr->val;
	}
};

node *tree = new node();
int main() {

}