#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// 0 1 2 3 4 5 6 7 8 9
// 6 2 5 5 4 5 6 3 7 5

vector<int> num;

vector<vector<vector<int>>> diff = {
    {
        {-4, -1, -1, -2, -1, 0, -3, 1, -1},
        {3, 3, 2, 3, 4, 1, 5, 3},
        {0, -1, 0, 1, -2, 2, 0},
        {-1, 0, 1, -2, 2, 0},
        {1, 2, -1, 3, 1},
        {1, -2, 2, 0},
        {-3, 1, -1},
        {4, 2},
        {-2},
        {}
    },
    {
        {0, 4, 1, 1, 2, 1, 0, 3, -1, 1},
        {-4, 0, -3, -3, -2, -3, -4, -1, -5, -3},
        {-1, 3, 0, 0, 1, 0, -1, 2, -2, 0},
        {-1, 3, 0, 0, 1, 0, -1, 2, -2, 0},
        {-2, 2, -1, -1, 0, -1, -2, 1, -3, -1},
        {-1, 3, 0, 0, 1, 0, -1, 2, -2, 0},
        {0, 4, 1, 1, 2, 1, 0, 3, -1, 1},
        {-3, 1, -2, -2, -1, -2, -3, 0, -4, -2},
        {1, 5, 2, 2, 3, 2, 1, 4, 0, 2},
        {-1, 3, 0, 0, 1, 0, -1, 2, -2, 0}
    }
};

string ifCanMakeDigit(map<int, string>& possible, int curDigit);

int main() {

    string inpNum;
    cin >> inpNum;

    for (int i = 0; i < inpNum.size(); i++) {
        num.push_back(inpNum[i] - '0');
    } 
    reverse(num.begin(), num.end());

    map<int, string> possible;
    possible.emplace(0, "");
    for (int i = 0; i < inpNum.size(); i++) {
        string res = ifCanMakeDigit(possible, i);
        if (res.compare("false")) {
            cout << res;
        }
    }

    return 0;
}

string ifCanMakeDigit(map<int, string>& possible, int curDigit) {

    for (int i = 0; i < diff[0][num[curDigit]].size(); i++) {
        if (possible.find(-1 * diff[0][num[curDigit]][i]) != possible.end()) {
            return to_string(num[curDigit] + i + 1);
        }
    }


    for (int i = 0; i < diff[1][num[curDigit]].size(); i++) {
        for (auto j = possible.begin(); j != possible.end(); j++) {
            auto findSum = possible.find(diff[1][num[curDigit]][i] + j->first);
            if (findSum != possible.end()) {
                possible.insert(make_pair(findSum->first, to_string(num[curDigit]) + findSum->second));
            }
            else {
                possible.insert(make_pair(diff[1][num[curDigit]][i] + j->first, to_string(i) + j->second));
            }
        }
    }

    return "false";
}