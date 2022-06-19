#include <iostream>
#include <string>

using namespace std;

int main(){
    int N, M;
    cin >> N >> M;

    string* board = new string[N];
    for(int i = 0; i < N; i++)
        cin >> board[i];

    int minChange = 987654321;
    
    for(int i = 0; i < N - 7; i++){
        for(int j = 0; j < M - 7; j++){

            int color_change = 0;

            for(int k = 0; k < 8; k++){
                for(int l = 0; l < 8; l++){
                    if((k + l) % 2){
                        if(board[i + k][j + l] == 'W'){
                            color_change++;
                        }
                    }
                    else{
                        if(board[i + k][j + l] == 'B'){
                            color_change++;
                        }
                    }
                }
            }

            color_change = 64 - color_change < color_change ? 64 - color_change : color_change;

            if(minChange > color_change)
                minChange = color_change;

        }
    }

    cout << minChange;

    return 0;
}