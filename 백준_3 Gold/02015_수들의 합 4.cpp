#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
    int N;
    long long K;
    cin >> N >> K;

    vector<long long> A(N);
    for(int i = 0; i < N; i++)
        cin >> A[i];

    unordered_map<long long, long long> accumSum;
    long long curAccum = 0;
    accumSum[curAccum] = 1;

    long long ans = 0;

    for(int i = 0; i < N; i++){
        curAccum += A[i];

        auto iter = accumSum.find(curAccum - K);
        if(iter != accumSum.end()){
            ans += iter->second;
        }

        if(accumSum.find(curAccum) == accumSum.end())
            accumSum[curAccum] = 1;
        else
            accumSum[curAccum] += 1;
    }

    cout << ans;

    return 0;
}