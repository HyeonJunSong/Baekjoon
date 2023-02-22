////23.02.22
//이해 및 설계 : 5m 36s
//입력 : 3m 22s
//구현 : 25m 43s

//tot : 34m 41s

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> dir = {
    {-1,  0,  0},
    { 0, -1,  0},
    { 0,  0,  1},
    { 0,  1,  0},
    { 0,  0, -1},
    { 1,  0,  0}
};

int main(){
    int M, N, H;
    cin >> M >> N >> H;
    vector<vector<vector<int>>> box(H, vector<vector<int>>(N, vector<int>(M)));

    for(int h = 0; h < H; h++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                cin >> box[h][i][j];
            }
        }
    }

    vector<vector<int>> ripen; //ripen element = vector<int>(3) {h, i, j}
    //한번 돌면서 익은지 검사
    for(int h = 0; h < H; h++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(box[h][i][j] == 1)
                    ripen.push_back({h, i, j});
            }
        }
    }

    //ripen에 아무것도 추가 안될때까지 while문 돌며 days 체크
    int days = -1;
    while(!ripen.empty()){
        vector<vector<int>> newRipen;
        for(auto iter = ripen.begin(); iter != ripen.end(); iter++){
            for(int d = 0; d < 6; d++){
                if(0 <= (*iter)[0] + dir[d][0] && (*iter)[0] + dir[d][0] < H)
                if(0 <= (*iter)[1] + dir[d][1] && (*iter)[1] + dir[d][1] < N)
                if(0 <= (*iter)[2] + dir[d][2] && (*iter)[2] + dir[d][2] < M)
                if(box[(*iter)[0] + dir[d][0]][(*iter)[1] + dir[d][1]][(*iter)[2] + dir[d][2]] == 0){
                    newRipen.push_back({(*iter)[0] + dir[d][0], (*iter)[1] + dir[d][1], (*iter)[2] + dir[d][2]});
                    box[(*iter)[0] + dir[d][0]][(*iter)[1] + dir[d][1]][(*iter)[2] + dir[d][2]] = 1;
                }                
            }
        }
        ripen = newRipen;
        days++;
    }

    //안익은게 남았는지 검사
    bool ifUnRipenLeft = false;
    for(int h = 0; h < H; h++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(box[h][i][j] == 0){
                    ifUnRipenLeft = true;
                    break;
                }
            }
            if(ifUnRipenLeft) break;
        }
        if(ifUnRipenLeft) break;
    }


    //리턴
    if(ifUnRipenLeft)
        cout << -1;
    else
        cout << days;

    return 0;
}