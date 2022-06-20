#include<bits/stdc++.h>
using namespace std;


class graph
{
private:
    int no_vertices,no_edges;
    int *parent;

    vector<int> *Vlist;
    vector<int> *WeightList;

public:
    //vector<string> vertexMap;
    graph();
    graph(int n);
    void addEdge(int v1, int v2, int weight);
    int getEdge(int u, int v);
    int changeEdgeW(int u, int v, int newW);
    void bfs(int start);
    vector<int> dfs(int start);
    void print_adjList();
    bool eliminated(int out_edge);
};

graph::graph(int n)
{

    no_vertices = n;
    no_edges = 0;
    Vlist = new vector<int>[no_vertices];
    WeightList = new vector<int>[no_vertices];
    parent= new int[n];

    ///vertexMap.resize(n);
    ///visited.resize(no_vertices,false); ///dfs function
}
void graph::addEdge(int v1, int v2, int weight)
{
    if(v1>=0 && v2>=0 && v1<no_vertices && v2<no_vertices)
    {
        Vlist[v1].push_back(v2);
        WeightList[v1].push_back(weight);
        no_edges++;
    }
}
void graph::print_adjList()
{
    for(int i=0; i<no_vertices; i++)
    {
        cout<<i<<": ";
        for(int j=0; j<Vlist[i].size(); j++)
        {
            cout<<Vlist[i][j]<<"("<<WeightList[i][j]<<") ";
        }
        cout<<endl;
    }
}

int graph::getEdge(int u, int v)
{
    for(int i=0; i<Vlist[u].size(); i++)
    {
        int adj_vert = Vlist[u][i];
        if(adj_vert==v)
            return WeightList[u][i];
    }
}
int graph::changeEdgeW(int u, int v, int newW)
{
    for(int i=0; i<Vlist[u].size(); i++)
    {
        int adj_vert = Vlist[u][i];
        if(adj_vert==v)
            WeightList[u][i] = newW;
    }
}

void graph::bfs(int start)
{
    vector<bool> visited(no_vertices, false);
    for(int i=0; i<no_vertices; i++)
    {
        parent[i]=-1;
    }
    queue<int> bfs_que;
    bfs_que.push(start);
    visited[start] = true;
    while(!bfs_que.empty())
    {
        int present_vert = bfs_que.front();
        bfs_que.pop();
        for(int i=0; i<Vlist[present_vert].size(); i++)
        {
            int adj_vert = Vlist[present_vert][i];
            int adj_vert_w = getEdge(present_vert, adj_vert);
            if(!visited[adj_vert] && adj_vert_w>0)
            {
                parent[adj_vert] = present_vert;
                visited[adj_vert] = true;
                bfs_que.push(adj_vert);
            }
        }
    }

}

bool graph::eliminated(int out_edge)
{
    int sink = no_vertices-1;
    int max_flow=0;
    while(1)
    {

        bfs(0);

        if(parent[sink]==-1) break;
        else if(parent[sink]!=-1)
        {
            int present = sink;
            int minimum_cap = 999999;
            while(1)
            {
                //cout<<present<<" ";
                int a = getEdge(parent[present], present);
                //cout<<parent[present]<<" "<<present<<" "<<a<<endl;
                if(a<minimum_cap) minimum_cap=a;
                present=parent[present];
                if(present==0) break;
            }
            present = sink;
            while(1)
            {
                int a = getEdge(parent[present], present);
                a = a-minimum_cap;
                changeEdgeW(parent[present], present, a);
                present=parent[present];

                if(present==0) break;

            }
            max_flow+=minimum_cap;
        }
        //print_adjList();
    }
    //cout<<max_flow<<endl;
    if(out_edge!=max_flow) return true;
    else return false;
}


int main()
{
    int n;
    cin>>n;

    string team_names[n];
    int team_idx[n] ={-1};
    int wlr[n][3];
    int most_wins=-1;
    int most_wins_team = -1;
    int vs_games[n][n];


    for(int i=0; i<n; i++)
    {
        cin>>team_names[i];

        cin>>wlr[i][0];
        if(wlr[i][0]>most_wins) {
            most_wins=wlr[i][0];
            most_wins_team=i;
        }
        cin>>wlr[i][1];
        cin>>wlr[i][2];
        for(int j=0; j<n; j++)
        {
            cin>>vs_games[i][j];
        }
    }
    int x = 1+ ((n-1)*(n-2)/2) + (n-1) + 1;

    bool flag = false; ///true if eliminated
    for(int k=0; k<n; k++){
        int reason = 0;
        int max_wins_possible = wlr[k][0]+wlr[k][2];
        if(max_wins_possible<most_wins){
                flag=true;
                reason=1;
        }

        if(flag==false){
            int out_edge=0;
            graph bb_elim(x);
            int games = ((n-1)*(n-2))/2;
            int vertex_count=1;
            for(int i=0; i<n; i++)
            {
                if(i!=k){
                    team_idx[i]=vertex_count;
                    vertex_count++;
                    int can_win = wlr[k][0]+wlr[k][2]-wlr[i][0];
                    bb_elim.addEdge(team_idx[i],x-1,can_win);
                }

            }
            for(int i=0; i<n; i++)
            {
                for(int j=i+1; j<n; j++)
                {
                    if(i!=k && j!=k)
                    {
                        int tot_match = vs_games[i][j];
                        bb_elim.addEdge(0, vertex_count, tot_match);
                        out_edge+=tot_match;
                        bb_elim.addEdge(vertex_count,team_idx[i], 999999);
                        bb_elim.addEdge(vertex_count,team_idx[j], 999999);
                        vertex_count++;
                    }
                }
            }
            flag = bb_elim.eliminated(out_edge);
        }
        if(flag==true)
        {
            cout<<team_names[k]<<" is eliminated!"<<endl;
        }
        if(reason==1)
        {
            cout<<"They can win at most "<<wlr[k][0]<<" + "<<wlr[k][2]<<" = "<<wlr[k][0]+wlr[k][2]<<" games"<<endl;
            cout<<team_names[most_wins_team]<<" has won a total of "<<most_wins<<" games "<<endl;

        }
        cout<<endl;
        flag=false;

    }
    //bb_elim.print_adjList();

}
