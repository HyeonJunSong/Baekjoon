#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N;
vector<vector<bool>> home;

bool ifPipeAvailable(pair<int, int>& pipe1, pair<int, int>& pipe2);

int main() {

    cin >> N;
    home = vector<vector<bool>>(N, vector<bool>(N, false));
    int inp;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> inp;
            if (inp == 1)
                home[i][j] = true;
        }
    }

    stack<pair<pair<int, int>, pair<int, int>>> s;
    s.push(pair<pair<int, int>, pair<int, int>>(pair<int, int>(0, 0), pair<int, int>(0, 1)));

    int cnt = 0;
    pair<int, int> left;
    pair<int, int> right;

    while (!s.empty()) {
        pair<pair<int, int>, pair<int, int>> curNode;
        curNode = s.top();
        s.pop();
        if (curNode.second.first == N - 1 && curNode.second.second == N - 1) {
            cnt++;
            continue;
        }

        left = curNode.second;
        if (curNode.first.first == curNode.second.first) {
            //우측
            right = curNode.second;
            right.second++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }

            //우측 아래
            right = curNode.second;
            right.first++;
            right.second++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }
        }
        else if (curNode.first.second == curNode.second.second) {
            //아래
            right = curNode.second;
            right.first++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }

            //우측 아래
            right = curNode.second;
            right.first++;
            right.second++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }
        }
        else {
            //우측
            right = curNode.second;
            right.second++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }

            //아래
            right = curNode.second;
            right.first++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }

            //우측 아래
            right = curNode.second;
            right.first++;
            right.second++;
            if (ifPipeAvailable(left, right)) {
                s.push(pair<pair<int, int>, pair<int, int>>(left, right));
            }

        }
    }

    cout << cnt;


    return 0;
}

bool ifPipeAvailable(pair<int, int>& pipe1, pair<int, int>& pipe2) {

    if (pipe2.first == N || pipe2.second == N)
        return false;
    if (home[pipe1.first][pipe1.second])
        return false;
    if (home[pipe2.first][pipe2.second])
        return false;
    if (home[pipe1.first][pipe2.second])
        return false;
    if (home[pipe2.first][pipe1.second])
        return false;

    return true;
}