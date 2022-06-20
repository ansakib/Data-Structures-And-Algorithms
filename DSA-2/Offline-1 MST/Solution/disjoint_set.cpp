#include <iostream>
using namespace std;

struct Node
{
    int Data, Parent, Rank;
};

class Set
{
    int MaxSize;
    Node **nodes;
public:
    Set(int MaxSize);
    void MakeSet(int x);
    int FindSet(int x);
    void Union(int u, int v);
    void Print(int u);
    ~Set();
};

Set::Set(int MaxSize)
{
    this->MaxSize = MaxSize;
    nodes = new Node*[MaxSize];
    for( int i=0; i<=MaxSize-1; i++ ) nodes[i] = NULL;
}

void Set::MakeSet(int x)
{
    Node *node;
    node = new Node;
    node->Data = x;
    node->Parent = x;
    node->Rank = 0;
    nodes[x] = node;
}

int Set::FindSet(int x)
{
    if( nodes[x]->Data != nodes[x]->Parent )
    {
        nodes[x]->Parent = FindSet( nodes[x]->Parent );
    }
    return nodes[x]->Parent;
}

void Set::Union(int u, int v)
{
    int firstSet = FindSet(u);
    int secondSet = FindSet(v);

    if( firstSet == secondSet ) return;

    if( nodes[firstSet]->Rank > nodes[secondSet]->Rank )
    {
        nodes[secondSet]->Parent = firstSet;
    }
    else
    {
        nodes[firstSet]->Parent = secondSet;
    }

    if( nodes[firstSet]->Rank == nodes[secondSet]->Rank )
    {
        nodes[secondSet]->Rank = nodes[secondSet]->Rank + 1;
    }
}

void Set::Print(int u)
{
    int root = FindSet(u);
    for( int i=0; i<=MaxSize-1; i++ )
    {
        if( nodes[i] != NULL && FindSet( nodes[i]->Data ) == root )
        {
            cout << nodes[i]->Data << " ";
        }
    }
    cout << "\n";
}

Set::~Set()
{
    for( int i=0; i<=MaxSize-1; i++ )
    {
        if( nodes[i] != NULL )
        {
            delete nodes[i];
        }
    }
    delete[] nodes;
}

int main()
{
    cout << "Enter Max Size: ";
    int MaxSize;
    cin >> MaxSize;
    Set mySet(MaxSize);
    while( true )
    {
        int choice;
        cout << "1. Make Set\n";
        cout << "2. Find Set\n";
        cout << "3. Union\n";
        cout << "4. Print Set\n";
        cout << "5. Quit\n";
        cout << "\tYour Choice: ";
        cin >> choice;

        if( choice == 1 )
        {
            cout << "Enter element: ";
            int x;
            cin >> x;
            mySet.MakeSet(x);
        }
        else if( choice == 2 )
        {
            cout << "Enter element: ";
            int x;
            cin >> x;
            int parent = mySet.FindSet(x);
            cout << x << " is in set : " << parent << "\n";
        }
        else if( choice == 3 )
        {
            int u, v;
            cout << "Enter first element: ";
            cin >> u;
            cout << "Enter second element: ";
            cin >> v;
            mySet.Union(u, v);
        }
        else if( choice == 4 )
        {
            cout << "Enter element: ";
            int x;
            cin >> x;
            mySet.Print(x);
        }
        else if( choice == 5 )
        {
            break;
        }
        cout << "\n";
    }

    return 0;
}

