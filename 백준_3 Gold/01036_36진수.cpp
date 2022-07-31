////22.07.31
//3H 3M 11S
//
//49%에서 두시간 잡아먹었는데
//가중치 구할 때 정밀하게 안해서 그런듯

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

bool compare2(pair<int, vector<int>> a, pair<int, vector<int>> b) {
    for (int i = a.second.size() - 1; i >= 0; i--) {
        if (a.second[i] != b.second[i]) return a.second[i] > b.second[i];
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    vector<string> nums(N);
    for (int i = 0; i < N; i++)
        cin >> nums[i];
    int K;
    cin >> K;

    //자릿수별로 벡터에 넣기 -> 거꾸로 읽고 바꿔야함
    //벡터에 넣을때도 뒤집어서 넣기
    vector<vector<int>> unitNums;

    for (int i = 0; i < N; i++) {
        for (int j = nums[i].size() - 1; j >= 0; j--) {
            if (unitNums.size() <= nums[i].size() - j - 1) unitNums.push_back(vector<int>());
            if ('0' <= nums[i][j] && nums[i][j] <= '9') {
                unitNums[nums[i].size() - j - 1].push_back(nums[i][j] - '0');
            }
            else {
                unitNums[nums[i].size() - j - 1].push_back(nums[i][j] - 'A' + 10);
            }
        }
    }

    //숫자들의 가중치 구하기
    vector<pair<int, vector<int>>> weight(36, make_pair<int, vector<int>>(0, vector<int>(1, 0)));
    for (int i = 0; i < 36; i++) weight[i].first = i;
    

    for (int i = 0; i < unitNums.size(); i++) {
        vector<int> numOfNums(36, 0);
        for (int j = 0; j < unitNums[i].size(); j++) numOfNums[unitNums[i][j]]++;

        for (int j = 0; j < 36; j++) {
            for (int j = 0; j < 36; j++) weight[j].second.push_back(0);
            if (numOfNums[j] == 0) continue;
            weight[j].second[i] += numOfNums[j] * (35 - j);
            weight[j].second[i + 1] += (int)(weight[j].second[i] / 36);
        }
    }

    //가중치를 기준으로 바꿀 숫자 구하기
    sort(weight.begin(), weight.end(), compare2);
    set<int> change;
    for (int i = 0; i < K; i++) {
        change.insert(weight[i].first);
    }

    //숫자 바꾸기
    //바꾼숫자 합쳐서 하나의 벡터로
    vector<int> complete;
    for (int i = 0; i < unitNums.size(); i++) {
        int tot = 0;
        for (int j = 0; j < unitNums[i].size(); j++) {
            if (change.find(unitNums[i][j]) != change.end())
                tot += 35;
            else
                tot += unitNums[i][j];
        }

        complete.push_back(tot);
    }   

    //자리수 올림하기
    for (int i = 0; i < complete.size(); i++) {
        if (complete[i] >= 36) {
            if (i == complete.size() - 1)
                complete.push_back(0);
            complete[i + 1] += (int)(complete[i] / 36);
            complete[i] %= 36;
        }
    }

    //영어로 바꾸기
    string res = "";
    bool zeroCheck = false;
    for (int i = complete.size() - 1; i >= 0; i--) {
        if (!zeroCheck) {
            if (complete[i] == 0) continue;
            else zeroCheck = true;
        }

        if (0 <= complete[i] && complete[i] <= 9)
            res += char('0' + complete[i]);
        else
            res += char('A' + complete[i] - 10);
    }

    if (res.size() == 0) res += '0';
    cout << res;

    return 0;
}