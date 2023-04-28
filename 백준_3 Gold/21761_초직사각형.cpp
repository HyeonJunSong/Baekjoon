#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<long long> hyperCube(4);
vector<vector<long long>> cards(4);
vector<int> index(4, 0);

int getLargestDim();

int main() {
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < 4; i++)
        cin >> hyperCube[i];
    
    char T;
    int U;
    for (int i = 0; i < N; i++) {
        cin >> T >> U;
        cards[T - 'A'].push_back(U);
    }

    for(int i = 0; i < 4; i++)
        sort(cards[i].rbegin(), cards[i].rend());
    
    for(int i = 0; i < K; i++){
        int curIncDim = getLargestDim();
        cout << (char)('A' + curIncDim) << ' ' << cards[curIncDim][index[curIncDim]] << '\n';
        hyperCube[curIncDim] += cards[curIncDim][index[curIncDim]];
        index[curIncDim] += 1;
    }

}

int getLargestDim(){

    long long maxIncreaseVolume = 0;
    int maxIncVolInd;
    
    for(int i = 0; i < 4; i++){
        if(cards[i].size() == index[i]) continue;

        long long curVolIncrease = cards[i][index[i]];
        for(int j = 0; j < 4; j++){
            if(j == i) continue;
            curVolIncrease *= hyperCube[j];
        }

        if(maxIncreaseVolume < curVolIncrease){
            maxIncreaseVolume = curVolIncrease;
            maxIncVolInd = i;
        }
    }
    
    return maxIncVolInd;
}