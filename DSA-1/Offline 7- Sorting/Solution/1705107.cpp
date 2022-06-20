#include<bits/stdc++.h>
using namespace std;

void mergesort(int *arrray, int left, int right);
void mergee(int *arrray, int left, int mid, int right);

void quicksort(int *arrray, int start_idx, int end_idx);
int partitionn(int *arrray, int start_idx, int end_idx);


void exchange(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


int main()
{
    while(true)
    {
        int choice;
        cout<<"1. Sort an Array \t 2. Quit"<<endl;
        cin>>choice;
        if(choice==1)
        {
            int input_size, order_choice;
            cout<<"Enter size of the array: ";
            cin>>input_size;
            int *numbers = new int[input_size];
            cout<<"Select Order: \n1.Ascending order \t 2.Descending order \t 3.Random order"<<endl;
            cin>>order_choice;

                ///Generating Arrays
            if(order_choice==1)
            {
                numbers[0] = rand()%10;
                for(int i=1; i<input_size; i++)
                {
                    numbers[i] = numbers[i-1] + rand()%10;
                }
            }
            else if(order_choice==2)
            {
                numbers[0] = 50000;
                for(int i=1; i<input_size; i++)
                {
                    numbers[i] = numbers[i-1] - rand()%10;
                }
            }
            else if(order_choice==3)
            {
                for(int i=0; i<input_size; i++)
                {
                    numbers[i] = rand();
                }
            }

                ///Measuring Time for Merge Sort
            int merge_tempNumbers[input_size];
            int repeat = 1000000/input_size;
            clock_t start,finish,time1,time2;
            start = clock();
            for( int i=1; i<=repeat; i++ )
            {
                for(int i=0; i<input_size; i++) merge_tempNumbers[i] = numbers[i];
                mergesort(merge_tempNumbers, 0, input_size);
                //for(int i=0; i<input_size-1; i++) if(tempNumbers[i]>tempNumbers[i+1]) {cout<<"WRONGGG!!";break;}
            }
            finish = clock();
            time1 = finish-start;

            start = clock();
            for( int i=1; i<=repeat; i++ )
            {
                int tempNumbers[input_size];
                for(int i=0; i<input_size; i++) tempNumbers[i] = numbers[i];
            }
            finish = clock();
            time2 = finish-start;

            double merge_time = double(time1-time2)/CLOCKS_PER_SEC;
            cout << "Merge Sort Time: " << (merge_time/repeat)*1000000 << " microseconds" << endl;


                ///Measuring time for Quick Sort
            int quick_tempNumbers[input_size];
            start = clock();
            for( int i=1; i<=repeat; i++ )
            {
                for(int i=0; i<input_size; i++) quick_tempNumbers[i] = numbers[i];
                quicksort(quick_tempNumbers, 0, input_size-1);
                //for(int i=0; i<input_size-1; i++) if(tempNumbers[i]>tempNumbers[i+1]) {cout<<"WRONGGG!!";break;}
            }
            finish = clock();
            time1 = finish-start;

            start = clock();
            for( int i=1; i<=repeat; i++ )
            {
                int tempNumbers[input_size];
                for(int i=0; i<input_size; i++) tempNumbers[i] = numbers[i];
            }
            finish = clock();
            time2 = finish-start;

            double quick_time = double(time1-time2)/CLOCKS_PER_SEC;
            cout << "Quick Sort Time: " << (quick_time/repeat)*1000000 << " microseconds" << endl;
            /*for(int i=0; i<input_size; i++)
            {
                cout<<numbers[i]<<" ";
            }
            cout<<endl;*/

                ///printing sorted arrays
            cout<<left<<setw(15)<<"Merge Sort"<<left<<setw(15)<<"Quick Sort"<<endl;
            for(int i=0;i<input_size;i++)
            {
                cout<<left<<setw(15)<<merge_tempNumbers[i]<<left<<setw(15)<<quick_tempNumbers[i]<<endl;
            }
            delete []numbers;
        }
        else if(choice==2)
        {
            break;
        }
    }
}


void mergesort(int *arrray, int left, int right)
{
    int mid;
    if(left<right)
    {
        mid = left + (right-left)/2;
        mergesort(arrray, left, mid);
        mergesort(arrray, mid+1, right);
        mergee(arrray,left, mid, right);
    }
}


void mergee(int *arrray, int left, int mid, int right)
{
    int i, j, k, size_right, size_left;
    i=0;
    j=0;
    k=left;
    size_left = mid-left+1;
    size_right = right-mid;
    int left_array[size_left];
    int right_array[size_right];
    for(int idx=0; idx<size_left; idx++)
    {
        left_array[idx] = arrray[left+idx];
    }
    for(int idx=0; idx<size_right; idx++)
    {
        right_array[idx] = arrray[mid+1+idx];
    }
    while(i<size_left && j<size_right)
    {
        if(left_array[i]<right_array[j])
        {
            arrray[k] = left_array[i];
            i++;
        }
        else
        {
            arrray[k] = right_array[j];
            j++;
        }
        k++;
    }
    while(i<size_left)
    {
        arrray[k] = left_array[i];
        i++;
        k++;
    }
    while(j<size_right)
    {
        arrray[k] = right_array[j];
        k++;
        j++;
    }
}


void quicksort(int *arrray, int start_idx, int end_idx)
{
    if(start_idx<end_idx)
    {
        int partition_idx = partitionn(arrray, start_idx, end_idx);
        quicksort(arrray, start_idx, partition_idx-1);
        quicksort(arrray, partition_idx+1, end_idx);
    }
}

int partitionn(int *arrray, int start_idx, int end_idx)
{
    int pivotElement = arrray[end_idx];
    int partition_idx = start_idx;
    for(int i=start_idx; i<end_idx; i++)
    {
        if(arrray[i]<=pivotElement)
        {
            exchange(&arrray[i], &arrray[partition_idx]);
            partition_idx++;
        }
    }
    exchange(&arrray[partition_idx], &arrray[end_idx]);
    return partition_idx;
}
