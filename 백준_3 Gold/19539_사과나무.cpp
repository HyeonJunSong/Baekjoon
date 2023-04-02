////20230402
//이해 및 설계 : 9m 42s
//입력 : 1m 43s
//구현 : 4m 22s

//tot : 15m 48s

#include <iostream>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    int appleTree;
    int numOf2 = 0;
    int numOf1 = 0;
    for(int i = 0; i < N; i++){
        cin >> appleTree;
        numOf2 += appleTree / 2;
        numOf1 += appleTree % 2;
    }

    if(numOf2 >= numOf1 && (numOf2 - numOf1) % 3 == 0)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}