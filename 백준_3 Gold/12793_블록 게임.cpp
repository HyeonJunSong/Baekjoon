#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int N, M, K;

//빈공간 : -1
//블럭 : 0(번호 부여 전) or 번호
vector<vector<int>> board;
vector<vector<bool>> visited;

//블럭번호 매기기
int blockNum = 0;
int dir[4][2] = {
    { 0, -1},
    {-1,  0},
    { 0,  1},
    { 1,  0},
};

void numberBlocksRec(int i, int j){
    visited[i][j] = true;
    board[i][j] = blockNum;

    for(int d = 0; d < 4; d++){
        if(0 <= i + dir[d][0] && i + dir[d][0] < M
        && 0 <= j + dir[d][1] && j + dir[d][1] < N
        && !visited[i + dir[d][0]][j + dir[d][1]]
        && board[i + dir[d][0]][j + dir[d][1]] == 0)
            numberBlocksRec(i + dir[d][0], j + dir[d][1]);
    }
}

void numberBlocks(){
    visited = vector<vector<bool>>(M, vector<bool>(N, false));

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(visited[i][j] || board[i][j] != 0) continue;
            blockNum++;
            numberBlocksRec(i, j);
        }
    }
}


int main(){

    float inpK;
    cin >> N >> M >> inpK;

    N = 2 * N + 1;
    M = 2 * M + 1;
    K = inpK * 2;

    vector<string> inpBoard(M);
    for(int i = 0; i < M; i++)
        cin >> inpBoard[i];
    board = vector<vector<int>>(M, vector<int>(N));

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            switch(inpBoard[i][j]){
                case 'B':
                case '.':
                    board[i][j] = 0;
                    break;
                default:
                    board[i][j] = -1;
                    break;
            }
        }
    }

    numberBlocks();


    // for(auto e: board){
    //     for(auto e2: e)
    //         printf("%2d ", e2);
    //     cout << endl;
    // }
    reverse(board.begin(), board.end());

    int curI = 0, curJ = K;
    int dI = 1;
    int dJ = -1;
    set<int> blockNumSet;
    while(true){
        // cout << curJ << ' ' << curI << endl;

        if(curJ == 0 || curJ == N - 1) dJ *= -1;
        if(curI == M - 1) dI *= -1;
        
        int nexI = curI + dI;
        int nexJ = curJ + dJ;

        if(board[curI][curJ] != -1)
            blockNumSet.insert(board[curI][curJ]);
        if(board[nexI][curJ] != -1)
            blockNumSet.insert(board[nexI][curJ]);
        if(board[curI][nexJ] != -1)
            blockNumSet.insert(board[curI][nexJ]);

        if(nexI == 0) break;

        curI = nexI;
        curJ = nexJ;
    }

    cout << blockNumSet.size();

    return 0;
}