//2h 17m 44s

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void maxSeatNum_firstLine(vector<vector<bool>> ifCanSit, int curLine, int curJ, int tot);
void maxSeatNum(vector<vector<bool>> ifCanSit, int curLine, int curJ, int tot);
vector<vector<bool>> updateSeats(vector<vector<bool>> ifCanSit, int i, int j);

int maxTot = 0;

int main() {

    int C;
    cin >> C;
    for (int c = 0; c < C; c++) {
        int N, M;
        cin >> N >> M;
        vector<string> classRoom(N);
        for (int i = 0; i < N; i++)
            cin >> classRoom[i];

        vector<vector<bool>> ifCanSit(N, vector<bool>(M, true));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (classRoom[i][j] == 'x') ifCanSit[i][j] = false;
        maxTot = 0;
        maxSeatNum_firstLine(ifCanSit, ifCanSit.size() - 1, -1, 0);
        cout << maxTot << endl;

    }

}

void maxSeatNum_firstLine(vector<vector<bool>> ifCanSit, int curLine, int curJ, int tot) {

    for (curJ = curJ + 1; curJ < ifCanSit[0].size(); curJ++)
        if (ifCanSit[curLine][curJ])
            break;

    if (curJ == ifCanSit[0].size()) {
        maxSeatNum(ifCanSit, curLine - 1, -1, tot);
    }
    else {
        maxSeatNum_firstLine(updateSeats(ifCanSit, curLine, curJ), curLine, curJ, tot + 1);
        maxSeatNum_firstLine(ifCanSit, curLine, curJ, tot);
    }
}

void maxSeatNum(vector<vector<bool>> ifCanSit, int curLine, int curJ, int tot) {

    if (curLine == -1) {
        if (maxTot < tot)
            maxTot = tot;
        return;
    }

    for (curJ = curJ + 1; curJ < ifCanSit[0].size(); curJ++)
        if (ifCanSit[curLine][curJ])
            break;

    if (curJ == ifCanSit[0].size()) {
        maxSeatNum(ifCanSit, curLine - 1, -1, tot);
    }
    else if (curJ == ifCanSit[0].size() - 1) {
        maxSeatNum(updateSeats(ifCanSit, curLine, curJ), curLine - 1, -1, tot + 1);
    }
    else {
        maxSeatNum(updateSeats(ifCanSit, curLine, curJ), curLine, curJ + 1, tot + 1);

        if (ifCanSit[curLine][curJ + 1]) {
            maxSeatNum(updateSeats(ifCanSit, curLine, curJ + 1), curLine, curJ + 1, tot + 1);
        }
    }


}

vector<vector<bool>> updateSeats(vector<vector<bool>> ifCanSit, int i, int j) {
    vector<vector<bool>> newIfCanSit(ifCanSit.size());
    for (int i = 0; i < ifCanSit.size(); i++)
        newIfCanSit[i] = ifCanSit[i];

    //좌
    if (j != 0) {
        //좌
        newIfCanSit[i][j - 1] = false;

        //좌앞
        if (i != 0) newIfCanSit[i - 1][j - 1] = false;
    }

    //우
    if (j != (ifCanSit[0].size() - 1)) {
        //우
        newIfCanSit[i][j + 1] = false;

        //좌앞
        if (i != 0) newIfCanSit[i - 1][j + 1] = false;
    }

    newIfCanSit[i][j] = false;

    return newIfCanSit;
}

/*
1
10 10
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
*/