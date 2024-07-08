#include <iostream>
#include <vector>

using namespace std;

int N, M, A, B;
vector<vector<int>> board;

vector<vector<int>> memo;

int getAns(int I, int J){

    if(J == M - 1){
        for(int i = I; i < N; i++)
            if(board[i][J] == 2) return 0;
        return 1;
    }

    //옆으로 넘어갈 수 있는 최소 I구하기
    int minNextI = I;
    bool obstacticleAppeared = false;
    for(int i = I; i < N; i++){
        if(board[i][J] == 1){
            if(obstacticleAppeared) return 0;
            minNextI = i;
        }
        if(board[i][J] == 2)
            obstacticleAppeared = true;
    }

    //다음 라인에 지금 I 아래에 아이템이 있는지 확인
    for(int i = I - 1; i >= 0; i--){
        if(board[i][J + 1] == 1) return 0;
    }

    int ans = 0;
    if(board[minNextI][J + 1] != 2){
        if(memo[minNextI][J + 1] == -1)
            memo[minNextI][J + 1] = getAns(minNextI, J + 1);
        ans += memo[minNextI][J + 1];
    }
    if(minNextI < N - 1 && board[minNextI + 1][J] != 2){
        if(memo[minNextI + 1][J] == -1)
            memo[minNextI + 1][J] = getAns(minNextI + 1, J);
        ans += memo[minNextI + 1][J];
    }

    return ans;
}

int main(){

    cin >> N >> M >> A >> B;

    board = vector<vector<int>>(N, vector<int>(M, 0));
    for(int i = 0; i < A; i++){
        int I, J;
        cin >> I >> J;
        I--;J--;
        board[I][J] = 1;
    }
    for(int i = 0; i < B; i++){
        int I, J;
        cin >> I >> J;
        I--;J--;
        board[I][J] = 2;
    }

    memo = vector<vector<int>>(N, vector<int>(M, -1));
    cout << getAns(0, 0);


    return 0;
}