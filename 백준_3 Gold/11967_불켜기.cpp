#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<vector<pair<int, int>>>> switches;

//0 : light offed
//1 : light on, but not visited
//2 : light on and visited
vector<vector<int>> rooms;

int N, M;

int dir[4][2] = {
    { 0,  1},
    { 1,  0},
    { 0, -1},
    {-1,  0},
};

int turnOnLightDFS();

int main(){

    cin >> N >> M;
    switches = vector<vector<vector<pair<int, int>>>>(N + 1, vector<vector<pair<int, int>>>(N + 1));

    for(int i = 0; i < M; i++){
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        switches[x][y].push_back(pair<int, int>(a, b));
    }
    rooms = vector<vector<int>>(N + 1, vector<int>(N + 1, 0));

    rooms[1][1] = 1;
    
    int totTurnedOn = 1;
    int newTurnedOnNum;

    do{
        newTurnedOnNum = turnOnLightDFS();
        totTurnedOn += newTurnedOnNum;
    }while(newTurnedOnNum != 0);

    cout << totTurnedOn;

    return 0;
}

int turnOnLightDFS(){
    vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));

    stack<pair<int, int>> s;
    s.emplace(1, 1);

    int turnedOnNum = 0;

    while(!s.empty()){
        pair<int, int> curNode = s.top();
        s.pop();

        if(visited[curNode.first][curNode.second])
            continue;
        visited[curNode.first][curNode.second] = true;

        //불켜기
        if(rooms[curNode.first][curNode.second] == 1){
            for(auto iter = switches[curNode.first][curNode.second].begin(); iter != switches[curNode.first][curNode.second].end(); iter++){
                if(rooms[iter->first][iter->second] == 0){
                    rooms[iter->first][iter->second] = 1;
                    turnedOnNum++;
                }
            }
            rooms[curNode.first][curNode.second] == 2;
        }

        for(int d = 0; d < 4; d++){
            if(1 <= curNode.first + dir[d][0] && curNode.first + dir[d][0] <= N
            && 1 <= curNode.second + dir[d][1] && curNode.second + dir[d][1] <= N
            && rooms[curNode.first + dir[d][0]][curNode.second + dir[d][1]] >= 1
            && !visited[curNode.first + dir[d][0]][curNode.second + dir[d][1]]){
                s.emplace(curNode.first + dir[d][0], curNode.second + dir[d][1]);
            }
        }
    }

    return turnedOnNum;
}