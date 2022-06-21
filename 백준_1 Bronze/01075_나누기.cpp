#include <iostream>

using namespace std;

int main(){

    int N, F;
    cin >> N >> F;

    for(int i = 0; i < 100; i++){
        if((N - (N % 100) + i) % F == 0){
            if(0 <= i && i <= 9)
                cout << '0' << i;
            else
                cout << i;
            break;
        }
    }
}