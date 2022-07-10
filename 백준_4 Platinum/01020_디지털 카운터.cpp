#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<int, string> possible;

vector<int> num;

vector<int> stroke = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};

string str;
int goal;

vector<vector<vector<int>>> strokes = {
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
        {0, -4, -1, -1, -2, -1, 0, -3, 1, -1},
        {4, 0, 3, 3, 2, 3, 4, 1, 5, 3},
        {1, -3, 0, 0, -1, 0, 1, -2, 2, 0},
        {1, -3, 0, 0, -1, 0, 1, -2, 2, 0},
        {2, -2, 1, 1, 0, 1, 2, -1, 3, 1},
        {1, -3, 0, 0, -1, 0, 1, -2, 2, 0},
        {0, -4, -1, -1, -2, -1, 0, -3, 1, -1},
        {3, -1, 2, 2, 1, 2, 3, 0, 4, 2},
        {-1, -5, -2, -2, -3, -2, -1, -4, 0, -2},
        {1, -3, 0, 0, -1, 0, 1, -2, 2, 0},
    }
};

string ifCanMake(int curDigit);

string calcDiff(string num);

int main() {

    cin >> str;

    num = vector<int>(str.size());
    for (int i = 0; i < str.size(); i++) num[str.size() - i - 1] = str[i] - '0';

    goal = 0;
    possible.emplace(0, "");

    for (int i = 0; i < num.size(); i++) {
        string res = ifCanMake(i);
        if (res.compare("false")) {
            cout << calcDiff(res);
            return 0;
        }
    }

    int totStroke = 0;
    for (int i = 0; i < num.size(); i++) totStroke += stroke[num[i]];
    if (totStroke == 6 * num.size()) {
        string res = "";
        for (int i = 0; i < num.size(); i++) res += '0';
        cout << calcDiff(res);
        return 0;
    }

    goal = totStroke;
    possible.clear();
    possible.emplace(6 * num.size(), "");
    num = vector<int>(str.size(), 0);

    for (int i = 0; i < num.size(); i++) {
        string res = ifCanMake(i);

        if (res.compare("false")) {
            int diff = str.size() - res.size();
            for (int i = 0; i < diff; i++) res = "0" + res;
            cout << calcDiff(res);
            return 0;
        }
    }




    return 0;
}

string ifCanMake(int curDigit) {

    for (int i = 0; i < strokes[0][num[curDigit]].size(); i++) {
        if (possible.find(goal - strokes[0][num[curDigit]][i]) != possible.end()) {
            return to_string(num[curDigit] + i + 1) + possible.find(goal - strokes[0][num[curDigit]][i])->second;
        }
    }

    map<int, string> newPossible;

    for (int i = strokes[1][num[curDigit]].size() - 1; i >= 0; i--) {

        for (auto iter = possible.begin(); iter != possible.end(); iter++) {
            newPossible[iter->first + strokes[1][num[curDigit]][i]] = to_string(i) + iter->second;
        }

    }

    possible = newPossible;

    return "false";
}

string calcDiff(string num) {
    num = str.substr(0, str.size() - num.size()) + num;

    if (num.compare(str) == 0) {
        string res = "1";
        for (int i = 0; i < str.size(); i++) res += '0';
        return res;
    }

    vector<int> res = vector<int>(num.size() + 1);

    for (int i = 0; i < str.size(); i++) {
        res[i + 1] = num[i] - str[i];
    }
    
    res[0] = 1;

    for (int i = res.size() - 1; i > 0; i--) {
        if (res[i] < 0) {
            res[i - 1]--;
            res[i] = 10 + res[i];
        }
    }

    string resStr = "";
    bool ifPassed = false;

    for (int i = 1; i < res.size(); i++) {
        if (!ifPassed) {
            if (res[i] == 0) continue;
            if (res[i] != 0) ifPassed = true;
        }

        resStr += '0' + res[i];
    }

    return resStr;
}