////23.07.03
//이해 및 설계 : 3m 35s
//입력 : 5m 51s
//구현 : 38m
//tot : 47m 26s

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int dir[4][2] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

class node{
public:
    int i;
    int j;
    bool ifWallDestroied;
    int passedBlockNum;

    node(int i, int j, bool ifWallDestroied, int passedBlockNum){
        this->i = i;
        this->j = j;
        this->ifWallDestroied = ifWallDestroied;
        this->passedBlockNum = passedBlockNum;
    }

    bool operator< (node b) const{
        return passedBlockNum > b.passedBlockNum;
    }
};

int main(){
    int N, M;
    cin >> N >> M;

    vector<string> map(N);
    for(int i = 0; i < N; i++)
        cin >> map[i];
    
    priority_queue<node> PQ;
    PQ.push(node(0, 0, false, 1));

    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<bool>> visited_distroied(N, vector<bool>(M, false));

    int ans = -1;

    while(!PQ.empty()){
        node curNode = PQ.top();
        PQ.pop();

        if(curNode.i == N-1 && curNode.j == M-1){
            ans = curNode.passedBlockNum;
            break;
        }


        if(curNode.ifWallDestroied){
            if(visited_distroied[curNode.i][curNode.j]) continue;
            visited_distroied[curNode.i][curNode.j] = true;
        }
        else{
            if(visited[curNode.i][curNode.j]) continue;
            visited[curNode.i][curNode.j] = true;
        }

        for(int d = 0; d < 4; d++){
            if(0 <= curNode.i + dir[d][0] && curNode.i + dir[d][0] < N
            && 0 <= curNode.j + dir[d][1] && curNode.j + dir[d][1] < M){
                if(curNode.ifWallDestroied && !visited_distroied[curNode.i + dir[d][0]][curNode.j + dir[d][1]]){
                    if(map[curNode.i + dir[d][0]][curNode.j + dir[d][1]] == '0'){
                        PQ.push(node(curNode.i + dir[d][0], curNode.j + dir[d][1], curNode.ifWallDestroied, curNode.passedBlockNum + 1));
                    }
                }
                else if(!curNode.ifWallDestroied){
                    if(map[curNode.i + dir[d][0]][curNode.j + dir[d][1]] == '1'){
                        if(!visited_distroied[curNode.i + dir[d][0]][curNode.j + dir[d][1]])
                            PQ.push(node(curNode.i + dir[d][0], curNode.j + dir[d][1], true, curNode.passedBlockNum + 1));
                    }
                    else{
                        if(!visited[curNode.i + dir[d][0]][curNode.j + dir[d][1]])
                           PQ.push(node(curNode.i + dir[d][0], curNode.j + dir[d][1], curNode.ifWallDestroied, curNode.passedBlockNum + 1));
                    }
                }
            }
        }
    }
    cout << ans;

    return 0;
}