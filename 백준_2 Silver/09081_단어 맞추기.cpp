#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string findNextOne(string str);
int main() {
    int T;
    cin >> T;
    vector<string> cases(T);
    for (int i = 0; i < T; i++)
        cin >> cases[i];

    for (int i = 0; i < T; i++)
        cout << findNextOne(cases[i]) << endl;

    return 0;
}

string findNextOne(string str) {
    int len = str.length();
    vector<char> stack;
    stack.push_back(str[len - 1]);

    int last = -1;
    for (int i = 1; i < len; i++) {
        if (stack[i - 1] > str[len - i - 1]) {
            last = len - i - 1;
            break;
        }
        stack.push_back(str[len - i - 1]);
    }

    if (last == -1)
        return str;

    char next = 'Z' + 1;
    int nextInd;
    for (int i = 0; i < stack.size(); i++) {
        if (str[last] < stack[i] && stack[i] < next) {
            nextInd = i;
            next = stack[i];
        }
    }

    stack[nextInd] = str[last];
    sort(stack.begin(), stack.end());
    string result = str.substr(0, last);
    result += next;
    for (int i = 0; i < stack.size(); i++)
        result += stack[i];
    return result;
}