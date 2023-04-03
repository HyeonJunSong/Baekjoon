#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<int, int> a, pair<int, int> b){
    return a.second > b.second;
}

int main(){

    int N;
    cin >> N;
    vector<pair<int, int>> works(N, pair<int, int>());

    for(int i = 0; i < N; i++)
        cin >> works[i].first >> works[i].second;
    
    sort(works.begin(), works.end(), comp);

    int curEndTime = works[0].second - works[0].first;
    for(int i = 1; i < N; i++){
        if(curEndTime > works[i].second)
            curEndTime = works[i].second - works[i].first;
        else
            curEndTime = curEndTime - works[i].first;
    }

    if(curEndTime < 0)
        cout << -1;
    else
        cout << curEndTime;

    return 0;
}