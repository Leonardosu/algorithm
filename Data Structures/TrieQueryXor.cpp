#include "bits/stdc++.h" // Leonardo Su
#define f first
#define s second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
/*
	Given a N queries.
	There are three types.
	+ x . Add the number x in your multiset.
	- x . Remove that number from your multiset.
	? x . Print the max xor you can get with x and a number form your multiset. 
		  max value x ^ y, y in multiset
*/

#define N 32
#define S 2
struct node
{
	int val;
	int qtd;
	node *prox[S];

	node()
	{
		qtd = val = 0;
		for(int i = 0; i < S; i++) prox[i] = NULL;
	}

	void Insert(int number) // Insert a new number
	{
		node *curr = this;

		for(int i=N-1;i>=0;--i)
		{
			bool bit = (number & (1<<i));

			if(curr->prox[bit] == NULL)
				curr->prox[bit] = new node();

			curr->qtd++;
			curr = curr->prox[bit];
		}

		curr->qtd++;
		curr->val = number;
	}

	void Remove(int number) // Remove a number
	{
		node *curr = this;

		for(int i=N-1;i>=0;--i)
		{
			bool bit = number & (1<<i);

			curr->qtd--;
			curr = curr->prox[bit];
		}

		curr->qtd--;
	}

	int query(int number) // max xor with this number
	{
		node *curr = this;

		for(int i=N-1;i>=0;--i)
		{
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

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int n;
	cin>>n;
	tree->Insert(0);

	while(n--)
	{
		char t;
		int x;
		cin>>t>>x;

		if(t == '+')
			tree->Insert(x);
		else if(t == '-')
			tree->Remove(x);
		else		
			cout<<tree->query(x)<<"\n";		
	}
}