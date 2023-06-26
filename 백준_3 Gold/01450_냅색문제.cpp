#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int N, C;
vector<long long> items;
vector<long long> sumFrom;

int getNumOfCases(int I, long long spaceLeft);

int main(){

    cin >> N >> C;
    items = vector<long long>(N);
    for(int i = 0; i < N; i++)
        cin >> items[i];
    
    //분기한정 전략을 위한 내림차순 정렬
    sort(items.rbegin(), items.rend());

    //분기한정 전략을 위한 누적합
    sumFrom = vector<long long>(N);
    sumFrom[N - 1] = items[N - 1];
    for(int i = N - 2; i >= 0; i--)
        sumFrom[i] = items[i] + sumFrom[i + 1];
        
    cout << getNumOfCases(0, C);

    return 0;
}

int getNumOfCases(int I, long long spaceLeft){

    ////기저
    if(I == N - 1){
        if(items[I] <= spaceLeft)
            return 2;
        else
            return 1;
    }

    //분기 한정 전략 : 남은거 다 합쳐도 공간이 남았을 때
    if(spaceLeft >= sumFrom[I])
        return pow(2, N - I);

    //탐색
    int ans = 0;

    if(spaceLeft == items[I])
        ans += 1;
    else if(spaceLeft - items[I] >= 0)
        ans += getNumOfCases(I + 1, spaceLeft - items[I]);

    ans += getNumOfCases(I + 1, spaceLeft);

    ////반환
    return ans;
}