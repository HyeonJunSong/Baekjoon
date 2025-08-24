#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

int getGCD(int a, int b){
    if(a < 0) a *= -1;
    if(b < 0) b *= -1;

    if(a > b) swap(a, b);

    while(a >= 1){
        int tmp = a;
        a = b % a;
        b = tmp;
    }

    return b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<int> P(N);
    for(int i = 0; i < N; i++) cin >> P[i];

    // BFS
    queue<pair<int, int>> Q({{0, 0}});
    vector<bool> visited(40001, false);

    while(Q.size() > 0){
        pair<int, int> cur = Q.front();
        Q.pop();

        if(cur.first == M){
            cout << cur.second;
            return 0;
        }

        for(int i = 0; i < N; i++) {
            if(cur.first + P[i] > 20000 || cur.first + P[i] < -20000) continue;
            if(visited[cur.first + P[i] + 20000]) continue;
            visited[cur.first + P[i] + 20000] = true;
            Q.push({cur.first + P[i], cur.second + 1});
        }
    }

    cout << -1;
    return 0;
}