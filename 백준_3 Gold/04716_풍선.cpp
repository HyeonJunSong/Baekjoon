////230527
//이해 및 설계 : 12m 20s
//입력 : 4m 6s
//구현 : 8m 29s

//tot : 24m 55s

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void testCase(int N, int A, int B);
bool comp(pair<int, pair<int, int>> A, pair<int, pair<int, int>> B);

int main(){
    while(true){
        int N, A, B;
        cin >> N >> A >> B;
        if(N == 0) break;
        testCase(N, A, B);
    }
    return 0;
}

void testCase(int N, int A, int B){
    vector<pair<int, pair<int, int>>> teams(N);
    for(int i = 0; i < N; i++)
        cin >> teams[i].first >> teams[i].second.first >> teams[i].second.second;
    
    sort(teams.begin(), teams.end(), comp);

    int totDistance = 0;

    for(int i = 0; i < N; i++){
        if(teams[i].second.first < teams[i].second.second){

            if(A == 0){
                totDistance += teams[i].first * teams[i].second.second;
                B -= teams[i].first;
            }
            else if(A - teams[i].first < 0){
                totDistance += A * teams[i].second.first;
                totDistance += (teams[i].first - A) * teams[i].second.second;
                B -= (teams[i].first - A);
                A = 0;
            }
            else{
                totDistance += teams[i].first * teams[i].second.first;
                A -= teams[i].first;
            }

        }
        else{

            if(B == 0){
                totDistance += teams[i].first * teams[i].second.first;
                A -= teams[i].first;
            }
            else if(B - teams[i].first < 0){
                totDistance += B * teams[i].second.second;
                totDistance += (teams[i].first - B) * teams[i].second.first;
                A -= (teams[i].first - B);
                B = 0;
            }
            else{
                totDistance += teams[i].first * teams[i].second.second;
                B -= teams[i].first;
            }

        }
    }

    cout << totDistance << endl;

    return;
}

bool comp(pair<int, pair<int, int>> A, pair<int, pair<int, int>> B){
    return abs(A.second.first - A.second.second) > abs(B.second.first - B.second.second);
}