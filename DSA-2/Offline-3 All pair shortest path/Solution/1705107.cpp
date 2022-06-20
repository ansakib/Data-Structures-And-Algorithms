#include<bits/stdc++.h>
using namespace std;
#define INF INT_MAX

class graph
{
private:
    int no_vertices;
    int **adj_matrix;

public:
    graph();
    graph(int n);
    void addEdge(int v1, int v2, int weight);
    void floyd_warshall();
    void print_adjList();
};

graph::graph()
{
    no_vertices = 0;
}
graph::graph(int n)
{
    no_vertices = n;
    adj_matrix = new int*[no_vertices+1];
    for(int i=0; i<=no_vertices; i++)
    {
        adj_matrix[i] = new int[no_vertices+1];
        for(int j=0; j<=no_vertices; j++)
        {
            if(i==0 || j==0 || i==j)
            {
                adj_matrix[i][j] = 0;
            }
            else
                adj_matrix[i][j] = INF;
        }
    }
}
void graph::addEdge(int v1, int v2, int weight)
{
    if(v1>0 && v2>0 && v1<=no_vertices && v2<=no_vertices)
    {
        adj_matrix[v1][v2] = weight;
    }
    else
    {
        cout<<"out of bounds"<<endl;
    }
}

void graph::floyd_warshall()
{
    int all_pair[no_vertices+1][no_vertices+1];
    for(int i=0; i<=no_vertices; i++)
    {
        for(int j=0; j<=no_vertices; j++)
        {
            all_pair[i][j] = adj_matrix[i][j];
        }
    }

    for(int cnt=1; cnt<=no_vertices; cnt++)
    {
        for(int i=1; i<=no_vertices; i++)
        {
            for(int j=1; j<=no_vertices; j++)
            {
                if(all_pair[i][cnt]!= INF && all_pair[cnt][j]!=INF && all_pair[i][cnt]+all_pair[cnt][j]<all_pair[i][j])
                {
                    all_pair[i][j] = all_pair[i][cnt]+all_pair[cnt][j];
                }
            }
        }
    }

    cout<<"Shortest distance matrix"<<endl;
    for(int i=1; i<=no_vertices; i++)
    {
        for(int j=1; j<=no_vertices; j++)
        {
            if(all_pair[i][j] == INF) cout<<"INF"<<"    ";

            else cout<<all_pair[i][j]<<"      ";
        }
        cout<<endl;
    }
}


void graph::print_adjList()
{
    for(int i=1; i<=no_vertices; i++)
    {
        cout<<i<<": ";
        for(int j=1; j<=no_vertices; j++)
        {
            if(adj_matrix[i][j] == INF) cout<<"INF"<<" ";

            else cout<<adj_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    int no_vertices, no_edges;
    cin>>no_vertices>>no_edges;
    graph gg(no_vertices);
    for(int i=0; i<no_edges; i++)
    {
        int u, v, w;
        cin>>u>>v>>w;
        gg.addEdge(u,v,w);
    }
    gg.floyd_warshall();


}

