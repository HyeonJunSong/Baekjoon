////22.06.28
//이해 및 설계 : 10m 4s
//입력 : 2m 37s
//구현 : 28m 43s
//
//tot : 14m 24s

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b);

int main(){
    int N;
    cin >> N;
    vector<pair<int, int>> arr;
    for(int i = 0; i < N; i++){
        int inp;
        cin >> inp;
        arr.push_back(make_pair(inp, i));
    }

    sort(arr.begin(), arr.end(), compare);

    vector<pair<int, int>> arr2;

    for(int i = 0; i < N; i++){
        arr2.push_back(make_pair(arr[i].second, i));
    }

    sort(arr2.begin(), arr2.end(), compare);

    for(int i = 0; i < N - 1; i++)
        cout << arr2[i].second << ' ';
    cout << arr2[N - 1].second;

    return 0;
}

bool compare(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}