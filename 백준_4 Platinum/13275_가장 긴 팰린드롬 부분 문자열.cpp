#include <iostream>
#include <vector>
#include <string>

using namespace std;

string str;
vector<int> longestPalindromeFrom;
pair<int, int> theMostFarPalindrome;    //first : center, second : end

int getLongestPalindrome(int I);
int calRealPalidromeLen(int I, int radius);

#define blank '@'

int main() {

    string inpStr;
    cin >> inpStr;

    ////전처리 : 사이에 문자열 하나씩 끼워넣기
    str = inpStr[0];
    for (int i = 1; i < inpStr.size(); i++) {
        str += blank;
        str += inpStr[i];
    }

    ////매니처 알고리즘

    longestPalindromeFrom = vector<int>(str.size());
    theMostFarPalindrome = { -1, -1 };

    int longestPalindrome = 1;

    for (int i = 1; i < str.size() - 1; i++) {
        longestPalindromeFrom[i] = getLongestPalindrome(i);
        if (theMostFarPalindrome.second < i + longestPalindromeFrom[i]) {
            theMostFarPalindrome.first = i;
            theMostFarPalindrome.second = i + longestPalindromeFrom[i];
        }

        int plaindromeLength = calRealPalidromeLen(i, longestPalindromeFrom[i]);
        if (longestPalindrome < plaindromeLength)
            longestPalindrome = plaindromeLength;
    }

    cout << longestPalindrome;

    return 0;
}

int getLongestPalindrome(int I) {
    int radius = 1;
    if (I <= theMostFarPalindrome.second) {
        //만약 지금 탐색하려는 부분이 탐색했던 영역에 포함돼있으면
        //radius 재조정

        radius = longestPalindromeFrom[2 * theMostFarPalindrome.first - I] + 1 < theMostFarPalindrome.second - I + 1 ? longestPalindromeFrom[2 * theMostFarPalindrome.first - I] + 1 : theMostFarPalindrome.second - I + 1;

        if (I + radius >= str.size())
            return str.size() - I - 1;
    }

    for (; I + radius < str.size() && I - radius >= 0; radius++)
        if (str[I + radius] != str[I - radius])
            break;

    return radius - 1;
}

int calRealPalidromeLen(int I, int radius) {
    int init = 1;
    if (str[I] == blank)
        init = 0;

    if (radius == 0)
        return init;

    if (str[I + 1] != blank && str[I + radius] != blank)
        return (radius / 2 + 1) * 2 + init;
    else
        return (radius / 2) * 2 + init;
}