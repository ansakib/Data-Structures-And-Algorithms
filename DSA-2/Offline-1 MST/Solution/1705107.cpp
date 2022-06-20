#include<bits/stdc++.h>
using namespace std;

/// Disjoint Set ///

struct Node
{
    int value;
    int parent;
    int raank;
};

class dis_set
{
    int maxSize;
    Node *nodes;

public:
    dis_set(int maxSize);
    void makeset(int value);
    int findset(int value);
    void unions(int u, int v);
    ~dis_set();
};

dis_set::dis_set(int maxSize)
{
    this->maxSize = maxSize;
    nodes = new Node[maxSize];
}

void dis_set::makeset(int value)
{
    Node V;
    V.value = value;
    V.parent = value;
    V.raank = 0;
    nodes[value] = V;
}
int dis_set::findset(int value)
{
    if(value!= nodes[value].parent)
    {
      nodes[value].parent = findset(nodes[value].parent); ///for path compression
    }
    return nodes[value].parent;
}
void dis_set::unions(int u, int v)
{
    int set_a = findset(u);
    int set_b = findset(v);

    if(set_a==set_b) return;
    if(nodes[set_a].raank<=nodes[set_b].raank)
    {
        nodes[set_a].parent = set_b;
    }
    else
    {
        nodes[set_b].parent = set_a;
    }
    if(nodes[set_a].raank==nodes[set_b].raank)
    {
        nodes[set_b].raank++;
    }
}
dis_set::~dis_set()
{
    delete [] nodes;
}


/// Priority Queue ///

struct queueNode
{
    int idx;
    double value;
    int parent;
};

class minPQ
{
    int maxs, sizee;
    queueNode **qu;
    int *idxTracker;
    int leftC(int idx);
    int rightC(int idx);
    int parent(int idx);
    void minHeapify(int idx);
    void decreaseKeyEngine(int idx, double val);
public:
    minPQ(int maxsz);
    void push(queueNode *node);
    bool isEmpty();
    queueNode* extractMin();
    void decreaseKey(int idx, double val);
};
minPQ::minPQ(int maxsz)
{
    maxs = maxsz;
    sizee = 0;
    idxTracker = new int[maxs];
    qu = new queueNode*[maxs+1];
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
    if(left<=sizee && qu[left]->value < qu[small]->value)
        small = left;
    if(right<=sizee && qu[right]->value < qu[small]->value)
        small = right;
    if(small!=idx)
    {
        ///swap them
        queueNode* temp;
        temp = qu[small];
        qu[small] = qu[idx];
        idxTracker[qu[small]->idx] = small;
        qu[idx] = temp;
        idxTracker[qu[idx]->idx] = idx;

        minHeapify(small);
    }
}
void minPQ::decreaseKeyEngine(int idx, double val)
{
    qu[idx]->value = val;
    int present = idx;
    while(present>1 && qu[parent(present)]->value > qu[present]->value)
    {
        ///swap present node with parent
        queueNode *temp;
        temp = qu[present];
        qu[present] = qu[parent(present)];
        idxTracker[qu[present]->idx] = present;
        qu[parent(present)]=temp;
        idxTracker[qu[parent(present)]->idx] = parent(present);

        present = parent(present);
    }
}
void minPQ::push(queueNode *node)
{
    sizee++;
    qu[sizee] = node;
    int present = sizee;
    idxTracker[node->idx] = sizee;
    while(present>1 && qu[parent(present)]->value > qu[present]->value)
    {
        ///swap present node with parent
        queueNode *temp;
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
queueNode* minPQ::extractMin()
{
    queueNode *minNode = qu[1];
    qu[1] = qu[sizee]; ///replace with the last element
    idxTracker[qu[1]->idx] =1;
    sizee--;
    minHeapify(1);
    return minNode;
}
void minPQ::decreaseKey(int idx, double val)
{
    int i = idxTracker[idx];
    decreaseKeyEngine(i, val);
}


/// Graph Class ///

class edge
{
public:
    int v1,v2;
    double weight;
    edge(int v1, int v2, double weight)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->weight = weight;
    }
};

bool comp(edge v1, edge v2)
{

    return v1.weight<v2.weight;
}

class graph
{
private:
    int no_vertices;
    vector<vector<edge > > adjList;

public:
    graph();
    graph(int n);
    void addEdge(int v1, int v2, int weight);
    double kruskalAlgo();
    double primsAlgo();
    void print_adjList();
};

graph::graph()
{
    no_vertices = 0;
}
graph::graph(int n)
{
    no_vertices = n;
    adjList.resize(n);
}
void graph::addEdge(int v1, int v2, int weight)
{
    if(v1>=0 && v2>=0 && v1<no_vertices && v2<no_vertices)
    {
        adjList[v1].push_back(edge(v1,v2,weight));
        adjList[v2].push_back(edge(v2,v1,weight));
    }
    else
    {
        cout<<"out of bounds"<<endl;
    }
}

double graph::kruskalAlgo()
{
    if(no_vertices==0) return 0;

    double cost = 0;
    dis_set krusk_set(no_vertices);
    for(int i=0; i<no_vertices; i++)
    {
        krusk_set.makeset(i);
    }

    vector<edge> sorted_edges;
    for(int i=0; i<no_vertices; i++)
    {
        for(int j=0; j<adjList[i].size(); j++)
        {
            sorted_edges.push_back(adjList[i][j]); ///adjlist[i][j] edge type er element
        }
    }
    sort(sorted_edges.begin(), sorted_edges.end(), comp);
    vector<edge> solutionEdges;

    for(int i=0; i<sorted_edges.size();i++)
    {
        int v1, v2;
        double weight;
        v1 = sorted_edges[i].v1;
        v2 = sorted_edges[i].v2;
        weight = sorted_edges[i].weight;
        if(krusk_set.findset(v1)!=krusk_set.findset(v2))
        {
            krusk_set.unions(v1,v2);
            solutionEdges.push_back(sorted_edges[i]);
            cost=cost+weight;
        }
    }

    cout<<"List of edges selected by Kruskals: { ";
    for(int i=0; i<solutionEdges.size();i++)
    {
        cout<<"("<<solutionEdges[i].v1<<","<<solutionEdges[i].v2<<") ";
    }
    cout<<"}"<<endl;
    return cost;

}

double graph::primsAlgo()
{
    if(no_vertices==0) return 0;
    double cost = 0;
    int flag[no_vertices]; ///flag=0 means vertex is in queue else in solve
    for(int i=0; i<no_vertices; i++)
    {
        flag[i] = 0;
    }

    queueNode **Vlist = new queueNode*[no_vertices];
    for(int i=0; i<no_vertices; i++)
    {
        queueNode *temp = new queueNode;
        temp->idx = i;
        temp->value = 99999;
        temp->parent = -1;
        Vlist[i] = temp;
    }
    Vlist[0]->value = 0;

    minPQ prQ(no_vertices);
    for(int i=0; i<no_vertices; i++)
    {
        prQ.push(Vlist[i]); ///all vertex are in priority queue
    }
    while(!prQ.isEmpty())
    {
        queueNode *minNode = prQ.extractMin();
        int u= minNode->idx;
        for(int i=0; i<adjList[u].size(); i++)
        {
            int v = adjList[u][i].v2;
            double weight = adjList[u][i].weight;
            if(flag[v]==0 && weight < Vlist[v]->value)
            {
                Vlist[v]->parent = u;
                prQ.decreaseKey(v, weight);
            }
        }
        flag[u] = 1;
    }

    vector <edge> solutionEdges;
    for(int i=0; i<no_vertices; i++)
    {
        if(Vlist[i]->parent!= -1)
        {
            int v1 = Vlist[i]->idx;
            int v2 = Vlist[i]->parent;
            double weight = Vlist[i]->value;
            cost = cost+weight;
            solutionEdges.push_back(edge(v1,v2, weight));
        }
    }
    cout<<"List of edges selected by Prims: { ";
    for(int i=0; i<solutionEdges.size();i++)
    {
        cout<<"("<<solutionEdges[i].v1<<","<<solutionEdges[i].v2<<") ";
    }
    cout<<"}"<<endl;
    return cost;
}

void graph::print_adjList()
{
    for(int i=0; i<no_vertices; i++)
    {
        cout<<i<<"- ";
        for(int j=0; j<adjList[i].size();j++)
        {
            cout<<j<<" ";
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
        double weight;
        cin>>u>>v>>weight;
        gg.addEdge(u,v,weight);
    }
    double k_cost = gg.kruskalAlgo();
    double p_cost = gg.primsAlgo();
    cout<<"Cost of the minimum spanning tree : (Kruskal-> "<<k_cost<<") and (Prims-> "<<p_cost<<")"<<endl;

}


