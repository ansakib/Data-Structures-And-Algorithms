#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    int degree;
    Node *parent, *child, *sibling;
};

bool compar(const pair<int,int> &node1, const pair<int,int> &node2)
{
    return (node1.second < node2.second);
}

class bHeap
{
    list<Node*> heap;

    Node* treeUnion(Node *t1, Node *t2);
    list<Node*> heapUnion(list<Node*> &h1, list<Node*> &h2);
    Node* createNewNode(int data);
    Node* findNode(Node* node, int daata);
    //Node* findInTree(Node* node, int daata);
    void findLevels(Node* root,vector<pair<int, int > > &levelNodes, int level);
    void printEachTree(Node* node);

public:
    int findMax();
    int extractMax();
    void insertData(int data);
    void increaseKey(int old_data, int new_data);
    void print();
};



Node* bHeap::treeUnion(Node *t1, Node *t2)
{
    Node *small, *large;
    if(t1->data >= t2->data)
    {
        small = t2;
        large = t1;
    }
    else
    {
        small = t1;
        large = t2;
    }
    small->parent = large;
    small->sibling = large->child;
    large->child = small;

    large->degree++;

    return large;
}

list<Node*> bHeap::heapUnion(list<Node*> &h1, list<Node*> &h2)
{
    list<Node*>::iterator it1 = h1.begin();
    list<Node*>::iterator it2 = h2.begin();

    list<Node*> mergedHeap;


    while(it1!=h1.end() && it2!=h2.end())
    {
        if((*it1)->degree <= (*it2)->degree)
        {
            mergedHeap.push_back(*it1);
            it1++;
        }
        else
        {
            mergedHeap.push_back(*it2);
            it2++;
        }
    }


    while(it1!=h1.end())
    {
        mergedHeap.push_back(*it1);
        it1++;
    }


    while(it2!=h2.end())
    {
        mergedHeap.push_back(*it2);
        it2++;
    }


    if(mergedHeap.size()>1)
    {
        //cout<<"test: "<<(*mergedHeap.end())->data<<endl;
        list<Node*>::iterator left, current, right;

        left = mergedHeap.begin();
        current = left;
        current++;
        right = current;
        right++;


        while(current != mergedHeap.end())
        {
            if(right!=mergedHeap.end() && ((*left)->degree == (*current)->degree) && ((*current)->degree==(*right)->degree))
            {
                /// jokhon porpor 3ta node er degree soman hobe, just pass them
                //if(((*left)->degree == (*current)->degree) && ((*current)->degree==(*right)->degree))
                //{
                    left++;
                    current++;
                    right++;

                //}
            }
            else if((*left)->degree == (*current)->degree)
            {
                *left = treeUnion(*left, *current);
                mergedHeap.erase(current);
                current = right;
                right++;
            }
            else
            {
                left++;
                current++;
                right++;

            }
        }
    }

    return mergedHeap;
}


Node* bHeap::createNewNode(int data)
{
    Node* node = new Node;
    node->data = data;
    node->degree = 0;
    node->child = NULL;
    node->sibling = NULL;
    node->parent = NULL;

    return node;
}


int bHeap::findMax()
{
    list<Node*>:: iterator current;
    current = heap.begin();
    int max_data = (*current)->data;
    while(current!=heap.end())
    {
        int temp = (*current)->data;
        if(temp>max_data)
        {
            max_data = temp;
        }
        current++;
    }
    return max_data;
}

int bHeap::extractMax()
{
    list<Node*>::iterator current, max_node;
    current = heap.begin();
    max_node = current;
    int max_data = (*current)->data;
    while(current!=heap.end())
    {
        int temp = (*current)->data;
        if(temp>max_data)
        {
            max_data = temp;
            max_node = current;
        }
        current++;
    }

    list<Node*> mainHeap, ext_heap;
    current = heap.begin();
    while(current!=heap.end())
    {
        if(current!=max_node)
        {
            mainHeap.push_back(*current);
        }
        current++;
    }

    Node *child_max;
    child_max = (*max_node)->child;
    while(child_max)
    {
        Node *sibling_maxChild = child_max->sibling;
        child_max->parent = NULL;
        child_max->sibling = NULL; ///to reverse the order

        ext_heap.push_front(child_max);
        child_max = sibling_maxChild;
    }

    heap.clear();
    heap = heapUnion(mainHeap, ext_heap);

    return max_data;
}

Node* bHeap::findNode(Node* node, int daata)
{
    if(node==NULL) return NULL;

    if(node->data == daata)
    {
        return node;
    }


    Node* child = findNode(node->child, daata);
    if(child!=NULL)
    {
        return child;
    }
    //cout<<"here0: "<<node->data<<endl;
    return findNode(node->sibling, daata);
    //cout<<"here1: "<<node->data<<endl;
}

/*Node* bHeap::findInTree(Node* node, int daata)
{
    if(node->data == daata)
    {
        return node;
    }
    while(node)
    {
        findInTree(node->child, daata);
        node=node->sibling;
    }
}*/

void bHeap::insertData(int data)
{
    list<Node*> tempHeap;
    Node *newNode = createNewNode(data);
    tempHeap.push_back(newNode);
    cout<<"INSERTED "<<data<<endl;

    heap = heapUnion(heap, tempHeap);
}

void bHeap::increaseKey(int old_data, int new_data)
{
    Node* temp = *heap.begin();
    //cout<<"temp: "<<temp->data<<endl;
    Node* desiredNode = findNode(temp, old_data);
    desiredNode->data = new_data;
    Node *p = desiredNode->parent;
    while(p!=NULL && desiredNode->data > p->data)
    {
        swap(desiredNode->data, p->data);
        desiredNode = p;
        p = p->parent;
    }
}


void bHeap::print()
{
    cout<<"Printing Binomial Heap..."<<endl;
    cout<<"--------------------------"<<endl;

    list<Node*>:: iterator it = heap.begin();
    //cout<<heap.size();

    while(it!=heap.end())
    {
        cout<<"Binomial Tree, B"<<(*it)->degree<<endl;
        printEachTree(*it);
        it++;
    }
}

void bHeap::printEachTree(Node* node)
{

    /*while(node)
    {
        cout<<node->data<<" ";
        printEachTree(node->child);
        node=node->sibling;
    }*/
    vector<pair<int, int > > levelNodes;

    findLevels(node, levelNodes, 0);
    sort(levelNodes.begin(), levelNodes.end(), compar);

    int current = -1;

    for(int i=0; i<levelNodes.size(); i++)
    {
        if(current < levelNodes[i].second)
        {
            cout<<endl;
            cout<<"Level "<<levelNodes[i].second<<" : ";
            current = levelNodes[i].second;
        }
        cout<<levelNodes[i].first<<" ";
    }
    cout<<endl;
    cout<<endl;
}

void bHeap::findLevels(Node *root,vector<pair<int, int > > &levelNodes, int level)
{
    if(root==NULL)
    {
        return;
    }
    pair<int, int> temp;
    temp = make_pair(root->data, level);
    levelNodes.push_back(temp);
    //cout<<"here0"<<endl;

    findLevels(root->child, levelNodes ,level+1);
    findLevels(root->sibling, levelNodes ,level);
}





int main()
{
    ifstream inFile("in.txt");
    string read;

    bHeap heap;

    while(getline(inFile, read))
    {
        istringstream readLine(read);
        string operations;
        readLine>>operations;
        if(operations == "FIN")
        {
            cout<<"FindMax returned "<<heap.findMax()<<endl;
        }
        else if(operations == "EXT")
        {
            cout<<"ExtractMax returned "<<heap.extractMax()<<endl;
        }
        else if(operations == "INS")
        {
            int data;
            readLine>>data;
            heap.insertData(data);
        }
        else if(operations == "INC")
        {
            int old_data, new_data;
            readLine>>old_data;
            readLine>>new_data;
            //heap.increaseKey(old_data,new_data);
            cout<<"Increased "<<old_data<<". The Updated value is "<<new_data<<endl;
        }
        else if(operations == "PRI")
        {
            heap.print();
        }
    }
}

/*

INS 7
INS 12
INS 19
INS 5
INS 16
INS 6
PRI
INC 7 27
PRI
FIN
EXT
EXT
PRI

*/

