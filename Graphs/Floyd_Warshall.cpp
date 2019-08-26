#include <bits/stdc++.h>
/*
    Leonado Su
    Floyd_Warshall complexity O(N^3) :D
*/
#define MAXN 256 //Number of vertice
#define INF 0x1f1f1f1f //The max distance I can have
using namespace std;

int dist[MAXN][MAXN];
int n,m;
int a,b,d;

int main() // In this case, I want to find the shortest path
{
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin>>n>>m;
    memset (dist, 0x1f, sizeof(dist)); //set infinty the distance of edge "i" to "j"

    for(int i=1;i<=n;++i) // setup the distance for the vertice "i" to "i" to zero
        dist[i][i]=0;

    for(int i=0;i<m;++i) // Read the input
    {
        cin>>a>>b>>d;
        dist[a][b] = d; 
        dist[b][a] = d; //In this case,the graph is bidirectional
    }

    for(int k=1;k<=n;++k) // Why is O(N^3)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
            dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);

    //Now I know the minimum distance of the edge "i" to edge "j" in O(1)
}