////2022.06.28
//이해 및 설계 : 10m 46s
//입력 : 1m 55s
//구현 : 28m 58s
//
//tot : 41m 40s

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

string sentence;
vector<string> words;

vector<int> minCostFromCurInd;

int retMinCost(int curI);
bool checkIfCanMake(int curI, int wordI);
int calculateCost(int curI, int wordI);

int main() {

    cin >> sentence;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        string inp;
        cin >> inp;
        words.push_back(inp);
    }

    for (int i = 0; i < sentence.size(); i++)
        minCostFromCurInd.push_back(-2);

    cout << retMinCost(0);

}

int retMinCost(int curI) {

    if (curI == sentence.size())
        return 0;

    if (minCostFromCurInd[curI] != -2)
        return minCostFromCurInd[curI];

    for (int i = 0; i < words.size(); i++) {
        if (sentence.size() < curI + words[i].size()) continue;

        if (checkIfCanMake(curI, i)) {
            int nextMinCost = retMinCost(curI + words[i].size());
            if (nextMinCost == -1) continue;

            int curMinCost = calculateCost(curI, i) + nextMinCost;
            if (minCostFromCurInd[curI] > curMinCost || minCostFromCurInd[curI] == -2)
                minCostFromCurInd[curI] = curMinCost;
        }
    }

    if(minCostFromCurInd[curI] == -2)
        minCostFromCurInd[curI] = -1;

    return minCostFromCurInd[curI];
}

bool checkIfCanMake(int curI, int wordI) {
    string subStr = sentence.substr(curI, words[wordI].size());
    string word = words[wordI];

    sort(subStr.begin(), subStr.end());
    sort(word.begin(), word.end());

    return subStr.compare(word) == 0;
}

int calculateCost(int curI, int wordI) {
    string subStr = sentence.substr(curI, words[wordI].size());
    string word = words[wordI];

    int cnt = 0;
    for (int i = 0; i < word.size(); i++) {
        if (subStr[i] != word[i]) cnt++;
    }

    return cnt;
}