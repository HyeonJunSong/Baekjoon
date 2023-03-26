////230326
//이해 및 설계 : 11m 43s
//입력 : 2m 57s
//구현 : 11m 22s

//tot : 26m 2s

#include <iostream>
#include <vector>

using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<vector<int>> houses(N, vector<int>(3));
    for(int i = 0; i < N; i++)
        cin >> houses[i][0] >> houses[i][1] >> houses[i][2];

    int ans = 987654321;
    vector<int> prev(3);
    vector<int> cur(3);
    
    //첫집이 R일때 최소
    prev[0] = 987654321;
    prev[1] = houses[N - 1][1];
    prev[2] = houses[N - 1][2];

    for(int i = N - 2; i > 0; i--){
        cur[0] = prev[1] < prev[2] ? prev[1] : prev[2];
        cur[1] = prev[0] < prev[2] ? prev[0] : prev[2];
        cur[2] = prev[1] < prev[0] ? prev[1] : prev[0];
        
        prev[0] = cur[0] + houses[i][0];
        prev[1] = cur[1] + houses[i][1];
        prev[2] = cur[2] + houses[i][2];
    }
    if(prev[1] < prev[2]){
        if(ans > houses[0][0] + prev[1])
            ans = houses[0][0] + prev[1];
    }
    else{
        if(ans > houses[0][0] + prev[2])
            ans = houses[0][0] + prev[2];
    }

    //첫집이 G일때 최소
    prev[1] = 987654321;
    prev[2] = houses[N - 1][2];
    prev[0] = houses[N - 1][0];

    for(int i = N - 2; i > 0; i--){
        cur[0] = prev[1] < prev[2] ? prev[1] : prev[2];
        cur[1] = prev[0] < prev[2] ? prev[0] : prev[2];
        cur[2] = prev[1] < prev[0] ? prev[1] : prev[0];
        
        prev[0] = cur[0] + houses[i][0];
        prev[1] = cur[1] + houses[i][1];
        prev[2] = cur[2] + houses[i][2];
    }
    if(prev[2] < prev[0]){
        if(ans > houses[0][1] + prev[2])
            ans = houses[0][1] + prev[2];
    }
    else{
        if(ans > houses[0][1] + prev[0])
            ans = houses[0][1] + prev[0];
    }

    //첫집이 B일때 최소
    prev[2] = 987654321;
    prev[0] = houses[N - 1][0];
    prev[1] = houses[N - 1][1];

    for(int i = N - 2; i > 0; i--){
        cur[0] = prev[1] < prev[2] ? prev[1] : prev[2];
        cur[1] = prev[0] < prev[2] ? prev[0] : prev[2];
        cur[2] = prev[1] < prev[0] ? prev[1] : prev[0];
        
        prev[0] = cur[0] + houses[i][0];
        prev[1] = cur[1] + houses[i][1];
        prev[2] = cur[2] + houses[i][2];
    }
    if(prev[0] < prev[1]){
        if(ans > houses[0][2] + prev[0])
            ans = houses[0][2] + prev[0];
    }
    else{
        if(ans > houses[0][2] + prev[1])
            ans = houses[0][2] + prev[1];
    }

    cout << ans;

    return 0;
}