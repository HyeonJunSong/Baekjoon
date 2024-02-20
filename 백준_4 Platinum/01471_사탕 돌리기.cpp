#include <iostream>
#include <vector>

using namespace std;

int N;

int getNextSpace(int curSpace) {

    int temp = curSpace + 1;
    int move = 0;
    while (temp > 0) {
        move += temp % 10;
        temp /= 10;
    }

    return (curSpace + move) % N;
}

vector<int> nextSpace;
vector<int> maxDetph;

int getMaxDepth(int idx);

int main() {

    cin >> N;
    N;
    nextSpace = vector<int>(N, 0);
    for (int i = 0; i < N; i++)
        nextSpace[i] = getNextSpace(i);

    maxDetph = vector<int>(N, 0);
    vector<bool> visited(N, false);
    //사이클 찾아서 표시
    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;

        vector<bool> curVisited(N, false);
        vector<int> path;
        int curIdx = i;
        while (!curVisited[curIdx] && !visited[curIdx]) {
            path.push_back(curIdx);
            curVisited[curIdx] = true;
            visited[curIdx] = true;
            curIdx = nextSpace[curIdx];
        }

        if (curVisited[curIdx]) {
            int cycleStIdx = 0;
            for (; curIdx != path[cycleStIdx]; cycleStIdx++);

            for (int j = cycleStIdx; j < path.size(); j++)
                maxDetph[path[j]] = path.size() - cycleStIdx;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (maxDetph[i] == 0)
            maxDetph[i] = getMaxDepth(i);
        ans = max(ans, maxDetph[i]);
    }

    cout << ans;


    return 0;
}

int getMaxDepth(int idx) {
    if (maxDetph[nextSpace[idx]] == 0)
        maxDetph[nextSpace[idx]] = getMaxDepth(nextSpace[idx]);
    return maxDetph[nextSpace[idx]] + 1;
}