////22.04.30
//이해 및 설계 : 8m 13s
//입력 : 51s
//구현 : 15m 36s

//tot : 24m 40s

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool ifPossible(string S, string T);

int main(){
    string S;
    string T;

    cin >> S;
    cin >> T;

    if(ifPossible(S, T))
        cout << 1;
    else
        cout << 0;

    return 0;
}

bool ifPossible(string S, string T){
    if(T.length() == S.length())
        return !T.compare(S);
    
    string substr = T.substr(0, T.length() - 1);

    if(T.back() == 'A')
        return ifPossible(S, substr);
    
    if(T.back() == 'B'){
        reverse(substr.begin(), substr.end());
        return ifPossible(S, substr);
    }
}