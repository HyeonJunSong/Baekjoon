#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int main(){
    int N, L;
    cin >> N >> L;

    vector<pair<int, int>> pools(N);
    for(int i = 0; i < N; i++)
        cin >> pools[i].first >> pools[i].second;
    
    sort(pools.begin(), pools.end(), comp);

    int cnt = 1;
    int curBoardEnd = pools[0].first + L;
    for(int i = 0; i < N; i++){
        if(curBoardEnd >= pools[i].second) continue;

        if(curBoardEnd <= pools[i].first)
            curBoardEnd = pools[i].first + L;
        else
            curBoardEnd += L;
        i--;
        cnt++;
    }

    cout << cnt;

    return 0;
}