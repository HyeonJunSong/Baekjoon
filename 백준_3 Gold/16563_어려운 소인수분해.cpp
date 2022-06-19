#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


int main(){
    int N;
    cin >> N;

    int* nums = new int[N];
    for(int i = 0 ; i < N; i++)
        cin >> nums[i];

    int maxNum = nums[0];
    for(int i = 1; i < N; i++)
        if(maxNum < nums[i])
            maxNum = nums[i];

    vector<int> memo(maxNum + 1, -1);
        
    
    for(int i = 2; i <= (int)(sqrt(maxNum)); i++){

        if(memo[i] != -1) continue;
        memo[i] = i;
        for(int j = i * 2; j <= maxNum; j += i){
            if(memo[j] == -1)
                memo[j] = i;
        }
    }

    for(int i = 0; i < N; i++){
        while(nums[i] != 1){
            if(memo[nums[i]] == -1){
                cout << nums[i] << ' ';
                break;
            }
            cout << memo[nums[i]] << ' ';
            nums[i] /= memo[nums[i]];
        }
        cout << '\n';
    }

    

    return 0;
}