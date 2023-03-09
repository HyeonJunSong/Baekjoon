#include <iostream>
#include <vector>

using namespace std;

int dir[8][2] = {
    {-1,  0},
    {-1, -1},
    { 0, -1},
    { 1, -1},
    { 1,  0},
    { 1,  1},
    { 0,  1},
    {-1,  1}
};

void moveFish(vector<vector<pair<int, int>>>& fishes);

int main() {

    vector<vector<pair<int, int>>> fishes(4, vector<pair<int, int>>(4, pair<int, int>()));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> fishes[i][j].first;
            cin >> fishes[i][j].second;
            fishes[i][j].second--;
        }
    }

    vector<pair<vector<vector<pair<int, int>>>, int>> stack;
    int maxNum = fishes[0][0].first;
    fishes[0][0].first = 0;
    moveFish(fishes);
    stack.push_back({ fishes, maxNum });

    while (!stack.empty()) {
        auto curNode = stack.back();
        stack.pop_back();

        //상어 찾기
        int i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++)
                if (curNode.first[i][j].first == 0)
                    break;
            if (j < 4 && curNode.first[i][j].first == 0)
                break;
        }
        //이동할 수 있는 곳 몰색
        int curFishNum = 0;
        int curDir = curNode.first[i][j].second;
        for (int k = 1; k <= 3; k++) {
            if (0 <= i + k * dir[curDir][0] && i + k * dir[curDir][0] < 4
                && 0 <= j + k * dir[curDir][1] && j + k * dir[curDir][1] < 4) {
                if (curNode.first[i + k * dir[curDir][0]][j + k * dir[curDir][1]].first != -1) {
                    vector<vector<pair<int, int>>> newFishes = curNode.first;
                    curFishNum = newFishes[i + k * dir[curDir][0]][j + k * dir[curDir][1]].first + curNode.second;
                    newFishes[i][j].first = -1;
                    newFishes[i + k * dir[curDir][0]][j + k * dir[curDir][1]].first = 0;
                    moveFish(newFishes);
                    stack.push_back({
                        newFishes, curFishNum
                    });
                }
            }
            else break;
        }
        if (curFishNum == 0) {
            if (maxNum < curNode.second)
                maxNum = curNode.second;
        }
    }

    cout << maxNum;
    return 0;
}

void moveFish(vector<vector<pair<int, int>>>& fishes) {
    vector<pair<int, int>> fishToMove(17, pair<int, int>(-1, -1));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (fishes[i][j].first > 0) {
                fishToMove[fishes[i][j].first].first = i;
                fishToMove[fishes[i][j].first].second = j;
            }
        }
    }

    for (int i = 1; i <= 16; i++) {
        if (fishToMove[i].first == -1) continue;

        for (int d = 0; d < 8; d++) {
            int curDir = (fishes[fishToMove[i].first][fishToMove[i].second].second + d) % 8;
            if (0 <= fishToMove[i].first + dir[curDir][0] && fishToMove[i].first + dir[curDir][0] < 4
                && 0 <= fishToMove[i].second + dir[curDir][1] && fishToMove[i].second + dir[curDir][1] < 4
                && fishes[fishToMove[i].first + dir[curDir][0]][fishToMove[i].second + dir[curDir][1]].first != 0) {
                fishes[fishToMove[i].first][fishToMove[i].second].second = curDir;
                if (fishes[fishToMove[i].first + dir[curDir][0]][fishToMove[i].second + dir[curDir][1]].first == -1) {
                    pair<int, int> temp = fishes[fishToMove[i].first + dir[curDir][0]][fishToMove[i].second + dir[curDir][1]];
                    fishes[fishToMove[i].first + dir[curDir][0]][fishToMove[i].second + dir[curDir][1]] = fishes[fishToMove[i].first][fishToMove[i].second];
                    fishes[fishToMove[i].first][fishToMove[i].second] = temp;
                }
                else {
                    pair<int, int> temp = fishes[fishToMove[i].first + dir[curDir][0]][fishToMove[i].second + dir[curDir][1]];
                    fishes[fishToMove[i].first + dir[curDir][0]][fishToMove[i].second + dir[curDir][1]] = fishes[fishToMove[i].first][fishToMove[i].second];
                    fishes[fishToMove[i].first][fishToMove[i].second] = temp;

                    fishToMove[temp.first].first = fishToMove[i].first;
                    fishToMove[temp.first].second = fishToMove[i].second;
                }
                break;
            }
        }
    }
}