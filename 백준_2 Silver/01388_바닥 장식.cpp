#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){

    int N, M;
    cin >> N >> M;

    vector<string> room(N);
    for(int i = 0; i < N; i++)
        cin >> room[i];
    
    vector<vector<bool> > ifColored(N, vector<bool>(M, false));
    int coloredNum = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(ifColored[i][j]) continue;

            if(room[i][j] == '-')
                for(int k = 1; j + k < M && room[i][j + k] == '-'; k++) ifColored[i][j + k] = true;
            else
                for(int k = 1; i + k < N && room[i + k][j] == '|'; k++) ifColored[i + k][j] = true;

            coloredNum++;
        }
    }
    
    cout << coloredNum;


    return 0;
}