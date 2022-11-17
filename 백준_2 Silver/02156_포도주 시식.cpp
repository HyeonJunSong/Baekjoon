#include <iostream>
#include <vector>

using namespace std;

vector<int> podo;
vector<vector<int>> memo;

int largest(int ind, int cnt);


int main(){

    int n;
    cin >> n;

    podo = vector<int>(n);
    for(int i = 0; i < n; i++) cin >> podo[i];

    memo = vector<vector<int>>(n, vector<int>(3, -1));
    cout << largest(0, 0);

    return 0;
}

int largest(int ind, int cnt){
    if(ind == podo.size() - 1){
        if(cnt == 2) return 0;
        else return podo[ind];
    }

    int ret = 0;
    
    if(cnt != 2){
        if(memo[ind + 1][cnt + 1] == -1)
            memo[ind + 1][cnt + 1] = largest(ind + 1, cnt + 1);
        ret = memo[ind + 1][cnt + 1] + podo[ind];
    }
    if(memo[ind + 1][0] == -1)
        memo[ind + 1][0] = largest(ind + 1, 0);
    
    if(ret < memo[ind + 1][0])
        ret = memo[ind + 1][0];

    return ret;
}