#include <stdio.h>
/*
	The Algorithm of Kruskal totally in C 
    Leonado Su
    Kruskal complexity O(M.Log(N)) :D , when M is the number Edges and N is the number of vertice
*/
void makeset(int x, int p[], int rank[]) //initializes
{
    p[x] = x;
    rank[x] = 0;
}

void link(int x,int y, int p[], int rank[]) // united the vertice "X" with "Y"
{
    if(rank[x]>rank[y])
        p[y]=x;
    
    else
        p[x]=y;
    
    if(rank[x]==rank[y])
        rank[y]=rank[y]+1;    
}

int findset(int x, int p[]) // the father of "X"
{
    if(x!=p[x])
        p[x]= findset(p[x], p);    
    return (p[x]);
}

void uni(int x,int y, int p[], int rank[])
{
    link(findset(x,p),findset(y,p), p, rank);
}

typedef struct
{
    int custo;
    int e1;
    int e2;
} Aresta;

void merge(Aresta a[], int ini, int fim)
{
	Aresta aux[fim - ini + 1];
	int meio = (ini + fim)/2;
	int k = 0;
	int i = ini;
	int j = meio + 1;

	while((i<=meio)&&(j<=fim))
	{
		if(a[i].custo <= a[j].custo)
		{
			aux[k]=a[i];
			k++;
			i++;
		}
		else
		{
			aux[k]=a[j];
			k++;
			j++;
		}
	}

	while(i<=meio)
	{
		aux[k]=a[i];
		k++;
		i++;
	}

	while(j<=fim)
	{
		aux[k]=a[j];
		k++;
		j++;
	}

	for(k=0;k<=fim-ini;k++)
		a[ini+k]=aux[k];	
}

void mergesort(Aresta a[], int ini, int fim) // Mergesort O(N.Log(N))
{
	if(ini!=fim)
	{
		int meio = (ini+fim)/2;
		mergesort(a,ini,meio);
		mergesort(a,meio+1,fim);
		merge(a,ini,fim);
	}
}

int main()
{
    int N,M; // number of Vertices and Edges
    int custo = 0; // The answer

    scanf("%d %d",&N,&M); // Read the input

    int rank[N+1];  int repre[N+1]; // "rank" save the level and "repre" save the father of vertice
    Aresta k[M];  // "k" save the Edges

    for(int i=0;i<M;i++) // Read the Edges
    {
        scanf("%d %d %d",&k[i].e1,&k[i].e2,&k[i].custo); // (a,b,c) when "e1" and "e2" are the vertice with cost "custo"
    }

    for(int i=1;i<=N;i++) // make the set
    {
        makeset(i,repre,rank);
    }

    mergesort(k,0,M); // Sort the edges

    for(int i=0;i<M;i++) // For each edge ,Look if the vertice (e1 and e2) are united
    {
        if(findset(k[i].e1,repre) != findset(k[i].e2,repre)) // if the father aren't same,they unite
        {
            custo+=k[i].custo; // custo save the cost to build the MST 
            uni(findset(k[i].e1,repre),findset(k[i].e2,repre),repre,rank); // unite they
        }
    }

    printf("%d\n",custo); // print the answer

 return 0;
}