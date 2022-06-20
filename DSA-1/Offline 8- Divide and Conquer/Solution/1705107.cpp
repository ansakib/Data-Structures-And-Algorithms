#include<bits/stdc++.h>
using namespace std;
struct Position
{
    int house_no;
    float x;
    float y;
};
struct result
{
    int house1, house2;
    float distance;
};
result close = {-1,-1,FLT_MAX};
result second_close = {-1,-1,FLT_MAX};

///ascending x sort
int comp_x(Position h1, Position h2)
{
    return h1.x<h2.x;
}
///ascending y sort
int comp_y(Position h1, Position h2)
{
    return h1.y<h2.y;
}

float findDist(Position h1, Position h2)
{
    float d = sqrt(((h1.x-h2.x)*(h1.x-h2.x))+((h1.y-h2.y)*(h1.y-h2.y)));
    return (d*1000)/1000;
}

result conquer_subP(Position xHouses[], int totalH)
{
    for(int i=0; i<totalH; i++)
    {
        for(int j=i+1; j<totalH; j++)
        {
            float crrnt = findDist(xHouses[i], xHouses[j]);
            if(crrnt<close.distance)
            {
                second_close = close;
                close.distance = crrnt;
                close.house1 = xHouses[i].house_no;
                close.house2 = xHouses[j].house_no;
            }
            else if(crrnt>close.distance && crrnt<second_close.distance)
            {
                second_close.distance = crrnt;
                second_close.house1 = xHouses[i].house_no;
                second_close.house2 = xHouses[j].house_no;
            }
        }
    }
    return second_close;
}

result divide_SecondClosest(Position xHouses[], Position yHouses[], int totalH)
{
    ///Conquer Call
    if(totalH<=3)
    {
        return conquer_subP(xHouses, totalH);
    }

    ///divide
    int middle = totalH/2;
    Position midHouse = xHouses[middle];
    Position left_yHouses[middle];
    int right_Hno = totalH-middle;
    Position right_yHouses[right_Hno];
    int leftIdx = 0;
    int rightIdx = 0;

    for(int i=0; i<totalH; i++)
    {
        if(yHouses[i].x<midHouse.x && leftIdx<middle)
        {
            left_yHouses[leftIdx] = yHouses[i];
            leftIdx++;
        }
        else
        {
            right_yHouses[rightIdx] = yHouses[i];
            rightIdx++;
        }
    }

    divide_SecondClosest(xHouses, left_yHouses, middle);
    divide_SecondClosest(xHouses+middle, right_yHouses, right_Hno);

    ///houses located in different part of vertical line
    Position acrossLine[totalH];
    int across_size = 0;
    for(int i=0; i<totalH; i++)
    {
        float rangeCheck = abs(yHouses[i].x-midHouse.x);
        if(rangeCheck<second_close.distance)
        {
            acrossLine[across_size] = yHouses[i];
            across_size++;
        }

    }
    for(int i=0; i<across_size; i++)
    {
        for(int j=i+1; j<across_size && abs(acrossLine[j].y-acrossLine[i].y)<second_close.distance; j++)
        {
            float crrnt = findDist(acrossLine[i], acrossLine[j]);
            if(crrnt<close.distance)
            {
                second_close = close;
                close.distance = crrnt;
                close.house1 = acrossLine[i].house_no;
                close.house2 = acrossLine[j].house_no;
            }
            else if(crrnt>close.distance && crrnt<second_close.distance)
            {
                second_close.distance = crrnt;
                second_close.house1 = acrossLine[i].house_no;
                second_close.house2 = acrossLine[j].house_no;
            }
        }
    }
    return second_close;
}

result SecondClosest(Position houses[], int totalH)
{
    Position xHouses[totalH];
    Position yHouses[totalH];
    for(int i=0;i<totalH;i++)
    {
        xHouses[i] = houses[i];
        yHouses[i] = houses[i];
    }
    sort(xHouses, xHouses+totalH, comp_x);
    sort(yHouses, yHouses+totalH, comp_y);
    divide_SecondClosest(xHouses, yHouses, totalH);
    return second_close;
    /*for(int i=0;i<totalH;i++)
    {
        cout<<xHouses[i].x<<" "<<xHouses[i].y<<endl;
    }
    cout<<"--------"<<endl;
    for(int i=0;i<totalH;i++)
    {
        cout<<yHouses[i].x<<" "<<yHouses[i].y<<endl;
    }*/
}

int main()
{
    int total_house;
    ifstream inputFile("input.txt");
    inputFile>>total_house;
    Position house_detail[total_house];
    for(int i=0; i<total_house; i++)
    {
        house_detail[i].house_no = i;
        inputFile>>house_detail[i].x;
        inputFile>>house_detail[i].y;
    }
    inputFile.close();

    result ans = SecondClosest(house_detail, total_house);
    cout<<ans.house1<<" "<<ans.house2<<endl;
    cout<<ans.distance<<endl;
}
