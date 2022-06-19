#include <iostream>
#include <math.h>

using namespace std;


bool ifPrime(int N){
    for(int i = 2; i <= (int)(sqrt(N)); i++){
        if(!(N % i))
            return false;
    }
    return true;
}

int main(){
    int N;
    cin >> N;

    int cnt = 0;
    for(int i = 0; i < N; i++){
        int inp;
        cin >> inp;
        if(inp != 1 && ifPrime(inp))
            cnt++;
    }

    cout << cnt;

    return 0;
}