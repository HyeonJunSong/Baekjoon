#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX 987654321

vector<pair<int, int>> spots;

int dir[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};
vector<string> board(5);

int retMinMove(int I, int movement);
bool checkIfAdjacent();

int main(){

    for(int i = 0; i < 5; i++)
        cin >> board[i];

    //별 위치 벡터로
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == '*'){
                spots.push_back(make_pair(i, j));
            }
        }
    }

    //재귀 돌면서 최소이동횟수 찾기
    cout << retMinMove(0, 0);


}

//재귀함수
int retMinMove(int I, int movement){
    if(I == spots.size()){
        if(checkIfAdjacent()) return 0;
        else return MAX;
    }

    int minMove = MAX;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == '*') continue;

            board[i][j] = '*';
            board[spots[I].first][spots[I].second] = '.';

            int ret = retMinMove(I + 1, movement + abs(spots[I].first - i + spots[I].second - j)) +  + abs(spots[I].first - i + spots[I].second - j);
            if(ret < minMove) minMove = ret;

            board[spots[I].first][spots[I].second] = '*';
            board[i][j] = '.';
        }
    }

    return minMove;
}

//인접한지 확인하는 함수
bool checkIfAdjacent(){

    vector<string> boardCpy = board;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(boardCpy[i][j] == '*'){
                vector<pair<int, int>> stack;
                stack.push_back(make_pair(i, j));
                boardCpy[i][j] = '.';

                int cnt = 1;

                while(!stack.empty()){
                    auto curNode = stack.back();
                    stack.pop_back();

                    for(int i = 0; i < 4; i++){
                        if(0 <= dir[i][0] + curNode.first && dir[i][0] + curNode.first < 5
                         && 0 <= dir[i][1] + curNode.second && dir[i][1] + curNode.second < 5
                         && boardCpy[dir[i][0] + curNode.first][dir[i][1] + curNode.second] == '*'){
                            stack.push_back(make_pair(dir[i][0] + curNode.first, dir[i][1] + curNode.second));
                            boardCpy[dir[i][0] + curNode.first][dir[i][1] + curNode.second] = '.';
                            cnt++;
                        }
                    }
                }

                if(cnt == spots.size()) return true;
                else return false;
            }
        }
    }

}