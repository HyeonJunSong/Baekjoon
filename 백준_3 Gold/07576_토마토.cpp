////23.02.23
//이해 및 설계 : 1m 5s
//입력 : 1m 37s
//구현 : 12m 14s

//tot : 14m 56s

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> dir = {
  {-1,  0},
  { 0,  1},
  { 1,  0},
  { 0, -1,}  
};

int main (){
    int M, N;
    cin >> M >> N;
    vector<vector<int>> box(N, vector<int>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> box[i][j];            
        }
    }

    ////익은 토마토 찾기
    vector<vector<int>> stack;  //vector<int> {i, j}
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(box[i][j] == 1) stack.push_back({i, j});            
        }
    }
    

    ////stack이 빌때까지 토마토 익히며 날짜 지나기
    int days = 0;
    while(true){
        vector<vector<int>> newStack;
        for(auto iter = stack.begin(); iter != stack.end(); iter++){
            for(int d = 0; d < 4; d++){
                if(0 <= (*iter)[0] + dir[d][0] && (*iter)[0] + dir[d][0] < N)
                if(0 <= (*iter)[1] + dir[d][1] && (*iter)[1] + dir[d][1] < M)
                if(box[(*iter)[0] + dir[d][0]][(*iter)[1] + dir[d][1]] == 0){
                    newStack.push_back({(*iter)[0] + dir[d][0], (*iter)[1] + dir[d][1]});
                    box[(*iter)[0] + dir[d][0]][(*iter)[1] + dir[d][1]] = 1;
                }
            }
        }

        stack = newStack;

        if(stack.empty())
            break;
        days++;
    }

    ////안익은 토마토 남은거 있는지 확인
    bool ifNotRipen = false;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(box[i][j] == 0){
                ifNotRipen = true;
                break;
            }
        }
        if(ifNotRipen) break;
    }

    if(ifNotRipen) cout << -1;
    else cout << days;

    return 0;
}