#include <iostream>
#include <vector>
#include <map>

using namespace std;

const long long divisor = 1000000007;

long long N, M;
vector<vector<long long>> augMatrix;

void initAugMatrix();
vector<bool> toBinaryVector(long long exponent);
vector<vector<long long>> augMatrixInvolution(long long exponent);
vector<long long> getFloorVector();


int main() {
    cin >> N >> M;

    if (N == M) {
        cout << 2;
        return 0;
    }
    else if(N < M){
        cout << 1;
        return 0;
    }

    //초기 벡터
    vector<long long> floorVector = getFloorVector();

    //첨가 행렬 초기화
    augMatrix = vector<vector<long long>>(M, vector<long long>(M, 0));
    initAugMatrix();

    vector<vector<long long>> involutedAugMatrix = augMatrixInvolution(N - M);

    long long ans = 0;
    for (int i = 0; i < M; i++)
        ans += (involutedAugMatrix[0][i] * floorVector[i]) % divisor;

    cout << ans % divisor;

    return 0;
}

void initAugMatrix() {

    augMatrix[0][0] = 1;
    augMatrix[0][M - 1] = 1;

    for (int i = 1; i < M; i++)
        augMatrix[i][i - 1] = 1;
}

vector<bool> toBinaryVector(long long exponent) {
    vector<bool> binaryNum;
    while (exponent != 1) {
        if (exponent % 2 == 1) {
            binaryNum.push_back(true);
        }
        else {
            binaryNum.push_back(false);
        }
        exponent /= 2;
    }
    binaryNum.push_back(true);
    return binaryNum;
}

vector<vector<long long>> augMatrixInvolution(long long exponent) {
    ////행렬 N-M제곱을 이진수로 치환해서 할것임 -> 시간과 공간의 적정 트레이드 오프
    // ex) 26 -> 16 + 8 + 2
    vector<vector<long long>> result(M, vector<long long>(M, 0));
    for (int i = 0; i < M; i++)
        result[i][i] = 1;
    
    vector<bool> binaryVector = toBinaryVector(exponent);

    vector<vector<vector<long long>>> augMatrixInvolutionOf2s;
    augMatrixInvolutionOf2s.push_back(augMatrix);
    for (int v = 1; v < binaryVector.size(); v++) {
        augMatrixInvolutionOf2s.push_back(vector<vector<long long>>(M, vector<long long>(M, 0)));
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    augMatrixInvolutionOf2s[v][i][j] = (augMatrixInvolutionOf2s[v][i][j] + augMatrixInvolutionOf2s[v - 1][i][k] * augMatrixInvolutionOf2s[v - 1][k][j]) % divisor;
    }

    for (int v = 0; v < binaryVector.size(); v++) {
        if (!binaryVector[v]) continue;
        vector<vector<long long>> tempResult(M, vector<long long>(M, 0));

        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < M; k++)
                    tempResult[i][j] = (tempResult[i][j] + result[i][k] * augMatrixInvolutionOf2s[v][k][j]) % divisor;

        result = tempResult;
    }

    return result;
}

vector<long long> getFloorVector() {
    vector<long long> floorVector(M, 1);
    floorVector[0] = 2;
    return floorVector;
}