#include <iostream>
#include <cmath>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout.precision(10);
    
    int N;
    cin >> N;
    for(int i = 0; i < N; i++){
        double F, T;
        cin >> F >> T;
        cout << "Case #" << i + 1 <<": " << pow((2 + F) / 2, T) << '\n';
    }

    return 0;
}
