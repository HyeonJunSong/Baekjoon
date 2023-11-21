#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<vector<int>> conflicts;
vector<int> gh(20);
vector<int> mh(20);

int ghTurn = -1;
int mhTurn = -1;
int jwTurn = 0;
int notTurn = 2;  //0:지우 1:경희 2:민호

vector<bool> ifDone;
int jwWonCnt = 0;
int ghWonCnt = 0;
int mhWonCnt = 0;

bool retIfWinnable() {

    if (jwTurn == N) {
        if (jwWonCnt >= K) return true;
        else return false;
    }
    if (jwWonCnt >= K || ghWonCnt >= K || mhWonCnt >= K)
        return false;

    switch (notTurn)
    {
    case 0:
        ghTurn++;
        mhTurn++;
        switch (conflicts[gh[ghTurn]][mh[mhTurn]]) {
        case 0:
        case 1:
            notTurn = 1;
            mhWonCnt++;
            if (retIfWinnable())
                return true;
            mhWonCnt--;
            break;
        case 2:
            notTurn = 2;
            ghWonCnt++;
            if (retIfWinnable())
                return true;
            ghWonCnt--;
            break;
        }
        ghTurn--;
        mhTurn--;
        return false;

    case 1:
        jwTurn++;
        mhTurn++;
        for (int i = 1; i <= N; i++) {
            if (ifDone[i]) continue;
            ifDone[i] = true;

            switch (conflicts[i][mh[mhTurn]]) {
            case 0:
            case 1:
                notTurn = 0;
                mhWonCnt++;
                if (retIfWinnable())
                    return true;
                mhWonCnt--;
                break;
            case 2:
                notTurn = 2;
                jwWonCnt++;
                if (retIfWinnable())
                    return true;
                jwWonCnt--;
                break;
            }
            ifDone[i] = false;
        }
        jwTurn--;
        mhTurn--;
        return false;

    case 2:
        jwTurn++;
        ghTurn++;
        for (int i = 1; i <= N; i++) {
            if (ifDone[i]) continue;
            ifDone[i] = true;

            switch (conflicts[i][gh[ghTurn]]) {
            case 0:
            case 1:
                notTurn = 0;
                ghWonCnt++;
                if (retIfWinnable())
                    return true;
                ghWonCnt--;
                break;
            case 2:
                notTurn = 1;
                jwWonCnt++;
                if (retIfWinnable())
                    return true;
                jwWonCnt--;
                break;
            }
            ifDone[i] = false;
        }
        jwTurn--;
        ghTurn--;
        return false;
    }
}

int main() {

    cin >> N >> K;

    conflicts = vector<vector<int>>(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> conflicts[i][j];

    for (int i = 0; i < 20; i++)
        cin >> gh[i];
    for (int i = 0; i < 20; i++)
        cin >> mh[i];

    ifDone = vector<bool>(N + 1, false);

    cout << retIfWinnable();

    return 0;
}