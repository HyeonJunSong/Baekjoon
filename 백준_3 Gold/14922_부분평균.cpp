#include <iostream>
#include <vector>

using namespace std;

#define ll long long

int N;
vector<ll> nums;
vector<ll> accumSum;

double getPartSum(int p, int q){
    return (double)(accumSum[q] - (p == 0 ? 0 : accumSum[p - 1])) / (double)(q - p + 1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    nums.assign(N, 0LL);

    for(int i = 0; i < N; i++) cin >> nums[i];

    accumSum.assign(N, 0LL);
    accumSum[0] += nums[0];
    for(int i = 1; i < N; i++) accumSum[i] = accumSum[i - 1] + nums[i];
    
    int ans = -1;
    double ansSum = 987654321;

    for(int i = 0; i < N - 1; i++){
        double curSum1 = getPartSum(i, i + 1);
        if(curSum1 < ansSum){
            ansSum = curSum1;
            ans = i;
        }

        if(i < N - 2){
            double curSum2 = getPartSum(i, i + 2);
            if(curSum2 < ansSum){
                ansSum = curSum2;
                ans = i;
            }
        }
    }

    cout << ans;

    return 0;
}