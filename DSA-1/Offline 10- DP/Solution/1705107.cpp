#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, target_sum;
    ifstream inputFile("input.txt");
    inputFile>>n;
    inputFile>>target_sum;
    int faces[n];
    for(int i=0;i<n;i++)
    {
        inputFile>>faces[i];
    }
    int dp_table[n][target_sum+1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=target_sum;j++)
        {
            dp_table[i][j]=0;
        }
    }

    for(int i=1; i<=faces[0] && i<=target_sum; i++)
    {
        dp_table[0][i] = 1;
    }
    for(int i=1; i<n; i++)
    {
        for(int j=1; j<=target_sum; j++)
        {
            dp_table[i-1][j] = (dp_table[i-1][j]+dp_table[i-1][j-1])%1000000007;
        }
        for(int j=1; j<=target_sum; j++)
        {
            if(j-faces[i]-1<0)
            {
                dp_table[i][j] = (dp_table[i-1][j-1])%1000000007;
            }
            else
            {
                dp_table[i][j] = (dp_table[i-1][j-1]-dp_table[i-1][j-faces[i]-1])%1000000007;
                if(dp_table[i][j]<0)
                {
                    dp_table[i][j] += 1000000007;
                }
            }
        }
    }
    cout<<dp_table[n-1][target_sum]<<endl;
}
