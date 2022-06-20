#include<iostream>
using namespace std;

void exchange(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

class PriorityQueue
{
    int *hp;
    int size,maxs;
public:
    PriorityQueue();
    PriorityQueue(int p);
    int parent(int i);
    int leftC(int i);
    int rightC(int i);
    void maxHeapify(int i);
    void insertElement(int x);
    int findMax();
    int extractMax();
    void increaseKey(int i,int newKey);
    void decreaseKey(int i,int newKey);
    void print();
};

PriorityQueue::PriorityQueue()
{
    size=0;
    maxs=10;
    hp=new int[maxs];
}

PriorityQueue::PriorityQueue(int p)
{
    size=0;
    maxs=p;
    hp=new int[maxs];
}

int PriorityQueue::parent(int i)
{
    return (i-1)/2;
}

int PriorityQueue::leftC(int i)
{
    return (2*i)+1;
}

int PriorityQueue::rightC(int i)
{
    return (2*i)+2;
}

void PriorityQueue::maxHeapify(int i)
{
    int l=leftC(i);
    int r=rightC(i);
    int largest;
    if(l<size && hp[l]>hp[i])
    {
        largest=l;
    }
    else
        largest=i;
    if(r<size && hp[r]>hp[largest])
        largest=r;
    if(largest!=i)
    {
        exchange(&hp[i] , &hp[largest]);
        maxHeapify(largest);
    }
}

void PriorityQueue::increaseKey(int i,int newKey)
{
    if(newKey<hp[i])
    {
        cout<<"New key is smaller than current key"<<endl;
        return;
    }
    hp[i]=newKey;
    while(i!=0 && hp[parent(i)]<hp[i])
    {
        exchange(&hp[i] , &hp[parent(i)]);
        i=parent(i);
    }
}

void PriorityQueue::insertElement(int x)
{
    if(size==maxs)
    {
        int *t;
        t=new int [maxs];
        for(int i=0;i<size;i++)
        {
            t[i]=hp[i];
        }
        delete[] hp;
        maxs+=10;
        hp=new int[maxs];
        for(int i=0;i<size;i++)
        {
            hp[i]=t[i];
        }
        delete[] t;
    }
    size++;
    hp[size-1]=-99999999;
    increaseKey(size-1,x);
}

int PriorityQueue::findMax()
{
    return hp[0];
}

int PriorityQueue::extractMax()
{
    if(size<=0)
    {
        cout<<"Heap Underflow"<<endl;
        return 99999999;
    }
    int maxm=hp[0];
    hp[0]=hp[size-1];
    size--;
    maxHeapify(0);
    return maxm;
}

void PriorityQueue::decreaseKey(int i, int newKey)
{
    if(newKey>hp[i])
    {
        cout<<"New key is Greater than current key"<<endl;
        return;
    }
    hp[i]=newKey;
    maxHeapify(i);
}

void PriorityQueue::print()
{
    for(int i=0;i<size;i++)
    {
        cout<<hp[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    PriorityQueue pq(50);
    int c=0;
    while(c!=7)
    {
        cout<<"1.Insert.  2.FindMax.  3.ExtractMax"<<endl;
        cout<<"4.IncreaseKey.  5.DecreaseKey.  6.Print  7.Quit"<<endl;
        cin>>c;
        if(c==1)
        {
            int x;
            cin>>x;
            pq.insertElement(x);
        }
        else if(c==2)
        {
            cout<<"Max: "<<pq.findMax()<<endl;
        }
        else if(c==3)
        {
            cout<<"Max: "<<pq.extractMax()<<endl;
        }
        else if(c==4)
        {
            int idx,newk;
            cout<<"Enter index: ";
            cin>>idx;
            cout<<"Enter New Key: ";
            cin>>newk;
            pq.increaseKey(idx,newk);
        }
        else if(c==5)
        {
            int idx,newk;
            cout<<"Enter index: ";
            cin>>idx;
            cout<<"Enter New Key: ";
            cin>>newk;
            pq.decreaseKey(idx,newk);
        }
        else if(c==6)
        {
            pq.print();
        }
        else if(c==7)
        {
            return 0;
        }
    }

}
