#include<bits/stdc++.h>
using namespace std;

#define predefined_size 10

class Array
{
private:
    string *main_array;
    int array_size, max_size;
    void resize_arr();

public:
    Array();
    Array(int n);
    Array(string *a, int len);
    ~Array();
    string* getArray();
    string getAnElement(int idx);
    void add(string element);
    void add(int idx, string element);
    void remove(int idx);
    void remove(string element);
    int* findIndex(string element);
    string* subArray(int start, int end);
    void merge(string *a1, string *a2, int n1, int n2);
    int length();
    bool isEmpty();
};

void Array::resize_arr()
{
    if(array_size==max_size)
    {
        string *temp;
        temp = new string[max_size];
        for(int i=0; i<array_size; i++)
        {
            temp[i] = main_array[i];
        }
        delete []main_array;

        max_size = max_size+1;
        main_array = new string[max_size];
        for(int i=0; i<array_size; i++)
        {
            main_array[i] = temp[i];
        }
        delete []temp;
    }
    else if(array_size == max_size-2)
    {
        string *temp;
        temp = new string[array_size];
        for(int i=0; i<array_size; i++)
        {
            temp[i] = main_array[i];
        }
        delete []main_array;

        max_size = max_size-1;
        main_array = new string[max_size];
        for(int i=0; i<array_size; i++)
        {
            main_array[i] = temp[i];
        }
        delete []temp;
    }
}

Array::Array()
{
    array_size=0;
    max_size = predefined_size;
    main_array = new string[max_size];
}

Array::Array(int n)
{
    array_size=0;
    max_size = n;
    main_array = new string[max_size];
}
Array::Array(string a[], int len)
{
    array_size=0;
    max_size=len;
    main_array=new string[max_size];
    for(int i=0;i<len;i++)
    {
        add(a[i]);
    }
}
Array::~Array()
{
    delete []main_array;
}

string* Array::getArray()
{
    return main_array;
}

string Array::getAnElement(int idx)
{
    return main_array[idx];
}

void Array::add(string element)
{
    resize_arr();
    main_array[array_size] = element;
    array_size++;
}

void Array::add(int idx, string element)
{
    resize_arr();
    for(int i=length(); i>idx; i--)
    {
        main_array[i]=main_array[i-1];
    }
    main_array[idx]=element;
    array_size++;
}

void Array::remove(int idx)
{
    resize_arr();
    if(idx<array_size && idx>=0)
    {
        for(int i=idx; i<array_size; i++)
        {
            main_array[i]=main_array[i+1];
        }
    }
    array_size--;
}

void Array::remove(string element)
{
    for(int i=0; i<array_size; i++)
    {
        if(main_array[i]==element)
        {
            remove(i);
            i--;
        }
    }
}

int* Array::findIndex(string element)
{
    int *idx_list;
    idx_list= new int[array_size+1];
    int cnt=0;
    for(int i=0; i<array_size; i++)
    {
        if(main_array[i]==element)
        {
            idx_list[cnt]=i;
            cnt++;
        }
    }
    if(cnt<array_size)
    {
        int *tmp;
        tmp = new int[cnt];
        for(int i=0;i<cnt;i++)
            tmp[i]=idx_list[i];
        delete []idx_list;
        idx_list=new int[cnt+1];
        for(int i=0;i<cnt;i++)
            idx_list[i]=tmp[i];
        delete []tmp;
    }
    idx_list[cnt]=-1;
    return idx_list;
}

string* Array::subArray(int start, int end)
{
    int subArray_size = end-start+1;
    string *subArrayData = new string[subArray_size];
    int sub_len = 0;
    for(int i=start; i<=end; i++)
    {
        subArrayData[sub_len]=main_array[i];
        sub_len++;
    }
    return subArrayData;
}

void Array::merge(string *a1, string *a2, int len1, int len2)
{
    delete []main_array;
    array_size = 0;
    max_size = len1+len2;
    main_array=new string[max_size];
    int i=0, j=0;
    while(i<len1 && j<len2)
    {
        if(a1[i]<a2[j])
        {
            add(a1[i]);
            i++;
        }
        else
        {
            add(a2[j]);
            j++;
        }
    }
    while(i<len1)
    {
        add(a1[i]);
        i++;
    }
    while(j<len2)
    {
        add(a2[j]);
        j++;
    }
}

int Array::length()
{
    return array_size;
}
bool Array::isEmpty()
{
    if(array_size==0)
        return true;
    else
        return false;
}

int main()
{
    string str[]={"sakib", "Python", "django", "Java"};
    int len = sizeof(str)/sizeof(str[0]);
    Array a(str, len);

    cout<<"Operations:"<<endl;
    cout<<"1. getArray() \t 2. getAnElement(int i) \t 3. add(element)"<<endl;
    cout<<"4. add(int i,element) \t 5. remove(element) \t 6. findIndex(element)"<<endl;
    cout<<"7. subarray \t 8. merge \t 9. length \t 10. isEmpty()"<<endl;
    int optn;
    while(true)
    {
        cout<<"Enter your Operation No: ";
        cin>>optn;
        if(optn == 1)
        {
            string *arr;
            arr=a.getArray();
            for(int i=0; i<a.length();i++)
            {
                cout<<arr[i]<<" ";
            }
            cout<<endl;
        }
        else if(optn==2)
        {
            int idx;
            cout<<"Enter the index i: ";
            cin>>idx;
            cout<<a.getAnElement(idx)<<endl;
        }
        else if(optn==3)
        {
            string element;
            cout<<"Enter the element: ";
            cin>>element;
            a.add(element);
        }
        else if(optn==4)
        {
            int indx;
            string element;
            cout<<"Enter index: ";
            cin>>indx;
            cout<<"Enter the element: ";
            cin>>element;
            a.add(indx, element);
        }
        else if(optn==5)
        {
            string element;
            cout<<"Enter the element to remove: ";
            cin>>element;
            a.remove(element);
        }
        else if(optn==6)
        {
            string element;
            cout<<"Enter Element: ";
            cin>>element;
            int *idx_list;
            idx_list = a.findIndex(element);
            for(int i=0; idx_list[i]!=-1 ; i++)
            {
                cout<<idx_list[i]<<" ";
            }
            cout<<endl;
        }
        else if(optn==7)
        {
            int start_idx, end_idx;
            cout<<"Enter starting index: ";
            cin>>start_idx;
            cout<<"Enter ending index: ";
            cin>>end_idx;
            string *subarrayData;
            subarrayData=a.subArray(start_idx,end_idx);
            for(int i=0; i<(end_idx-start_idx+1); i++)
            {
                cout<<subarrayData[i]<<" ";
            }
            cout<<endl;
        }
        else if(optn==8)
        {
            int len1, len2;
            cout<<"Enter the size of the first array: ";
            cin>>len1;
            string a1[len1];
            for(int i=0;i<len1;i++)
                cin>>a1[i];
            cout<<"Enter the size of the second array: ";
            cin>>len2;
            string a2[len2];
            for(int i=0;i<len2;i++)
                cin>>a2[i];

            a.merge(a1,a2,len1,len2);
        }
        else if(optn==9)
        {
            cout<<a.length()<<endl;
        }
        else if(optn==10)
        {
            if(a.isEmpty())
                cout<<"The array is Empty!"<<endl;
            else
                cout<<"The array is not Empty."<<endl;
        }
        else
        {
            break;
        }
    }

}
