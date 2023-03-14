////알고리즘은 문제없으나, long long 넘어가는 경우가 있어 오답.
////그대로 파이썬으로 옮겼음

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair<long long, long long> a, pair<long long, long long> b){
    return a.first < b.first;
}

int main(){
    int N;
    cin >> N;
    vector<pair<long long, long long>> villages(N);
    for(int i = 0; i < N; i++)
        cin >> villages[i].first >> villages[i].second;

    bool ifEveryThing0 = true;
    for(int i = 0; i < N; i++){
        if(villages[i].second != 0){
            ifEveryThing0 = false;
            break;
        }
    }
    if(ifEveryThing0){
        cout << -1000000000;
        return 0;
    }


    sort(villages.begin(), villages.end(), comp);

    vector<long long> sum_front(N);
    vector<long long> sum_back(N);
    sum_front[0] = villages[0].second;
    sum_back[N - 1] = villages[N - 1].second;
    
    for(int i = 1; i < N; i++){
        sum_front[i] = sum_front[i - 1] + villages[i - 1].second;
        sum_back[N - i - 1] = sum_back[N - i] + villages[N - i].second;
    }

    int ans = 0;
    int ansInd = 0;
    int prevResult = 0;

    for(int i = 1; i < N; i++){
        prevResult += sum_front[i - 1] * (villages[i].first - villages[i - 1].first);
        prevResult -= sum_back[i] * (villages[i].first - villages[i - 1].first);

        if(prevResult < ans){
            ans = prevResult;
            ansInd = i;
        }
    }

    cout << villages[ansInd].first;
    return 0;
}
