#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int value;
    Node* leftChild;
    Node* rightChild;
};

class BinarySearchTree
{
private:
    Node* root;
    Node* searchEngine(Node* pointedRoot, int data);
    Node* minEngine(Node* pointedRoot);
    Node* maxEngine(Node* pointedRoot);
    int heightEngine(Node* pointedRoot);
    Node* parent(int data);
    void preOrderEngine(Node* pointedNode);
    void inOrderEngine(Node* pointedNode);
    void postOrderEngine(Node* pointedNode);
    int sizeEngine(Node* pointedNode);

public:
    BinarySearchTree();
    void insertItem(int data);
    void searchItem(int data);
    int getInOrderSuccessor(int data);
    int getInOrderPredecessor(int data);
    void deleteItem(int data);
    int getItemDepth(int data);
    int getMaxItem();
    int getMinItem();
    int height();
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    int getSize();
};

BinarySearchTree::BinarySearchTree()
{
    root = new Node;
    root = NULL;
}

void BinarySearchTree::insertItem(int data)
{
    if(searchEngine(root, data))
    {
        return ; ///item already exist
    }

    Node* newNode = new Node;
    newNode->value = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    Node* pointedNode = root;
    Node* previousNode = NULL;

    while(pointedNode!=NULL)
    {
        previousNode = pointedNode;
        if(data<pointedNode->value)
        {
            pointedNode = pointedNode->leftChild;
        }
        else
        {
            pointedNode = pointedNode->rightChild;
        }
    }

    if(previousNode == NULL)
    {
        root = newNode;
    }
    else if(data < previousNode->value)
    {
        previousNode->leftChild = newNode;
    }
    else
    {
        previousNode->rightChild = newNode;
    }
}

void BinarySearchTree::searchItem(int data)
{
    Node* search_checker = searchEngine(root, data);
    if(search_checker!=NULL)
    {
        cout<<data<<" has been found."<<endl;
    }
    else
    {
        cout<<data<<" has not been found."<<endl;
    }
}

Node* BinarySearchTree::searchEngine(Node* pointedRoot, int data)
{
    if(pointedRoot == NULL)
    {
        return NULL;
    }
    else if(pointedRoot->value == data)
    {
        return pointedRoot;
    }
    else if(data<pointedRoot->value)
    {
        searchEngine(pointedRoot->leftChild, data);
    }
    else if(data>pointedRoot->value)
    {
        searchEngine(pointedRoot->rightChild, data);
    }
}

Node* BinarySearchTree::parent(int data)
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

int BinarySearchTree::getInOrderSuccessor(int data)
{
    Node* desiredNode = searchEngine(root, data);
    if(desiredNode == NULL)
    {
        cout<<"desired node not found!"<<endl;
        return INT_MIN;
    }
    else if(desiredNode->rightChild == NULL)
    {
        Node* temp = root;
        Node* successorNode = NULL;
        while(temp!=NULL)
        {
            if(temp->value == data)
            {
                if(successorNode!=NULL)
                    return successorNode->value;
                break;
            }
            else if(data<temp->value)
            {
                successorNode = temp;
                temp = temp->leftChild;
            }
            else
            {
                temp = temp->rightChild;
            }
        }

        if(successorNode==NULL)
        {
            cout<<"No In Order Successor Available!"<<endl;
            return INT_MIN;
        }
    }
    else
    {
        Node* successorNode = minEngine(desiredNode->rightChild);

        return successorNode->value;
    }
}

int BinarySearchTree::getInOrderPredecessor(int data)
{
    Node* desiredNode = searchEngine(root, data);
    if(desiredNode == NULL)
    {
        cout<<"desired node not found!"<<endl;
        return INT_MAX;
    }
    else if(desiredNode->leftChild == NULL)
    {
        Node* temp = root;
        Node* predecessorNode = NULL;
        while(temp!=NULL)
        {
            if(temp->value == data)
            {
                if(predecessorNode!=NULL)
                    return predecessorNode->value;
                break;
            }
            else if(data>temp->value)
            {
                predecessorNode = temp;
                temp = temp->rightChild;
            }
            else
            {
                temp = temp->leftChild;
            }
        }

        if(predecessorNode==NULL)
        {
            cout<<"No In Order Predecessor Available!"<<endl;
            return INT_MAX;
        }
    }
    else
    {
        Node* predecessorNode = maxEngine(desiredNode->leftChild);

        return predecessorNode->value;
    }
}

void BinarySearchTree::deleteItem(int data)
{
    Node* desiredItem = searchEngine(root, data);

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

int BinarySearchTree::getItemDepth(int data)
{
    Node* desiredItem = root;
    int depth = -1;
    while(desiredItem!=NULL)
    {
        if(desiredItem->value == data)
        {
            return depth+1;
        }
        else if(desiredItem->value> data)
        {
            desiredItem = desiredItem->leftChild;
            depth++;
        }
        else
        {
            desiredItem = desiredItem->rightChild;
            depth++;
        }
    }
    return -1;
}

int BinarySearchTree::getMaxItem()
{
    if(root==NULL)
    {
        return INT_MIN;
    }
    return maxEngine(root)->value;
}
Node* BinarySearchTree::maxEngine(Node* pointedRoot)
{
    while(pointedRoot->rightChild!=NULL)
    {
        pointedRoot = pointedRoot->rightChild;
    }
    return pointedRoot;
}

int BinarySearchTree::getMinItem()
{
    if(root==NULL)
    {
        return INT_MAX;
    }
    return minEngine(root)->value;
}
Node* BinarySearchTree::minEngine(Node* pointedRoot)
{
    while(pointedRoot->leftChild!=NULL)
    {
        pointedRoot = pointedRoot->leftChild;
    }
    return pointedRoot;
}

int BinarySearchTree::height()
{
    return heightEngine(root);
}
int BinarySearchTree::heightEngine(Node* pointedRoot)
{
    if(pointedRoot==NULL)
        return -1;

    int left_height = heightEngine(pointedRoot->leftChild);
    int right_height = heightEngine(pointedRoot->rightChild);

    if(left_height>right_height)
    {
        return left_height+1;
    }
    else
    {
        return right_height+1;
    }
}

void BinarySearchTree::printInOrder()
{
    inOrderEngine(root);
    cout<<endl;
}

void BinarySearchTree::inOrderEngine(Node* pointedNode)
{
    if(pointedNode!=NULL)
    {
        inOrderEngine(pointedNode->leftChild);
        cout<<pointedNode->value<<" ";
        inOrderEngine(pointedNode->rightChild);
    }
}

void BinarySearchTree::printPreOrder()
{
    preOrderEngine(root);
    cout<<endl;
}
void BinarySearchTree::preOrderEngine(Node* pointedNode)
{
    if(pointedNode!=NULL)
    {
        cout<<pointedNode->value<<" ";
        preOrderEngine(pointedNode->leftChild);
        preOrderEngine(pointedNode->rightChild);
    }
}

void BinarySearchTree::printPostOrder()
{
    postOrderEngine(root);
    cout<<endl;
}
void BinarySearchTree::postOrderEngine(Node* pointedNode)
{
    if(pointedNode!=NULL)
    {
        postOrderEngine(pointedNode->leftChild);
        postOrderEngine(pointedNode->rightChild);
        cout<<pointedNode->value<<" ";
    }
}

int BinarySearchTree::getSize()
{
    return sizeEngine(root);
}
int BinarySearchTree::sizeEngine(Node* pointedNode)
{
    if(pointedNode==NULL)
    {
        return 0;
    }

    int left_size = sizeEngine(pointedNode->leftChild);
    int right_size = sizeEngine(pointedNode->rightChild);
    int totalSize = left_size+right_size+1;

    return totalSize;
}

int main()
{
    BinarySearchTree tree;
    cout<<"1. Insert Item\t 2. Search Item\t 3. Get In Order Successor\t 4. Get In Order Predecessor"<<endl;
    cout<<"5. Delete Item\t 6. Get Item Depth\t 7. Get Max Item\t 8. Get Min Item\t 9. Get height"<<endl;
    cout<<"10. Print In Order\t 11. Print Pre Oder\t 12. Print Post Order\t 13. Get Size"<<endl;

    while(true)
    {
        int choice;
        cin>>choice;
        if(choice == 1)
        {
            int value;
            cout<<"Enter an item to insert: ";
            cin>>value;
            tree.insertItem(value);
        }
        else if(choice == 2)
        {
            int value;
            cout<<"Enter an item to Search: ";
            cin>>value;
            tree.searchItem(value);
        }
        else if(choice == 3)
        {
            int value;
            cout<<"Enter item: ";
            cin>>value;
            if(tree.getInOrderSuccessor(value)!=INT_MIN)
            {
                cout<<"In Order Successor: "<<tree.getInOrderSuccessor(value)<<endl;
            }
        }
        else if(choice == 4)
        {
            int value;
            cout<<"Enter item: ";
            cin>>value;
            if(tree.getInOrderPredecessor(value)!=INT_MAX)
            {
                cout<<"In Order Predecessor: "<<tree.getInOrderPredecessor(value)<<endl;
            }
        }
        else if(choice == 5)
        {
            int value;
            cout<<"Enter item to delete: ";
            cin>>value;
            tree.deleteItem(value);
        }
        else if(choice == 6)
        {
            int value;
            cout<<"Enter the item: ";
            cin>>value;
            cout<<"Depth: "<<tree.getItemDepth(value)<<endl;
        }
        else if(choice == 7)
        {
            cout<<"Max Item: "<<tree.getMaxItem()<<endl;
        }
        else if(choice == 8)
        {
            cout<<"Min Item: "<<tree.getMinItem()<<endl;
        }
        else if(choice == 9)
        {
            cout<<"Height: "<<tree.height()<<endl;
        }
        else if(choice == 10)
        {
            tree.printInOrder();
        }
        else if(choice == 11)
        {
            tree.printPreOrder();
        }
        else if(choice == 12)
        {
            tree.printPostOrder();
        }
        else if(choice == 13)
        {
            cout<<"Size: "<<tree.getSize()<<endl;
        }
    }
}
