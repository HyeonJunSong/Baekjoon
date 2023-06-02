#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> rolledIndex;

int N, K;
vector<int> fishbowl;

void insertFish();
void initRolledIndex();
void organizeFishBowl();
int getFishDiff();
vector<vector<int>> rollFishbowl();
vector<vector<int>> foldFishbowl();
vector<vector<int>> moveFish(vector<vector<int>> fishBowlP);
vector<int> spreadFishBowl(vector<vector<int>> fishBowlP);

int main(){

    cin >> N >> K;
    fishbowl = vector<int>(N);
    for(int i = 0; i < N; i++)
        cin >> fishbowl[i];
    
    initRolledIndex();

    int organizeCnt = 0;
    while(getFishDiff() > K){
        organizeFishBowl();
        organizeCnt++;
    }

    cout << organizeCnt;

    return 0;
}

void initRolledIndex(){
    
    rolledIndex.push_back({1, 0});
    int curInd = 2;

    while(curInd + rolledIndex[0].size() <= N){
        
        vector<vector<int>> newRolledIndex(rolledIndex[0].size());
        for(int i = 0; i < newRolledIndex.size(); i++){
            newRolledIndex[i].push_back(curInd + i);
            for(int j = rolledIndex.size() - 1; j >= 0 ; j--){
                newRolledIndex[i].push_back(rolledIndex[j][i]);
            }
        }
        curInd += rolledIndex[0].size();
        rolledIndex = newRolledIndex;
    }

    for(; curInd < N; curInd++)
        rolledIndex.push_back(vector<int>(1, curInd));
    
}

void organizeFishBowl(){

    insertFish();

    //roll fishbowl, movefish, spread
    fishbowl = spreadFishBowl(moveFish(rollFishbowl()));

    //fold fishbowl, movefish, spread
    fishbowl = spreadFishBowl(moveFish(foldFishbowl()));

}

void insertFish(){
    int minFish = 987654321;
    for(int i = 0; i < N; i++)
        if(minFish > fishbowl[i])
            minFish = fishbowl[i];

    for(int i = 0; i < N; i++)
        if(fishbowl[i] == minFish)
            fishbowl[i]++;
}

int getFishDiff(){
    int max = 0;
    int min = 987654321;
    for(int i = 0; i < N; i++){
        if(max < fishbowl[i])
            max = fishbowl[i];
        if(min > fishbowl[i])
            min = fishbowl[i];
    }

    return max - min;
}

vector<vector<int>> rollFishbowl(){
    vector<vector<int>> rolledFishBowl = rolledIndex;

    for(int i = 0; i < rolledFishBowl.size(); i++)
        for(int j = 0; j < rolledFishBowl[i].size(); j++)
            rolledFishBowl[i][j] = fishbowl[rolledFishBowl[i][j]];
    
    return rolledFishBowl;
}

vector<vector<int>> foldFishbowl(){
    vector<vector<int>> foldedFishBowl(N / 4);
    for(int i = 0; i < N / 4; i++){
        foldedFishBowl[i].push_back(fishbowl[3 * (N / 4) + i]);
        foldedFishBowl[i].push_back(fishbowl[0 * (N / 4) + (N / 4 - i - 1)]);
        foldedFishBowl[i].push_back(fishbowl[1 * (N / 4) + i]);
        foldedFishBowl[i].push_back(fishbowl[2 * (N / 4) + (N / 4 - i - 1)]);
    }

    return foldedFishBowl;
}

vector<vector<int>> moveFish(vector<vector<int>> fishBowlP){
    vector<vector<int>> movedFishBowl = fishBowlP;

    for(int i = 0; i < fishBowlP.size(); i++){
        for(int j = 0; j < fishBowlP[i].size(); j++){
            //right check
            if(i + 1 < fishBowlP.size() && fishBowlP[i + 1].size() > j){
                int d = abs(fishBowlP[i][j] - fishBowlP[i + 1][j]) / 5;
                if(d > 0){
                    if(fishBowlP[i][j] > fishBowlP[i + 1][j]){
                        movedFishBowl[i][j] -= d;
                        movedFishBowl[i + 1][j] += d;
                    }
                    else{
                        movedFishBowl[i][j] += d;
                        movedFishBowl[i + 1][j] -= d;
                    }
                }
            }

            //down check
            if(j > 0){
                int d = abs(fishBowlP[i][j] - fishBowlP[i][j - 1]) / 5;
                if(d > 0){
                    if(fishBowlP[i][j] > fishBowlP[i][j - 1]){
                        movedFishBowl[i][j] -= d;
                        movedFishBowl[i][j - 1] += d;
                    }
                    else{
                        movedFishBowl[i][j] += d;
                        movedFishBowl[i][j - 1] -= d;
                    }
                }
            }
        }
    }

    return movedFishBowl;
}

vector<int> spreadFishBowl(vector<vector<int>> fishBowlP){
    vector<int> newFishBowl;
    for(int i = 0; i < fishBowlP.size(); i++)
        for(int j = 0; j < fishBowlP[i].size(); j++)
            newFishBowl.push_back(fishBowlP[i][j]);
    
    return newFishBowl;
}