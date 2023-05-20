#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n;

bool ifXpiXIsN(int x);
int getGCD(int a, int b);

#define MAX 1000000001

int main(){

    cin >> n;

    int ans = MAX;
    for(int i = 1; i <= sqrt(n); i++){
        if(n % i == 0){
            if(ifXpiXIsN(i)){
                if(ans > i)
                    ans = i;
            }
            if(ifXpiXIsN(n / i)){
                if(ans > n / i)
                    ans = n / i;
            }
        }
    }

    if(ans == MAX)
        cout << -1;
    else
        cout << ans;


    return 0;
}

bool ifXpiXIsN(int x){
    int target = n / x;

    int cnt = 1;
    int i = 2;
    while(cnt <= target && i < x){
        if(getGCD(i, x) == 1)
            cnt++;
        i++;
    }

    return target == cnt;
}

int getGCD(int a, int b){

    if(a > b){
        int temp = a;
        a = b;
        b = temp;
    }

    while(a != 1){
        if(b % a == 0)
            break;

        int temp = a;
        a = b % a;
        b = temp;
    }

    return a;
}