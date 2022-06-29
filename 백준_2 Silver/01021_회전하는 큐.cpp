#include <iostream>
#include <vector>

using namespace std;

int main(){

    int N, M;
    cin >> N >> M;
    vector<int> nums;
    for(int i = 0; i < M; i++){
        int inp;
        cin >> inp;
        nums.push_back(inp - 1);
    }

    int tot = 0;
    for(int i = 0; i < M; i++){
        if(N - nums[i] < nums[i]){
            tot += N - nums[i];
            for(int j = i + 1; j < M; j++){
                nums[j] = (nums[j] + (N - nums[i]) ) % N - 1;
            }
            N--;
        }
        else{
            tot += nums[i];
            for(int j = i + 1; j < M;j++){
                nums[j] = (nums[j] - (nums[i]) + N) % N - 1;
            }
            N--;
        }
    }

    cout << tot;

    return 0;

}