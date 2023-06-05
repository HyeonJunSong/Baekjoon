#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> wishList;

vector<int> cowNumInBarn;

bool assignBarn(int cowNum, vector<bool>& visited);

int main() {
    int N, M;
    cin >> N >> M;

    wishList = vector<vector<int>>(N);
    for (int i = 0; i < N; i++) {
        int S;
        cin >> S;
        for (int j = 0; j < S; j++) {
            int wish;
            cin >> wish;

            wishList[i].push_back(wish);
        }
    }

    cowNumInBarn = vector<int>(M + 1, -1);

    for (int i = 0; i < N; i++){
        vector<bool> visited(M + 1, false);
        assignBarn(i, visited);
    }

    int cnt = 0;
    for (int i = 1; i <= M; i++)
        if (cowNumInBarn[i] != -1)
            cnt++;
    cout << cnt;

    return 0;
}

bool assignBarn(int cowNum, vector<bool>& visited) {

    for (int i = 0; i < wishList[cowNum].size(); i++) {
        if(visited[wishList[cowNum][i]]) continue;

        visited[wishList[cowNum][i]] = true;        
        if (cowNumInBarn[wishList[cowNum][i]] == -1
        || assignBarn(cowNumInBarn[wishList[cowNum][i]], visited)){
            cowNumInBarn[wishList[cowNum][i]] = cowNum;
            return true;
        }
    }

    return false;
}