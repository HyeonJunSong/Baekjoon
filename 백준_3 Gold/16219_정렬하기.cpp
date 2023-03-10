////23.03.10
//이해 및 설계 : 19m 23s
//입력 : 03m 11s
//구현 : 28m 42s

//tot : 51m 18s

#include <iostream>
#include <vector>

using namespace std;

int main(){

    int N;
    cin >> N;
    
    vector<int> S(N);
    for(int i = 0; i < N; i++)
        cin >> S[i];
    
    int M;
    cin >> M;
    vector<pair<int, int>> XY(M, {0, 0});
    for(int i = 0; i < M; i++)
        cin >> XY[i].first >> XY[i].second;

    if(N == 1){
        for(int i = 0; i < M; i++)
            cout << "0 ";
    }
    else if(N == 2){
        for(int i = 0; i < M; i++){
            //swap
            int temp = S[XY[i].first];
            S[XY[i].first] = S[XY[i].second];
            S[XY[i].second] = temp;

            if(S[0] != 0) cout << "1 ";
            else cout << "0 ";
        }
    }
    else{
        int temp;
        bool ifAranged = true;
        for(int j = 0; j < N; j++){
            if(S[j] != j){
                ifAranged = false;
                break;
            }
        }

        for(int i = 0; i < M; i++){
            if(XY[i].first != XY[i].second){
                //swap
                temp = S[XY[i].first];
                S[XY[i].first] = S[XY[i].second];
                S[XY[i].second] = temp;

                if(ifAranged){
                    ifAranged = false;
                }
                else{
                    //정렬 돼있는지 확인
                    ifAranged = true;
                    for(int j = 0; j < N; j++){
                        if(S[j] != j){
                            ifAranged = false;
                            break;
                        }
                    }
                }
            }


            if(ifAranged)
                cout << 0 << ' ';
            else
                cout << -1 << ' ';
        }
    }   
}