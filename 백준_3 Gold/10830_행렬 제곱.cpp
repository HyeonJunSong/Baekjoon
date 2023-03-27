////230327
//이해 및 설계 : 1m 35s
//입력 : 2m 31s
//구현 : 14m 39s

//tot : 18m 45s

#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<long long, vector<vector<int>>> cache;

int N;
vector<vector<int>> matrix;

vector<vector<int>> matrixInvolution(long long n);
int main(){
    long long B;
    cin >> N >> B;
    matrix = vector<vector<int>>(N, vector<int>(N));
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> matrix[i][j];

    vector<vector<int>> ans = matrixInvolution(B);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << ans[i][j] % 1000 << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}

vector<vector<int>> matrixInvolution(long long n){
    if(n == 1)
        return matrix;

    long long left = n / 2;
    long long right = n - left;

    if(cache.find(left) == cache.end())
        cache[left] = matrixInvolution(left);
    if(cache.find(right) == cache.end())
        cache[right] = matrixInvolution(right);
    
    vector<vector<int>> leftMatrix = cache[left];
    vector<vector<int>> rightMatrix = cache[right];
    vector<vector<int>> newMatrix(N, vector<int>(N, 0));

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            for(int k = 0; k < N; k++)
                newMatrix[i][j] += leftMatrix[i][k] * rightMatrix[k][j];
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
                newMatrix[i][j] %= 1000;
    
    return newMatrix;
}