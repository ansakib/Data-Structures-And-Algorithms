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

void graph::print_adjList()
{
    for(int i=0; i<no_vertices; i++)
    {
        for(int j=0; j<adjList[i].size(); j++)
        {
            cout<<adjList[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    int no_cities, no_roads, no_locations, no_friends, no_pieces, collected_pieces;
    cin>>no_cities>>no_roads>>no_locations>>no_friends;
    no_pieces = 0;
    collected_pieces = 0;
    int pieces_info[no_cities] = {0};
    int start_idx[no_friends];
    int collection[no_friends] = {0};
    graph mamaland(no_cities);
    for(int i=0; i<no_roads; i++)
    {
        int c1, c2;
        cin>>c1>>c2;
        mamaland.addEdge(c1, c2);
    }
    for(int i=0; i<no_locations; i++)
    {
        int city, pieces;
        cin>>city>>pieces;
        pieces_info[city] = pieces;
        no_pieces+=pieces;
    }
    for(int i=0; i<no_friends; i++)
    {
        int city, frnd;
        cin>>city>>frnd;
        start_idx[frnd] = city;
    }


    for(int i=0; i<no_friends; i++)
    {
        vector<int> bfs_trav = mamaland.bfs(start_idx[i]);
        for(int j=0; j<bfs_trav.size(); j++)
        {
            collection[i] += pieces_info[bfs_trav[j]];
            pieces_info[bfs_trav[j]] = 0;
        }
        collected_pieces += collection[i];
    }


    ofstream output_file;
    output_file.open("Output_bfs.txt");
    if(collected_pieces!=no_pieces)
    {
        output_file<<"Mission Impossible"<<endl;
    }
    else
    {
        output_file<<"Mission Accomplished"<<endl;
    }

    output_file<<collected_pieces<<" out of "<<no_pieces<<" are collected."<<endl;
    for(int i=0; i<no_friends; i++)
    {
        output_file<<i<<" collected "<<collection[i]<<" pieces"<<endl;
    }
    output_file.close();
}
