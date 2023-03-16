#include <iostream>
#include <cmath>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    long long N;
    for(int i = 0; i < T; i++){
        cin >> N;
        cout << (int)((-1 + sqrt(1 + 8 * N))/2) << '\n';
    }

    return 0;
}