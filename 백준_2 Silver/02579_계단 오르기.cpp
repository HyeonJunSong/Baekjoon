#include <iostream>
#include <vector>

using namespace std;


//계단 누적값들. 첫 요소는 이전에 연속된걸 밟았고, 두번째는 아님

int main(){
    int N;
    cin >> N;
    vector<int> stairs;
    stairs = vector<int>(N);
    vector<pair<int, int>> stairAccums;
    stairAccums = vector<pair<int, int>>(N, pair<int, int>(0, 0));
    for(int i = 0; i < N; i++)
        cin >> stairs[i];

    stairAccums[0].first = stairs[0];
    stairAccums[0].second = stairs[0];
    stairAccums[1].first = stairs[0] + stairs[1];
    stairAccums[1].second = stairs[1];

    for(int curStair = 2; curStair < N; curStair++){
        stairAccums[curStair].first = stairAccums[curStair - 1].second + stairs[curStair];
        stairAccums[curStair].second = stairAccums[curStair - 2].first > stairAccums[curStair - 2].second ? stairAccums[curStair - 2].first + stairs[curStair] : stairAccums[curStair - 2].second + stairs[curStair];
    }

    if(stairAccums[N - 1].first < stairAccums[N - 1].second)
        cout << stairAccums[N - 1].second;
    else
        cout << stairAccums[N - 1].first;

    return 0;
}