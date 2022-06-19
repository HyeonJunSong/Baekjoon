#include <iostream>

using namespace std;
int getGCD(int a, int b);

int main(){
    int N;
    cin >> N;

    for(int i = 0; i < N; i++){
        int a, b, d;
        cin >> a >> b >> d;
        int tot = 0;

        for(int j = 1; j <= (int)(a / d); j++){
            for(int k = 1; k <= (int)(b / d); k++){
                if(getGCD(j, k) == 1)
                    tot++;
            }
        }
        cout << tot << endl;
    }
}

int getGCD(int a, int b){
    if(a == b){
        return b;
    }
    else if(a > b){
        while(true){
            if(!(a % b))
                return b;
            else{
                int temp = a % b;
                a = b;
                b = temp;
            }
        }
    }
    else{
        while(true){
            if(!(b % a))
                return a;
            else{
                int temp = b % a;
                b = a;
                a = temp;
            }
        }
    }
}