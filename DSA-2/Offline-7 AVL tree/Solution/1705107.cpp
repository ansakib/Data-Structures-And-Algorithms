#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int value;
    Node* leftChild;
    Node* rightChild;
    int height;
};

class AVL_Tree
{
private:
    Node* root;
    int balanceFactor(Node *nd);
    int heightFunc(Node *nd);
    Node* singleRightRotation(Node *nd);
    Node* singleLeftRotation(Node *nd);
    Node* RightLeftRotation(Node *nd);
    Node* LeftRightRotation(Node *nd);
    Node* insertEngine(Node *nd, int value);
    void printEngine(Node *nd);
    Node* findEngine(Node *nd, int value);
    Node* parent(int data);
    Node* minEngine(Node* pointedRoot);
    Node* inOrderPred(Node *nd);
    Node* inOrderSucc(Node *nd);

public:
    AVL_Tree();
    void insertAvl(int value);
    void findItem(int value);
    Node* deleteItem(Node *nd, int value);
    void deleteH(int value);
    void print();
};

AVL_Tree::AVL_Tree()
{
    root=NULL;
}

int AVL_Tree::balanceFactor(Node *nd)
{
    if(nd==NULL) return 0;
    else if(nd->leftChild==NULL && nd->rightChild==NULL) return 0;
    else if(nd->leftChild!=NULL && nd->rightChild!=NULL)
    {
        nd->leftChild->height = heightFunc(nd->leftChild);
        nd->rightChild->height = heightFunc(nd->rightChild);
        return nd->leftChild->height - nd->rightChild->height;
    }
    else if(nd->leftChild!=NULL && nd->rightChild==NULL)
    {
        nd->leftChild->height = heightFunc(nd->leftChild);
        return nd->leftChild->height;
    }
    else if(nd->leftChild==NULL && nd->rightChild!=NULL)
    {
        nd->rightChild->height = heightFunc(nd->rightChild);
        int diff = 0-nd->rightChild->height;
        return diff;
    }
}

int AVL_Tree::heightFunc(Node *nd)
{
    if(nd==NULL)
    {
        return 0;
    }
    int leftH = heightFunc(nd->leftChild);
    int rightH = heightFunc(nd->rightChild);

    if(leftH>rightH)
        return leftH+1;
    else
        return rightH+1;
}

Node* AVL_Tree::singleRightRotation(Node *nd)
{
    Node *temp1;
    Node *temp2;
    temp1 = nd;
    temp2 = temp1->leftChild;
    temp1->leftChild = temp2->rightChild;
    temp2->rightChild = temp1;
    return temp2;

}

Node* AVL_Tree::singleLeftRotation(Node *nd)
{
    Node *temp1;
    Node *temp2;
    temp1 = nd;
    temp2 = temp1->rightChild;
    temp1->rightChild = temp2->leftChild;
    temp2->leftChild = temp1;
    return temp2;
}

Node* AVL_Tree::RightLeftRotation(Node *nd)
{
    Node *temp1;
    Node *temp2;
    Node *temp3;
    temp1 = nd;
    temp2 = temp1->rightChild;
    temp3 = temp1->rightChild->leftChild;
    temp1->rightChild = temp3->leftChild;
    temp2->leftChild = temp3->rightChild;
    temp3->leftChild = temp1;
    temp3->rightChild = temp2;

    return temp3;
}

Node* AVL_Tree::LeftRightRotation(Node *nd)
{
    Node *temp1;
    Node *temp2;
    Node *temp3;
    temp1 = nd;
    temp2 = temp1->leftChild;
    temp3 = temp1->leftChild->rightChild;
    temp1->leftChild = temp3->rightChild;
    temp2->rightChild = temp3->leftChild;
    temp3->rightChild = temp1;
    temp3->leftChild = temp2;

    return temp3;
}

Node* AVL_Tree::insertEngine(Node *nd, int value)
{

    if(nd==NULL)
    {
        Node *newNode;
        newNode = new Node;
        newNode->value = value;
        nd = newNode;
        nd->leftChild = NULL;
        nd->rightChild = NULL;
        nd->height = 1;
        return nd;
    }
    else if(value < nd->value)
    {
        nd->leftChild = insertEngine(nd->leftChild, value);
    }
    else
    {
        nd->rightChild = insertEngine(nd->rightChild, value);
    }

    nd->height = heightFunc(nd);
    //cout<<"nd:"<<nd->value<<" "<<value<<endl;

    int bfact = balanceFactor(nd);
    int bfactLeft = balanceFactor(nd->leftChild);
    int bfactRight = balanceFactor(nd->rightChild);
    /*if(value==6)
    {
        cout<<"bf:"<<bfact<<" "<<bfactLeft<<" "<<bfactRight<<endl;
        cout<<"h:"<<heightFunc(nd)<<" "<<heightFunc(nd->leftChild)<<" "<<heightFunc(nd->rightChild)<<endl;
        if(nd && nd->leftChild && nd->rightChild)
            cout<<"h2:"<<nd->height<<" "<<nd->leftChild->height<<" "<<nd->rightChild->height<<endl;
    }*/

    int heightInvCheck = false;
    if(bfact==2 && bfactLeft==1)
    {
        heightInvCheck = true;
        nd = singleRightRotation(nd);
    }
    else if(bfact==-2 && bfactRight==-1)
    {
        heightInvCheck = true;
        nd = singleLeftRotation(nd);
    }
    else if(bfact==2 && bfactLeft==-1)
    {
        heightInvCheck = true;
        nd = LeftRightRotation(nd);
    }
    else if(bfact==-2 && bfactRight==1)
    {
        heightInvCheck = true;
        nd = RightLeftRotation(nd);
    }

    if(heightInvCheck==true)
    {
        cout<<"Height invariant violated."<<endl;
        cout<<"After rebalancing: ";
    }
    return nd;
}

void AVL_Tree::insertAvl(int value)
{
    root = insertEngine(root, value);
    print();
    cout<<endl;
    cout<<endl;
}

Node* AVL_Tree::findEngine(Node *nd, int value)
{
    if(nd==NULL)
    {
        return NULL;
    }
    else if(nd->value == value)
    {
        return nd;
    }
    else if(value<nd->value)
    {
        findEngine(nd->leftChild, value);
    }
    else if(value>nd->value)
    {
        findEngine(nd->rightChild, value);
    }
}

void AVL_Tree::findItem(int value)
{
    Node* checker = findEngine(root, value);
    if(checker!=NULL)
    {
        cout<<"True"<<endl;
    }
    else
    {
        cout<<"False"<<endl;
    }
}

void AVL_Tree::printEngine(Node *nd)
{
    if(nd!=NULL)
    {
        cout<<nd->value<<"";
        if(nd->leftChild==NULL && nd->rightChild==NULL) return;
        cout<<"(";
        printEngine(nd->leftChild);
        cout<<")(";
        printEngine(nd->rightChild);
        cout<<")";
    }

}

void AVL_Tree::print()
{
    printEngine(root);
}

Node* AVL_Tree::parent(int data)
{
    Node* parent = NULL;
    Node* desiredItem = root;
    while(desiredItem!=NULL)
    {
        if(desiredItem->value == data)
        {
            break;
        }
        else if(desiredItem->value> data)
        {
            parent = desiredItem;
            desiredItem = desiredItem->leftChild;
        }
        else
        {
            parent = desiredItem;
            desiredItem = desiredItem->rightChild;
        }
    }
    return parent;
}

Node* AVL_Tree::inOrderPred(Node* nd)
{
    while(nd->rightChild!=NULL)
    {
        nd = nd->rightChild;
    }
    return nd;
}

Node* AVL_Tree::inOrderSucc(Node* nd)
{
    while(nd->leftChild!=NULL)
    {
        nd = nd->leftChild;
    }
    return nd;
}

void AVL_Tree::deleteH(int value)
{
    root = deleteItem(root, value);
}

Node* AVL_Tree::deleteItem(Node* nd, int value)
{
    if(!nd->leftChild && !nd->rightChild)
    {
        if(root==nd)
        {
            root = NULL;
        }
        delete nd;
        return NULL;
    }

    if(value > nd->value)
    {
        nd->rightChild = deleteItem(nd->rightChild, value);
    }
    else if(value < nd->value)
    {
        nd->leftChild = deleteItem(nd->leftChild, value);
    }
    else if(nd->rightChild!=NULL)
    {
        Node* succ;
        succ = inOrderSucc(nd->rightChild);
        nd->value = succ->value;
        nd->rightChild = deleteItem(nd->rightChild, succ->value);
    }
    else
    {
        Node* pre;
        pre = inOrderPred(nd->leftChild);
        nd->value = pre->value;
        nd->leftChild = deleteItem(nd->leftChild, pre->value);
    }

    int  bfact = balanceFactor(nd);
    int bfactLeft = balanceFactor(nd->leftChild);
    int bfactRight = balanceFactor(nd->rightChild);

    if(bfact==2)
    {
        if(bfactLeft==1 || bfactLeft==0)
            nd = singleRightRotation(nd);
        else if(bfactLeft==-1)
            nd = LeftRightRotation(nd);
    }
    else if(bfact==-2)
    {
        if(bfactRight==0)
            nd = singleRightRotation(nd);
        else if(bfactRight==-1)
            nd = singleLeftRotation(nd);
        else if(bfactRight==1)
            nd = RightLeftRotation(nd);
    }
    return nd;
}

/*Node* AVL_Tree::minEngine(Node* pointedRoot)
{
    while(pointedRoot->leftChild!=NULL)
    {
        pointedRoot = pointedRoot->leftChild;
    }
    return pointedRoot;
}

void AVL_Tree::deleteItem(int data)
{
    Node* desiredItem = findEngine(root, data);

    if(desiredItem==NULL)
    {
        return ;
    }
    else if(desiredItem->leftChild == NULL)
    {
        if(desiredItem==root)
        {
            root = desiredItem->rightChild;
        }
        else if(desiredItem == parent(data)->rightChild)
        {
            parent(data)->rightChild = desiredItem->rightChild;
        }
        else
        {
            parent(data)->leftChild = desiredItem->rightChild;
        }
        delete desiredItem;
    }
    else if(desiredItem->rightChild == NULL)
    {
        if(desiredItem==root)
        {
            root = desiredItem->leftChild;
        }
        else if(desiredItem == parent(data)->rightChild)
        {
            parent(data)->rightChild = desiredItem->leftChild;
        }
        else
        {
            parent(data)->leftChild = desiredItem->leftChild;
        }
        delete desiredItem;
    }
    else if(desiredItem->leftChild!=NULL && desiredItem->rightChild!=NULL)
    {
        Node* replacementNode = minEngine(desiredItem->rightChild);
        Node* parent_repNode = parent(replacementNode->value);
        if(parent_repNode == desiredItem)
        {
            desiredItem->rightChild = replacementNode->rightChild;
            desiredItem->value = replacementNode->value;
        }
        else
        {
            parent_repNode->leftChild = replacementNode->rightChild;
            desiredItem->value = replacementNode->value;
        }
    }
}

void AVL_Tree::deleteH(int data)
{
    Node* prnt = parent(data);
    deleteItem(data);
    int  bfact = balanceFactor(prnt);
    int bfactLeft = balanceFactor(prnt->leftChild);
    int bfactRight = balanceFactor(prnt->rightChild);
    while(prnt!=NULL){
        if(bfact==2)
        {
            if(bfactLeft==1 || bfactLeft==0)
                prnt = singleRightRotation(prnt);
            else if(bfactLeft==-1)
                prnt = LeftRightRotation(prnt);
        }
        else if(bfact==-2)
        {
            if(bfactRight==0)
                prnt = singleRightRotation(prnt);
            else if(bfactRight==-1)
                prnt = singleLeftRotation(prnt);
            else if(bfactRight==1)
                prnt = RightLeftRotation(prnt);
        }
        prnt = parent(prnt->value);
    }
}*/

int main()
{
    ifstream inFile("in.txt");
    string read;

    AVL_Tree tree;

    while(getline(inFile, read))
    {
        istringstream readLine(read);
        string operations;
        readLine>>operations;
        if(operations=="I")
        {
            int data;
            readLine>>data;
            tree.insertAvl(data);
        }
        else if(operations=="F")
        {
            int data;
            readLine>>data;
            tree.findItem(data);
        }
        else if(operations=="D")
        {
            int data;
            readLine>>data;
            tree.deleteH(data);
            tree.print();
            cout<<endl;
        }
    }

}

