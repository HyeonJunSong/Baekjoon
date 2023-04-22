#include <iostream>
#include <string>
#include <vector>

using namespace std;

string str1, str2;
vector<vector<pair<bool, string>>> cache;

string LCS(int str1Ind, int str2Ind);

int main(){

    cin >> str1 >> str2;

    cache = vector<vector<pair<bool, string>>>(str1.length() + 1, vector<pair<bool, string>>(str2.length() + 1, pair<bool, string>(false, "")));

    cout << LCS(0, 0);

    return 0;    
}

string LCS(int str1Ind, int str2Ind){
    
    if(str1Ind == str1.length() || str2Ind == str2.length())
        return "";

    if(str1[str1Ind] == str2[str2Ind]){
        if(!cache[str1Ind + 1][str2Ind + 1].first){
            cache[str1Ind + 1][str2Ind + 1].first = true;
            cache[str1Ind + 1][str2Ind + 1].second = LCS(str1Ind + 1, str2Ind + 1);
        }
        return cache[str1Ind + 1][str2Ind + 1].second + str1[str1Ind];
    }
    else{
        if(!cache[str1Ind][str2Ind + 1].first){
            cache[str1Ind][str2Ind + 1].first = true;
            cache[str1Ind][str2Ind + 1].second = LCS(str1Ind, str2Ind + 1);
        }
        if(!cache[str1Ind + 1][str2Ind].first){
            cache[str1Ind + 1][str2Ind].first = true;
            cache[str1Ind + 1][str2Ind].second = LCS(str1Ind + 1, str2Ind);
        }

        return cache[str1Ind + 1][str2Ind].second.length() > cache[str1Ind][str2Ind + 1].second.length() ? cache[str1Ind + 1][str2Ind].second : cache[str1Ind][str2Ind + 1].second;
    }

}