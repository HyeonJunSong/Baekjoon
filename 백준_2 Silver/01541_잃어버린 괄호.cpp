////02.21.2023
//이해 및 설계 : 18m 44s
//입력 : 5m 34s
//구현 : 11m 32s

//tot : 35m 50s

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int minSum(int stInd, int edInd);

vector<int> numSet;
vector<char> operSet;

vector<vector<int>> cache;

#define MAX 987654321

int main(){
    string inpStr;
    cin >> inpStr;

    string tempNum = "";
    for(int i = 0; i < inpStr.size(); i++){
        if(inpStr[i] == '+' || inpStr[i] == '-'){
            numSet.push_back(stoi(tempNum));
            operSet.push_back(inpStr[i]);
            tempNum = "";
        }
        else{
            tempNum += inpStr[i];
        }
    }
    numSet.push_back(stoi(tempNum));
    
    cache = vector<vector<int>>(numSet.size(), vector<int>(numSet.size() + 1, -1));
    cout << minSum(0, numSet.size());

    return 0;
}

int minSum(int stInd, int edInd){
    //////기저함수
    if(stInd + 1 == edInd){
        return numSet[stInd];
    }

    //////연산 & 메모이제이션
    int ans = MAX;
    for(int i = stInd + 1; i < edInd; i++){
        if(cache[stInd][i] == -1)
            cache[stInd][i] = minSum(stInd, i);
        if(cache[i][edInd] == -1)
            cache[i][edInd] = minSum(i, edInd);

        int frontGroup = cache[stInd][i];
        int rearGroup = cache[i][edInd];

        if(operSet[i - 1] == '+'){
            if(ans > frontGroup + rearGroup)
                ans = frontGroup + rearGroup;
        }
        else{
            if(ans > frontGroup - rearGroup)
                ans = frontGroup - rearGroup;
        }
    }


    //////리턴
    return ans;
}