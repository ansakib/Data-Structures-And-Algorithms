#include<bits/stdc++.h>
using namespace std;


struct graphNode
{
    int idx;
    int distance;
    int parent;
};


class graph
{
private:
    int no_vertices, no_edges;
    vector<int> *Vlist;
    vector<int> *WeightList;
    void relax_ford(graphNode *init, graphNode *finl, int weight);
    //vector<bool> visited; ///dfs function
    //vector<int> visiting_order; ///dfs function

public:
    graph();
    graph(int n);
    void addEdge(int v1, int v2, int weight);
    void bellman_ford(int source, int destination);
    void print_adjList();
};

graph::graph()
{
    no_vertices = 0;
    no_edges = 0;
    Vlist = new vector<int>[0];
    WeightList = new vector<int>[0];
}
graph::graph(int n)
{
    no_vertices = n;
    Vlist = new vector<int>[n];
    WeightList = new vector<int>[n];
    //visited.resize(no_vertices,false); ///dfs function
}
void graph::addEdge(int v1, int v2, int weight)
{
    if(v1>=0 && v2>=0 && v1<no_vertices && v2<no_vertices)
    {
        Vlist[v1].push_back(v2);
        WeightList[v1].push_back(weight);
        no_edges++;
    }
    else
    {
        cout<<"out of bounds"<<endl;
    }
}

void graph::bellman_ford(int source, int destination)
{
    graphNode **gInfo = new graphNode*[no_vertices];
    for(int i=0; i<no_vertices; i++)
    {
        graphNode *tempNode = new graphNode;
        tempNode->idx = i;
        tempNode->parent = -1;
        tempNode->distance = 100001;

        gInfo[i] = tempNode;

        gInfo[source]->distance = 0; ///src node distance is 0
    }
    for(int cnt=0; cnt<no_vertices-1; cnt++)
    {
        for(int i=0; i<no_vertices; i++)
        {
            for(int j=0; j<Vlist[i].size(); j++)
            {
                int adj_vertex = Vlist[i][j];
                int weight = WeightList[i][j];
                relax_ford(gInfo[i], gInfo[adj_vertex], weight);
            }
        }
    }
    cout<<"Using Bellman-Ford Algo: "<<endl;
    for(int i=0; i<no_vertices; i++)
    {
        for(int j=0; j<Vlist[i].size(); j++)
        {
            int old_weight = gInfo[Vlist[i][j]]->distance;
            int new_weight = WeightList[i][j] + gInfo[i]->distance;
            if(new_weight<old_weight)
            {
                cout<<"The graph contains a negative cycle."<<endl;
                return;
            }
        }
    }
    cout<<"The graph does not contain a negative cycle."<<endl;
    cout<<"Shortest path cost: "<< gInfo[destination]->distance<<endl;

    int present = destination;
    stack<int> path;
    path.push(destination);
    while(source!=present)
    {
        if(gInfo[present]->parent!=-1)
        {
            present= gInfo[present]->parent;
            path.push(present);
        }
        else
        {
            cout<<"NO PATH!"<<endl;
        }
    }
    cout<<path.top();
    path.pop();
    while(path.size()>0)
    {
        cout<<" -> "<<path.top();
        path.pop();
    }
}

void graph::relax_ford(graphNode *init, graphNode *finl, int weight)
{
    int new_weight = init->distance + weight;
    if(new_weight < finl->distance)
    {
        finl->distance = new_weight;
        finl->parent = init->idx;
    }
}


void graph::print_adjList()
{
    for(int i=0; i<no_vertices; i++)
    {
        cout<<i<<": ";
        for(int j=0; j<Vlist[i].size(); j++)
        {
            cout<<Vlist[i][j]<<" ";
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
    int source, dest;
    cin>>source>>dest;
    gg.bellman_ford(source, dest);

}

