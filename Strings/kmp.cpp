#include<bits/stdc++.h>// Knuth-Morris-Pratt (KMP) Algorithm
#define N 3000100	  // Find all the occurrences of wordS" inside text "B" with complexity O(|A| + |B|)
using namespace std; // Leonardo Su 

int prefix[N];

void kmp(string a,string b) //find string "a" in "b"
{
	string s = a + "#" + b;
	int n = s.size();
	prefix[0] = 0;
	int j = 0;

	for(int i = 1;i<n;++i)
	{
		while(j > 0 && (s[j] != s[i]))
			j = prefix[j-1];

		if(s[j] == s[i])
			prefix[i] = j + 1,j++;
	}
}

void reset()
{
	for(int i=0;i<N;++i) prefix[i] = 0;
}

int n,t;
vector<int>ans;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin>>t;
	string x,y,xx;
	bool flag = false;

	while(t--)
	{
		if(flag) cout<<"\n";
		flag = true;

		cout<<"Say the word and text:\n";
		cin>>y>>x; 
		
		int l = y.size() , r = x.size();

		reset(); ans.clear();
		kmp(y,x); 

		for(int i=0;i<l+r+1;i++) // if the prefix[i] == y.size()
		{						// thus finded y in x
			if(prefix[i] == l) // save the position on 'ans'
				ans.push_back(i-l);
		}

		
		cout<<"Find '"<<y<<"' "<<ans.size()<<" times on "<<x<<"\n";
		cout<<"In the positions:\n";
		
		for(int i=0;i<ans.size();++i) //position of the match
			cout<<ans[i] - l + 1<<" ";
		cout<<"\n";
	}
}