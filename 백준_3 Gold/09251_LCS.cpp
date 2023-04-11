#include <iostream>
#include <string>
#include <vector>

using namespace std;

string str1, str2;
vector<vector<int>> cache;

int LCS(int str1Ind, int str2Ind);

int main(){

    cin >> str1 >> str2;

    cache = vector<vector<int>>(str1.length() + 1, vector<int>(str2.length() + 1, -1));

    cout << LCS(0, 0);

    return 0;    
}

int LCS(int str1Ind, int str2Ind){
    
    if(str1Ind == str1.length() || str2Ind == str2.length())
        return 0;

    if(str1[str1Ind] == str2[str2Ind]){
        if(cache[str1Ind + 1][str2Ind + 1] == -1)
            cache[str1Ind + 1][str2Ind + 1] = LCS(str1Ind + 1, str2Ind + 1);
        return cache[str1Ind + 1][str2Ind + 1] + 1;
    }
    else{
        if(cache[str1Ind][str2Ind + 1] == -1)
            cache[str1Ind][str2Ind + 1] = LCS(str1Ind, str2Ind + 1);
        if(cache[str1Ind + 1][str2Ind] == -1)
            cache[str1Ind + 1][str2Ind] = LCS(str1Ind + 1, str2Ind);

        return cache[str1Ind + 1][str2Ind] > cache[str1Ind][str2Ind + 1] ? cache[str1Ind + 1][str2Ind] : cache[str1Ind][str2Ind + 1];
    }

}