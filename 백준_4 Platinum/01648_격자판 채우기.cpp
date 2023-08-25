#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

int N, M;

vector<bool> numToBin(int num) {
    vector<bool> bin(N, false);
    for (int i = 0; i < N; i++) {
        if (num % 2 == 1)
            bin[i] = true;
        else
            bin[i] = false;

        num /= 2;
    }

    return bin;
}

int binToNum(vector<bool>& bin) {
    int tot = 0;
    for (int i = 0; i < N; i++) {
        if (bin[i])
            tot += pow(2, i);
    }
    return tot;
}

inline int ifFilled(int num, int ind) {
    return num & (int)(pow(2, ind));
}
inline int setFilled(int num, int ind) {
    return num | (int)(pow(2, ind));
}

void nextNumOfCases(int& num, int curInd, vector<int>& numOfCases, int nextCase) {

    if (curInd == N)
        return numOfCases.push_back(nextCase);

    if (curInd == N - 1) {
        if (ifFilled(num, curInd))
            numOfCases.push_back(nextCase);
        else
            numOfCases.push_back(setFilled(nextCase, curInd));

        return;
    }

    if (ifFilled(num, curInd))
        return nextNumOfCases(num, curInd + 1, numOfCases, nextCase);


    nextNumOfCases(num, curInd + 1, numOfCases, setFilled(nextCase, curInd));

    if (!ifFilled(num, curInd + 1))
        nextNumOfCases(num, curInd + 2, numOfCases, nextCase);

    return;
}


int main() {
    cin >> N >> M;

    vector<vector<int>> numOfCases(pow(2, N), vector<int>());
    for(int i = 0; i < pow(2, N); i++)
      nextNumOfCases(i, 0, numOfCases[i], 0);

    //다음 층
    vector<int> nextFloorNumOfCases(pow(2, N), 0);
    for(int i = 0; i < numOfCases[0].size(); i++)
      nextFloorNumOfCases[numOfCases[0][i]]++;
    
    int curFloor = 1;
    while(curFloor < M){
      vector<int> tempFloorNumOfCases(pow(2, N), 0);
      for(int i = 0; i < nextFloorNumOfCases.size(); i++){
        for(int j = 0; j < numOfCases[i].size(); j++){
          tempFloorNumOfCases[numOfCases[i][j]] += nextFloorNumOfCases[i];
          tempFloorNumOfCases[numOfCases[i][j]] %= 9901;
        }
      }
      curFloor++;
      nextFloorNumOfCases = tempFloorNumOfCases;
    }

    cout << nextFloorNumOfCases[0];
    //2*2 테케 돌려보셈
    return 0;
}