#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
vector<int> products;
int costTruck, costHelicopter;


vector<vector<int>> cache_distance;
vector<vector<int>> cache_minDistanceSum;
vector<int> cache_minCost;

#define MAX 987654321

int getMinCost(int curInd);
int getMinDistanceSum(int st, int ed);

int main(){
    cin >> N;
    products = vector<int>(N);
    for(int i = 0; i < N; i++)
        cin >> products[i];
    cin >> costTruck >> costHelicopter;
    sort(products.begin(), products.end());

    cache_distance = vector<vector<int>>(N, vector<int>(N, 0));
    for(int i = 0; i < N; i++){
        cache_distance[i][0] = products[i] - products[0];
        for(int j = 1; j < N; j++){
            cache_distance[i][j] = cache_distance[i][j - 1] + abs(products[i] - products[j]);
        }
    }

    cache_minDistanceSum = vector<vector<int>>(N, vector<int>(N, -1));
    cache_minCost = vector<int>(N + 1, -1);

    int curSum = 0;
    int minCost = MAX;
    int curCost;
    for(int i = 0; i < N; i++){
        if(cache_minCost[i] == -1)
            cache_minCost[i] = getMinCost(i);
        curCost = curSum * costTruck + cache_minCost[i];
        if(minCost > curCost)
            minCost = curCost;

        curSum += products[i];
    }

    if(minCost > curSum * costTruck)
        minCost = curSum * costTruck;

    cout << minCost;

    return 0;
}

int getMinCost(int curInd){

    if(curInd == N)
        return 0;

    int minCost = MAX;
    int curCost;
    for(int i = curInd; i < N; i++){
        if(cache_minDistanceSum[curInd][i] == -1)
            cache_minDistanceSum[curInd][i] = getMinDistanceSum(curInd, i);
        
        if(cache_minCost[i + 1] == -1)
            cache_minCost[i + 1] = getMinCost(i + 1);

        curCost = cache_minDistanceSum[curInd][i] * costTruck + costHelicopter;

        if(minCost > cache_minCost[i + 1] + curCost)
            minCost = cache_minCost[i + 1] + curCost;
    }

    return minCost;
}

int getMinDistanceSum(int st, int ed){
    int minDistanceSum = MAX;

    if((ed - st + 1) % 2 == 0){
        int midLeft;
        if(st == 0)
            midLeft = cache_distance[(st + ed) / 2][ed];
        else
            midLeft = cache_distance[(st + ed) / 2][ed] - cache_distance[(st + ed) / 2][st - 1];

        int midRight;
        if(st == 0)
            midRight = cache_distance[(st + ed) / 2][ed];
        else
            midRight = cache_distance[(st + ed) / 2 + 1][ed] - cache_distance[(st + ed) / 2 + 1][st - 1];

        if(midLeft < midRight)
            return midLeft;
        else
            return midRight;
    }
    else{
        if(st == 0)
            return cache_distance[(st + ed) / 2][ed];
        else
            return cache_distance[(st + ed) / 2][ed] - cache_distance[(st + ed) / 2][st - 1];
    }
}