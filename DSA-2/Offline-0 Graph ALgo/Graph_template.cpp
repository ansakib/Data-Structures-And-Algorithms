#include<bits/stdc++.h>
using namespace std;

class graph
{
private:
    int no_vertices;
    vector<int> *adjList;

public:
    graph();
    graph(int n);
    void addEdge(int v1, int v2);
    vector<int> bfs(int start);
    vector<int> dfs(int start);
    bool bipartiteCheck(int src);
    bool bipartiteutil(int src, int colorArr[]);
    void print_adjList();
};

graph::graph()
{
    no_vertices = 0;
    adjList = new vector<int>[0];
}
graph::graph(int n)
{
    no_vertices = n;
    adjList = new vector<int>[n];
    ///visited.resize(no_vertices,false); ///dfs function
}
void graph::addEdge(int v1, int v2)
{
    if(v1>=0 && v2>=0 && v1<no_vertices && v2<no_vertices)
    {
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
    }
    else
    {
        cout<<"out of bounds"<<endl;
    }
}

vector<int> graph::bfs(int start)
{
    vector<bool> visited(no_vertices, false);
    vector<int> visiting_order;
    queue<int> bfs_que;
    bfs_que.push(start);
    visiting_order.push_back(start);
    visited[start] = true;
    while(!bfs_que.empty())
    {
        int present_vert = bfs_que.front();
        bfs_que.pop();
        for(int i=0; i<adjList[present_vert].size(); i++)
        {
            int adj_vert = adjList[present_vert][i];
            if(!visited[adj_vert])
            {
                visited[adj_vert] = true;
                visiting_order.push_back(adj_vert);
                bfs_que.push(adj_vert);
            }
        }
    }
    return visiting_order;
}

/*
vector<int> graph::dfs(int start)
{
    visited[start] = true;
    visiting_order.push_back(start);
    for(int i=0; i<adjList[start].size(); i++)
    {
        int adj_vert = adjList[start][i];
        if(!visited[adj_vert])
        {
            dfs(adj_vert);
        }
    }
    return visiting_order;
}
*/


bool graph::bipartiteCheck(int src) ///"-1" = noColor, "1" = 1st Color, "0" = 2nd Color
{
    int colorArr[no_vertices];
    for(int i=0; i<no_vertices; i++) colorArr[i] = -1;
    for(int i=0; i<no_vertices; i++)
    {
        if(colorArr[i]== -1)
        {
            if(bipartiteutil(src, colorArr)==false)
                return false;
        }
    }
    return true;

}
bool graph::bipartiteutil(int src, int colorArr[])
{
    colorArr[src] = 1;
    queue<int> bfs_que;
    bfs_que.push(src);
    while(!bfs_que.empty())
    {
        int present_vert = bfs_que.front();
        bfs_que.pop();

        for(int i=0; i<adjList[present_vert].size(); i++)
        {
            int adj_vert = adjList[present_vert][i];
            if(colorArr[adj_vert]==-1)
            {
                colorArr[adj_vert] = 1-colorArr[present_vert];
                bfs_que.push(adj_vert);
            }
            else if(colorArr[adj_vert] == colorArr[present_vert])
            {
                return false;
            }
        }
    }
    return true;
}


void graph::print_adjList()
{
    for(int i=0; i<no_vertices; i++)
    {
        cout<<i<<": ";
        for(int j=0; j<adjList[i].size(); j++)
        {
            cout<<adjList[i][j]<<" ";
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
        int u, v;
        cin>>u>>v;
        gg.addEdge(u,v);
    }
    cout<<gg.bipartiteCheck(0);


}

