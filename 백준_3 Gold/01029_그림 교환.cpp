////22.07.19
//이해 및 설계 : 40m 3s
//입력 : 2m 23s
//구현 : 1h 32m 42s

//tot : 2h 15m 9s

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int N;
vector<string> priceStr;

vector<vector<int>> price;

vector<map<int, map<int, int>>> memo;

int retMaxPeople(int curArtist, int byNow, int curPrice);
vector<bool> numToBool(int byNow);

int main() {

    cin >> N;
    priceStr = vector<string>(N);
    for (int i = 0; i < N; i++) cin >> priceStr[i];

    price = vector<vector<int>>(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            price[i][j] = priceStr[i][j] - '0';

    memo = vector<map<int, map<int, int>>>(N);

    cout << retMaxPeople(0, 1, 0);
    return 0;
}

int retMaxPeople(int curArtist, int byNow, int curPrice) {
    if (byNow == pow(2, N + 1) - 1) return 1;

    vector<bool> byNowBool = numToBool(byNow);

    int maxPeople = 0;

    for (int i = 0; i < N; i++) {
        if (byNowBool[i] || i == curArtist) continue;

        if (curPrice > price[curArtist][i]) continue;

        int curByNow = byNow + (int)(pow(2, i));
        if (memo[i].find(price[curArtist][i]) == memo[i].end()) {
            memo[i][price[curArtist][i]] = map<int, int>();
            memo[i][price[curArtist][i]][curByNow] = retMaxPeople(i, curByNow, price[curArtist][i]);
        }
        else if (memo[i][price[curArtist][i]].find(curByNow) == memo[i][price[curArtist][i]].end()) {
            memo[i][price[curArtist][i]][curByNow] = retMaxPeople(i, curByNow, price[curArtist][i]);
        }

        if (maxPeople < memo[i][price[curArtist][i]][curByNow]) maxPeople = memo[i][price[curArtist][i]][curByNow];
    }

    return maxPeople + 1;
}

vector<bool> numToBool(int byNow) {
    vector<bool> res(N, false);

    int ind = 0;
    while (byNow != 0) {
        if (byNow % 2) {
            res[ind] = true;
            byNow /= 2;
        }
        else {
            res[ind] = false;
            byNow /= 2;
        }
        ind++;
    }

    return res;
}