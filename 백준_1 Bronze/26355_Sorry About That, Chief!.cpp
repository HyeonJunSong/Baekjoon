#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool ifPrime(int n){
    int sqrtN = (int)(sqrt(n));
    for(int i = 2; i <= sqrtN; i++)
        if(n % i == 0) return false;
    return true;
}

void testCase(){
    int v;
    cin >> v;

    int d = 0;
    while(true){
        if(ifPrime(v + d) || ifPrime(v - d))
            break;
        d++;
    }

    cout << "Input value: " << v << '\n';
    if(d == 0){
        cout << "Would you believe it; it is a prime!\n\n";
    } else {
        cout << "Missed it by that much (" << d << ")!\n\n";
    }
}

int main(){
    int t;
    cin >> t;
    while(t-- > 0) testCase();
    return 0;
}