////230316
//이해 및 설계 : 4m 59s
//입력 : 3m 23s
//구현 : 37m 23s

//tot : 45m 45s

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class node{
public:
    int i;
    int j;
    int moved;
    node(int i, int j, int moved){
        this->i = i;
        this->j = j;
        this->moved = moved;
    }

    bool operator<(node b) const{
        return this->moved > b.moved;
    }
};

int dir[4][2] = {
    { 0, -1},
    {-1,  0},
    { 0,  1},
    { 1,  0}
};

int main(){

    int N, M;
    cin >> N >> M;

    vector<string> maze(N);
    for(int i = 0; i < N; i++)
        cin >> maze[i];
    
    priority_queue<node> PQ;
    for(int i = 1; i < N; i++){
        for(int j = 1; j < N; j++){
            if(maze[i][j] == 'S'){
                PQ.push(node(i, j, 0));
                break;
            }
        }
        if(!PQ.empty()) break;
    }

    int ans = 0;
    int keyLeft = M;

    vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));

    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();

        if(visited[curNode.i][curNode.j]) continue;
        visited[curNode.i][curNode.j] = true;

        if(maze[curNode.i][curNode.j] == 'K'){
            ans += curNode.moved;
            curNode.moved = 0;
            keyLeft--;
            maze[curNode.i][curNode.j] == '0';
            if(keyLeft == 0) break;
        }

        for(int d = 0; d < 4; d++){
            if(1 <= curNode.i + dir[d][0] && curNode.i + dir[d][0] < N - 1
            && 1 <= curNode.j + dir[d][1] && curNode.j + dir[d][1] < N - 1
            && !visited[curNode.i + dir[d][0]][curNode.j + dir[d][1]]
            && maze[curNode.i + dir[d][0]][curNode.j + dir[d][1]] != '1'){
                PQ.push(node(curNode.i + dir[d][0], curNode.j + dir[d][1], curNode.moved + 1));
            }
        }
    }

    if(keyLeft == 0)
        cout << ans;
    else
        cout << -1;

    return 0;
}