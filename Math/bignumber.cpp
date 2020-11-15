/*
	Leonardo Su
	Ainda falta implementar a divisão de dois bignumbers.
*/
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> bignum;
typedef long long int ll;

//Imprime um big number.
void print(bignum a)
{
	if(a.empty())
	{
		cout<<0;
		return;
	}

	if(a.back() == -1)
		cout<<"-";
	else
		cout<<a.back();

	for(int i=a.size()-2; i>=0; --i)
		cout<<a[i];
}

//Remove os zeros a esquerda do big number.
void removeZeros(bignum &a)
{
	while(a.size() > 1 && a.back() == 0)
		a.pop_back();	
}

//Converte uma string para um big number.
void StringToBignum(string num, bignum &c)
{	
	c.clear();
	for(int i = num.size()-1; i>=0; --i)
		c.push_back((int)(num[i] - '0'));
}

//Retorna se a < b
bool menor(bignum a, bignum b) 
{
	removeZeros(a); 
	removeZeros(b);

	if(a.size() != b.size()) 
		return a.size() < b.size();

	for(int i=a.size()-1;i>=0;--i) 
		if(a[i] != b[i]) 
			return a[i] < b[i];	
	return false;
}

/*
	Método de multiplicação de escola primária (Método trivial).
	c = a*b
	Complexidade O(size(a)*size(b)) ≌ O(N²)
*/
void multiplica(bignum a, bignum b, bignum &c)
{
	int n = a.size() + b.size();
	c.resize(n);	

	if(a.size() > b.size())
		swap(a,b);

	ll carry = 0LL,prod;
	for(int i=0;i<(int)a.size();++i)
	{

		carry = 0LL;
		for(int j=0;j<(int)b.size();++j)
		{
			prod = a[i]*1LL*b[j] + carry;
			carry = prod/10LL;
			c[i + j] += prod%10;			
		}

		c[i + (int)b.size()] += carry;		
	}

	carry = 0LL;
	removeZeros(c);

	for(int i=0;i<n;++i)
	{
		c[i] += carry;
		carry = c[i]/10LL;
		c[i] = c[i]%10;
	}

	removeZeros(c);
}

/*
	Soma de dois big number.
	c = a + b
	Complexidade O(max(size(a),size(b))) ≌ O(N)
*/
void adiciona(bignum a,bignum b,bignum &c)
{	
	int n = max(a.size(),b.size());
	int carry = 0,res;
	c.resize(n);

	int x,y;
	for(int i=0;i<n;++i)
	{
		x = (i < (int)a.size() ) ? a[i] : 0;
		y = (i < (int)b.size() ) ? b[i] : 0;
		res = x + y + carry;
		carry = res/10;
		c[i] = res%10;
	}

	if(carry)
		c.push_back(carry);

	removeZeros(c);
}

/*
	Subtração de dois big number, onde c pode ser negativo.
	c = a - b
	Complexidade O(max(size(a),size(b))) ≌ O(N)
*/
void subtrai(bignum a,bignum b,bignum &c)
{
	bool neg = false;
	if(menor(a,b))
	{
		neg = true;
		swap(a,b);
	}

	int n = max(a.size(),b.size());
	c.resize(n);

	int carry = 0,res;	
	int x,y;
	for(int i=0;i<n;++i)
	{
		x = (i < (int)a.size()) ? a[i] : 0;
		y = (i < (int)b.size()) ? b[i] : 0;
		res = x - y - carry;

		carry = 0;
		if(res < 0)
		{
			carry = 1;
			res += 10;
		}

		c[i] = res;
	}	

	removeZeros(c);
	if(neg)
		c.push_back(-1);
}


/*
	Ainda a ser implementado.
*/
void divisao(bignum a,bignum b,bignum &c)
{

}

int main()
{
	string s1,s2,op;

	while(cin>>s1>>op>>s2 && s1 != "s")
	{
		bignum a,b,c;
		StringToBignum(s1,a);
		StringToBignum(s2,b);
		if(op == "+")
			adiciona(a,b,c);
		else if(op == "-")
			subtrai(a,b,c);
		else if(op == "*")
			multiplica(a,b,c);
		else
			cout<<"sem divisao\n";		

		op = " " + op + " ";

		cout<<s1<<op<<s2<<" = ";
		print(c);
		cout<<"\n";
	}
}