////240207
//43m 49s

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dir[4][2] = {
  {-1, 0},
  { 1, 0},
  { 0,-1},
  { 0, 1},
};

#define MAX 987654321

int main() {

    int N, M;
    vector<vector<int>> map;

    cin >> N >> M;
    map = vector<vector<int>>(N, vector<int>(M));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> map[i][j];

    //섬에 번호 부여하기
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    int islandNum = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0 || visited[i][j]) continue;

            vector<pair<int, int>> stack(1, { i, j });
            while (!stack.empty()) {
                pair<int, int> curNode = stack.back();
                stack.pop_back();

                if (visited[curNode.first][curNode.second]) continue;
                visited[curNode.first][curNode.second] = true;
                map[curNode.first][curNode.second] = islandNum;

                for (int d = 0; d < 4; d++) {
                    if (0 <= curNode.first + dir[d][0] && curNode.first + dir[d][0] < N
                        && 0 <= curNode.second + dir[d][1] && curNode.second + dir[d][1] < M
                        && map[curNode.first + dir[d][0]][curNode.second + dir[d][1]] != 0
                        && !visited[curNode.first + dir[d][0]][curNode.second + dir[d][1]]) {
                        stack.push_back({ curNode.first + dir[d][0], curNode.second + dir[d][1] });
                    }
                }

            }
            islandNum++;
        }
    }
    islandNum--;

    //섬 돌며 그래프 그리기
    vector<vector<int>> graph(islandNum + 1, vector<int>(islandNum + 1, MAX));

    visited = vector<vector<bool>>(N, vector<bool>(M, false));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0 || visited[i][j]) continue;

            vector<pair<int, int>> stack(1, { i, j });
            while (!stack.empty()) {
                pair<int, int> curNode = stack.back();
                stack.pop_back();

                if (visited[curNode.first][curNode.second]) continue;
                visited[curNode.first][curNode.second] = true;

                for (int d = 0; d < 4; d++) {
                    if (0 <= curNode.first + dir[d][0] && curNode.first + dir[d][0] < N
                        && 0 <= curNode.second + dir[d][1] && curNode.second + dir[d][1] < M
                        && !visited[curNode.first + dir[d][0]][curNode.second + dir[d][1]]) {
                        if (map[curNode.first + dir[d][0]][curNode.second + dir[d][1]] != 0) {
                            stack.push_back({ curNode.first + dir[d][0], curNode.second + dir[d][1] });
                        }
                        else {

                            int distance = 1;
                            while (0 <= curNode.first + dir[d][0] * distance && curNode.first + dir[d][0] * distance < N
                                && 0 <= curNode.second + dir[d][1] * distance && curNode.second + dir[d][1] * distance < M
                                && map[curNode.first + dir[d][0] * distance][curNode.second + dir[d][1] * distance] == 0) distance++;

                            if (0 <= curNode.first + dir[d][0] * distance && curNode.first + dir[d][0] * distance < N
                                && 0 <= curNode.second + dir[d][1] * distance && curNode.second + dir[d][1] * distance < M
                                && distance - 1 >= 2)
                                graph[map[curNode.first][curNode.second]][map[curNode.first + dir[d][0] * distance][curNode.second + dir[d][1] * distance]] =
                                min(graph[map[curNode.first][curNode.second]][map[curNode.first + dir[d][0] * distance][curNode.second + dir[d][1] * distance]], distance - 1);

                        }
                    }
                }

            }
        }
    }

    vector<bool> graphVisited(islandNum + 1, false);
    priority_queue<pair<int, int>> PQ;

    int ans = 0;
    PQ.push({ 0, 1 });
    while (!PQ.empty()) {
        pair<int, int> curNode = PQ.top();
        PQ.pop();

        if (graphVisited[curNode.second]) continue;
        graphVisited[curNode.second] = true;

        ans += curNode.first;

        for (int i = 1; i <= islandNum; i++) {
            if (!graphVisited[i] && (graph[curNode.second][i] != MAX))
                PQ.push({ -1 * graph[curNode.second][i], i });
        }

    }

    for(int i = 1; i <= islandNum; i++){
      if(!graphVisited[i]){
        cout << -1;
        exit(0);
      }
    }

    cout << -1 * ans;

    return 0;
}