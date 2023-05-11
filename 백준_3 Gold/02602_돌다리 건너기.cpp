#include <iostream>
#include <vector>
#include <string>

using namespace std;

string scroll;
string angel;
string devil;
int strLen;

vector<vector<vector<int>>> cache;

int numOfCases(int ifAngel, int curScrollInd, int curLoc);

int main(){

    cin >> scroll;
    cin >> angel;
    cin >> devil;

    strLen = angel.length();
    cache = vector<vector<vector<int>>>(2, vector<vector<int>>(scroll.size() + 1, vector<int>(strLen + 1, -1)));

    cout << numOfCases(0, 0, 0) + numOfCases(1, 0, 0);

    return 0;
}

int numOfCases(int ifAngel, int curScrollInd, int curLoc){
    if(curScrollInd == scroll.size())
        return 1;
    if(curLoc == strLen)
        return 0;

    int tot = 0;
    if(ifAngel == 0){
        for(int i = curLoc; i < strLen; i++){
            if(angel[i] == scroll[curScrollInd]){
                if(cache[1][curScrollInd + 1][i + 1] == -1)
                    cache[1][curScrollInd + 1][i + 1] = numOfCases(1, curScrollInd + 1, i + 1);
                tot += cache[1][curScrollInd + 1][i + 1];
            }
        }
    }
    else{
        for(int i = curLoc; i < strLen; i++){
            if(devil[i] == scroll[curScrollInd]){
                if(cache[0][curScrollInd + 1][i + 1] == -1)
                    cache[0][curScrollInd + 1][i + 1] = numOfCases(0, curScrollInd + 1, i + 1);
                tot += cache[0][curScrollInd + 1][i + 1];
            }
        }
    }
    return tot;
}