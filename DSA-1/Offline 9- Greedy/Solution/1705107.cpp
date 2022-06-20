#include<bits/stdc++.h>
using namespace std;

bool comp_descending(int x, int y)
{
    return x>y;
}

int main()
{
    int n, k;
    cin>>n>>k;
    int plant_price[n];
    for(int i=0; i<n; i++)
    {
        cin>>plant_price[i];
    }
    sort(plant_price, plant_price+n, comp_descending);
    int counnt, cost, purchase_time;
    counnt = 0;
    cost = 0;
    purchase_time = 1;
    for(int i=0; i<n; i++)
    {
        if(counnt==k)
        {
            purchase_time++;
            counnt = 0;
        }
        cost += plant_price[i]*purchase_time;
        counnt++;
    }
    cout<<"Cost: "<<cost<<endl;
}
