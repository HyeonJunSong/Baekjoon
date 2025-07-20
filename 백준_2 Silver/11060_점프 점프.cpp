#include <iostream>
#include <vector>

using namespace std;

int main(){
    
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];

    vector<int> ans(N, 987654321);
    ans[0] = 0;
    for(int i = 0; i < N - 1; i++)
        for(int j = 1; j <= A[i] && i + j < N; j++)
            ans[i + j] = min(ans[i + j], ans[i] + 1);
    
    if(ans[N - 1] == 987654321)
        cout << -1;
    else
        cout << ans[N - 1];

    return 0;
}