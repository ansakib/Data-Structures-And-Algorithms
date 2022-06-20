#include<bits/stdc++.h>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node* next;
};

template <typename T>
class Queue
{
private:
    Node<T> *first;
    Node<T> *last;
    int length;

public:
    Queue();
    void enqueue(T value);
    T dequeue();
    T queueFront();
    int queue_size();
    bool isEmpty();
    void printQueue();
};

template <typename T>
Queue<T>::Queue()
{
    first = NULL;
    last = NULL;
    length = 0;
}

template <typename T>
void Queue<T>::enqueue(T value)
{
    Node<T> *newNode = new Node<T>;
    newNode->data = value;
    newNode->next = NULL;
    if(length == 0)
    {
        first = newNode;
        last = newNode;
    }
    else
    {
        last->next = newNode;
        last = newNode;
    }
    length++;
}

template <typename T>
T Queue<T>::dequeue()
{
    Node<T> *temp = first;
    first = first->next;
    if(first==NULL)
    {
        last == NULL;
    }
    T deq_data = temp->data;
    length--;
    delete temp;
    return deq_data;
}

template <typename T>
T Queue<T>::queueFront()
{
    if(!isEmpty())
        return first->data;
}

template <typename T>
int Queue<T>::queue_size()
{
    return length;
}

template <typename T>
bool Queue<T>::isEmpty()
{
    if(length == 0) return true;
    else return false;
}

template <typename T>
void Queue<T>::printQueue()
{
    Node<T> *temp = first;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

int main()
{
    string string_old, string_new;
    cout<<"Enter String_old= ";
    cin>>string_old;
    int repeatcheck[26] = {0};

    Queue<char> myqueue;

    for(int i=0; i<string_old.length(); i++)
    {
        int char_index = string_old[i] - 97;
        repeatcheck[char_index]++;

        myqueue.enqueue(string_old[i]);

        while(true)
        {
            int front_index = myqueue.queueFront()-97;
            if(myqueue.isEmpty())
            {
                string_new+='#';
                break;
            }
            else if(repeatcheck[front_index]>=2)
            {
                myqueue.dequeue();
            }
            else
            {
                string_new+=myqueue.queueFront();
                break;
            }
        }
    }

    cout<<"String_new= "<<string_new<<endl;
}
