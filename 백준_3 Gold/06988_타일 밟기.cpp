#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N;
vector<int> tiles;
int tileMaxNum;
vector<bool> ifTileExists;

long long getTotSum(int firstTile, int secondTile);

int main(){
    cin >> N;
    tiles = vector<int>(N);
    for(int i = 0; i < N; i++)
        cin >> tiles[i];
    
    tileMaxNum = tiles.back();
    ifTileExists = vector<bool>(tileMaxNum + 1, false);
    for(auto iter = tiles.begin(); iter != tiles.end(); iter++)
        ifTileExists[*iter] = true;
    
    //brute force
    long long maxTotSum = 0;
    for(int i = 0; i <= N - 3; i++){
        for(int j = i + 1; j <= N - 2; j++){
            long long curTotSum = getTotSum(tiles[i], tiles[j]);
            if(curTotSum > maxTotSum)
                maxTotSum = curTotSum;
        }
    }

    cout << maxTotSum;

    return 0;
}

long long getTotSum(int firstTile, int secondTile){
    long long totSum = firstTile + secondTile;
    int d = secondTile - firstTile;
    int cnt = 2;

    while(secondTile + d <= tileMaxNum && ifTileExists[secondTile + d]){
        totSum += secondTile + d;
        secondTile += d;
        cnt++;
    }

    if(cnt >= 3)
        return totSum;
    else
        return 0;
}