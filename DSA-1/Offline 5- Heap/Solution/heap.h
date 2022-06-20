#include<bits/stdc++.h>
using namespace std;

void exchange(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class Heap
{
private:
    int *hpArray;
    int hpSize;
    int parent(int idx);
    int leftChild(int idx);
    int rightChild(int idx);
    void maxHeapify(int idx);
    void buildMaxHeap();

public:
    Heap();
    Heap(int n);
    Heap(vector<int>&v);
    int size();
    void insert(int element);
    int getMax();
    void deleteKey();
    void printHeap();
};

Heap::Heap()
{
    hpSize = 0;
    hpArray = new int[100];
}

Heap::Heap(int n)
{
    hpSize = 0;
    hpArray = new int[n];
}

Heap::Heap(vector<int>&v)
{
    hpSize = v.size();
    hpArray = new int[hpSize];
    hpArray = &v[0];
    buildMaxHeap();
}

int Heap::parent(int idx)
{
    return (idx-1)/2;
}
int Heap::leftChild(int idx)
{
    return (2*idx)+1;
}
int Heap::rightChild(int idx)
{
    return (2*idx)+2;
}
void Heap::maxHeapify(int idx)
{
    int left = leftChild(idx);
    int right = rightChild(idx);
    int large = idx;

    if(left<hpSize && hpArray[left]>hpArray[large])
    {
        large = left;
    }
    if(right<hpSize && hpArray[right]>hpArray[large])
    {
        large = right;
    }

    if(large!=idx)
    {
        exchange(&hpArray[idx], &hpArray[large]);
        maxHeapify(large);
    }
}

void Heap::buildMaxHeap()
{
    for(int i = (hpSize/2)-1; i>=0; i--)
    {
        maxHeapify(i);
    }
}

int Heap::size()
{
    return hpSize;
}

void Heap::insert(int element)
{
    hpArray[hpSize] = element;
    int currentIdx = hpSize;
    hpSize++;

    while(currentIdx!=0)
    {
        if(hpArray[parent(currentIdx)] < hpArray[currentIdx])
        {
            exchange(&hpArray[parent(currentIdx)], &hpArray[currentIdx]);
            currentIdx = parent(currentIdx);
        }
        else
        {
            break;
        }
    }
}

int Heap::getMax()
{
    return hpArray[0];
}

void Heap::deleteKey()
{
    hpSize--;
    //hpArray[0] = hpArray[hpSize];
    exchange(&hpArray[0], &hpArray[hpSize]);
    maxHeapify(0);
}

void Heap::printHeap()
{
    for(int i=0;i<hpSize;i++)
    {
        cout<<hpArray[i]<<" ";
    }
    cout<<endl;
    cout<<"heapsize: "<<hpSize<<endl;
}



void heapsort(vector<int>&v)
{
    Heap hsort(v);
    for(int i=v.size(); i>=1; i--)
    {
        hsort.deleteKey();
    }
    reverse(v.begin(), v.end());
}

