#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

vector<vector<char>> board;

int dir[4][2] = {
    {-1,  0},
    { 0,  1},
    { 1,  0},
    { 0, -1},
};

class node{
public:
    int cnt;
    pair<int, int> red;
    pair<int, int> blue;

    node(int cnt, pair<int, int> red, pair<int, int> blue){
        this->cnt = cnt;
        this->red = red;
        this->blue = blue;
    }

    bool operator< (node b) const{
        return cnt > b.cnt;
    }
};

node tiltBoard(pair<int, int> red, pair<int, int> blue, int d);

int main(){

    int N, M;
    cin >> N >> M;

    board = vector<vector<char>>(N, vector<char>(M));
    node firstNode = node(0, pair<int, int>(), pair<int, int>());

    string inpStr;
    for(int i = 0; i < N; i++){
        cin >> inpStr;
        for(int j = 0; j < M; j++){
            if(inpStr[j] == 'R'){
                firstNode.red.first = i;
                firstNode.red.second = j;
                board[i][j] = '.';
            }
            else if(inpStr[j] == 'B'){
                firstNode.blue.first = i;
                firstNode.blue.second = j;
                board[i][j] = '.';
            }
            else{
                board[i][j] = inpStr[j];
            }
        }
    }

    priority_queue<node> PQ;
    PQ.push(firstNode);

    vector<vector<bool>> visited(N * M, vector<bool>(N * M, false));
    
    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();

        if(visited[curNode.red.first * M + curNode.red.second][curNode.blue.first * M + curNode.blue.second]) continue;
        visited[curNode.red.first * M + curNode.red.second][curNode.blue.first * M + curNode.blue.second] = true;

        for(int d = 0; d < 4; d++){
            if(visited[(curNode.red.first + dir[d][0]) * M + (curNode.red.second + dir[d][1])][(curNode.blue.first + dir[d][0]) * M + (curNode.blue.second + dir[d][1])]) continue;

            node afterTilt = tiltBoard(curNode.red, curNode.blue, d);
            if(afterTilt.cnt == -1) continue;
            if(afterTilt.cnt == 1){
                cout << curNode.cnt + 1;
                return 0;
            }
            afterTilt.cnt = curNode.cnt + 1;
            PQ.push(afterTilt);
        }
    }

    cout << -1;

    return 0;
}

//보드 기울이는 작업을 해주는 함수.
//보드 초기화할때 구슬은 빼놓고, tiltBoard 함수 인자로 구슬들 위치와 기울임 방향을 줌
//기울인 후의 구슬 위치를 node 객체로 반환.
//리턴 node의 cnt
//  1 : 빨강만 탈출
//  0 : 아무 구슬도 탈출못함
// -1 : 파랑 탈출 혹은 같이 탈출
node tiltBoard(pair<int, int> red, pair<int, int> blue, int d){

    node ret = node(0, red, blue);

    //파랑먼저 할지 빨강먼저 할지 결정
    if(blue.first * dir[d][0] + blue.second * dir[d][1] < red.first * dir[d][0] + red.second * dir[d][1]){
        while(board[red.first + dir[d][0]][red.second + dir[d][1]] == '.'){
            red.first += dir[d][0];
            red.second += dir[d][1];
        }

        if(board[red.first + dir[d][0]][red.second + dir[d][1]] == 'O'){
            ret.cnt = 1;
            red.first = -1;
            red.second = -1;
        }

        while(board[blue.first + dir[d][0]][blue.second + dir[d][1]] == '.'){
            if(blue.first + dir[d][0] == red.first && blue.second + dir[d][1] == red.second) break;
            blue.first += dir[d][0];
            blue.second += dir[d][1];
        }
        if(board[blue.first + dir[d][0]][blue.second + dir[d][1]] == 'O')
            ret.cnt = -1;

    }
    else{
        while(board[blue.first + dir[d][0]][blue.second + dir[d][1]] == '.'){
            blue.first += dir[d][0];
            blue.second += dir[d][1];
        }
        if(board[blue.first + dir[d][0]][blue.second + dir[d][1]] == 'O'){
            ret.cnt = -1;
            blue.first = -1;
            blue.second = -1;
        }

        while(board[red.first + dir[d][0]][red.second + dir[d][1]] == '.'){
            if(red.first + dir[d][0] == blue.first && red.second + dir[d][1] == blue.second) break;
            red.first += dir[d][0];
            red.second += dir[d][1];
        }

        if(board[red.first + dir[d][0]][red.second + dir[d][1]] == 'O' && ret.cnt != -1)
            ret.cnt = 1;
    }

    ret.red = red;
    ret.blue = blue;
    return ret;
}