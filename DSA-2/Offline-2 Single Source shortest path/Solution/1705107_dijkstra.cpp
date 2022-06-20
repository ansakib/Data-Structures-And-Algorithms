#include<bits/stdc++.h>
using namespace std;


/// Priority Queue ///

struct graphNode
{
    int idx;
    int distance;
    int parent;
};

class minPQ
{
    int maxs, sizee;
    graphNode **qu;
    int *idxTracker;
    int leftC(int idx);
    int rightC(int idx);
    int parent(int idx);
    void minHeapify(int idx);
public:
    minPQ(int maxsz);
    void push(graphNode *node);
    bool isEmpty();
    graphNode* extractMin();
    int getIdx(int idx_node);
    void decreaseKey(int idx, int val);
};
minPQ::minPQ(int maxsz)
{
    maxs = maxsz;
    sizee = 0;
    idxTracker = new int[maxs];
    qu = new graphNode*[maxs+1];
}
int minPQ::getIdx(int idx_node)
{
    return idxTracker[idx_node];
}
int minPQ::leftC(int idx)
{
    return idx*2;
}
int minPQ::rightC(int idx)
{
    return idx*2+1;
}
int minPQ::parent(int idx)
{
    return idx/2;
}
void minPQ::minHeapify(int idx)
{
    int left = leftC(idx);
    int right = rightC(idx);
    int small = idx;
    if(left<=sizee && qu[left]->distance < qu[small]->distance)
        small = left;
    if(right<=sizee && qu[right]->distance < qu[small]->distance)
        small = right;
    if(small!=idx)
    {
        ///swap them
        graphNode* temp;
        temp = qu[small];
        qu[small] = qu[idx];
        idxTracker[qu[small]->idx] = small;
        qu[idx] = temp;
        idxTracker[qu[idx]->idx] = idx;

        minHeapify(small);
    }
}
void minPQ::decreaseKey(int idx, int val)
{
    qu[idx]->distance = val;
    int present = idx;
    while(present>1 && qu[parent(present)]->distance > qu[present]->distance)
    {
        ///swap present node with parent
        graphNode *temp;
        temp = qu[present];
        qu[present] = qu[parent(present)];
        idxTracker[qu[present]->idx] = present;
        qu[parent(present)]=temp;
        idxTracker[qu[parent(present)]->idx] = parent(present);

        present = parent(present);
    }
}
void minPQ::push(graphNode *node)
{
    sizee++;
    qu[sizee] = node;
    int present = sizee;
    idxTracker[node->idx] = sizee;
    while(present>1 && qu[parent(present)]->distance > qu[present]->distance)
    {
        ///swap present node with parent
        graphNode *temp;
        temp = qu[present];
        qu[present] = qu[parent(present)];
        idxTracker[qu[present]->idx] = present;
        qu[parent(present)]=temp;
        idxTracker[qu[parent(present)]->idx] = parent(present);

        present = parent(present);
    }
}
bool minPQ::isEmpty()
{
    if(sizee==0)
        return true;
    else
        return false;
}
graphNode* minPQ::extractMin()
{
    graphNode *minNode = qu[1];
    qu[1] = qu[sizee]; ///replace with the last element
    idxTracker[qu[1]->idx] =1;
    sizee--;
    minHeapify(1);
    return minNode;
}


class graph
{
private:
    int no_vertices, no_edges;
    vector<int> *Vlist;
    vector<int> *WeightList;
    void relax_dijkstra(graphNode *init, graphNode *finl, int weight, minPQ &prQ);
    //vector<bool> visited; ///dfs function
    //vector<int> visiting_order; ///dfs function

public:
    graph();
    graph(int n);
    void addEdge(int v1, int v2, int weight);
    void dijkstra(int source, int destination);
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

void graph::dijkstra(int source, int destination)
{
    graphNode **gInfo = new graphNode*[no_vertices];
    minPQ prQ(no_vertices);
    for(int i=0; i<no_vertices; i++)
    {

        graphNode *tempNode = new graphNode;
        tempNode->idx = i;
        tempNode->parent = -1;
        tempNode->distance = 1000001;

        gInfo[i] = tempNode;

        gInfo[source]->distance = 0; ///src node distance is 0

        prQ.push(gInfo[i]); ///building priority queue
    }

    while(!prQ.isEmpty())
    {
        graphNode *present_node = prQ.extractMin();
        int present = present_node->idx;
        for(int i=0; i<Vlist[present].size(); i++)
        {
            graphNode *adjNode = gInfo[Vlist[present][i]];
            int weight = WeightList[present][i];
            relax_dijkstra(present_node, adjNode, weight, prQ);

        }

    }

    cout<<"Using Dijkstra Algo: "<<endl;
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
            break;
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

void graph::relax_dijkstra(graphNode *init, graphNode *finl, int weight, minPQ &prQ)
{
    int new_weight = init->distance + weight;
    if(finl->distance > new_weight)
    {
        finl->parent = init->idx;
        finl->distance = new_weight;
        int adj_idx = prQ.getIdx(finl->idx);
        prQ.decreaseKey(adj_idx, new_weight);
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
    gg.dijkstra(source,dest);

}


